import re
import sys
import bisect
import fitz
import pdfplumber

RE_REGADDR = re.compile(r"Register Address:\s*([0-9A-Fa-f]+)H,\s*([0-9]+)");
RE_NAME = re.compile(r"\b((?:IA32|MSR)_[A-Z0-9_]+)\b");
RE_ACCESS = re.compile(r"\(\s*(R/W|RO|WO|R|W)\s*\)");
RE_DESC_END = re.compile(
    r"(?:CPUID|\bIf\b|\bIF\b|\bReserved\b|"          # comment column / reserved
    r"Table\s+\d+-\d+\.|"                             # next table caption (page break)
    r"\n\s*\d+\s*:\s*\d+\b|"                         # "63:7" bit-field row
    r"\n\s*\d+\s+[A-Z])"                             # "0 EN:" bit-field row
)
# Table caption, e.g. "Table 2-33. Uncore PMU MSRs in the Intel Xeon ... Family"
RE_TABLE = re.compile(r"Table\s+\d+-\d+\.\s*([^\n]+)");


def read_text(pdf_path):
    try:
        doc = fitz.open(pdf_path);
        n = doc.page_count;
        print(f"reading {n} pages with PyMuPDF...", file=sys.stderr);
        parts = [];
        for i in range(n):
            parts.append(doc.load_page(i).get_text("text"));
            if i % 100 == 0:
                print(f"  page {i}/{n}", file=sys.stderr);
        doc.close();
        return "\n".join(parts);
    except ImportError:
        pass

    parts = [];
    with pdfplumber.open(pdf_path) as pdf:
        n = len(pdf.pages);
        print(f"reading {n} pages with pdfplumber (slow)...", file=sys.stderr);
        for i, page in enumerate(pdf.pages):
            parts.append(page.extract_text() or "");
            page.flush_cache();   # release per-page objects
            if i % 25 == 0:
                print(f"  page {i}/{n}", file=sys.stderr);
    return "\n".join(parts);


_UNICODE_FIXUPS = {
    "\u2212": "-", "\u2013": "-", "\u2014": "-",   # minus, en dash, em dash
    "\u2265": ">=", "\u2264": "<=", "\u2260": "!=",  # >=  <=  !=
    "\u2018": "'", "\u2019": "'",                     # smart single quotes
    "\u201c": '"', "\u201d": '"',                     # smart double quotes
    "\u00d7": "x", "\u2026": "...", "\u00a0": " ",     # times, ellipsis, nbsp
};


def clean(s):
    for bad, good in _UNICODE_FIXUPS.items():
        s = s.replace(bad, good);
    # drop anything else outside ASCII
    s = s.encode("ascii", "ignore").decode("ascii");
    return re.sub(r"\s+", " ", s).strip(" \t\r\n.;,");


def slugify(s):
    """Turn a caption into a lower-case namespace ident."""
    s = s.encode("ascii", "ignore").decode("ascii").lower();
    s = re.sub(r"[^a-z0-9]+", "_", s).strip("_");
    if not s:
        return "misc";
    if s[0].isdigit():
        s = "_" + s;
    return s;


def table_namespace(title):
    """Namespace for MSRs under a table caption. Architectural -> top level"""
    t = re.sub(r"\(Contd\.?\)", "", title, flags=re.I).strip()
    if re.search(r"architectural", t, flags=re.I):
        return "";
    for pat in (r"\bin the\s+(.+?)\s+Family\b",
                r"\bin\s+(.+?)\s+Family\b",
                r"\bfor the\s+(.+)$",
                r"\bfor\s+(.+)$"):
        mm = re.search(pat, t, flags=re.I);
        if mm:
            return slugify(mm.group(1));
    return slugify(t);


def parse(text):
    # Positions of every table caption, mapped to their namespace.
    caps = [(mm.start(), table_namespace(mm.group(1))) for mm in RE_TABLE.finditer(text)];
    cap_starts = [c[0] for c in caps];

    marks = list(RE_REGADDR.finditer(text));
    seen = {}   # (namespace, name) -> first hex address kept
    for i, m in enumerate(marks):
        stop = marks[i + 1].start() if i + 1 < len(marks) else len(text);
        block = text[m.start():stop];

        hdr = RE_REGADDR.match(block);
        hex_addr = hdr.group(1).upper();

        name_m = RE_NAME.search(block, hdr.end());
        if not name_m:
            continue;
        name = name_m.group(1);

        # Which table caption most recently preceded this MSR?
        j = bisect.bisect_right(cap_starts, m.start()) - 1;
        ns = caps[j][1] if j >= 0 else "";

        # Dedupe per namespace
        key = (ns, name);
        if key in seen:
            if seen[key] != hex_addr:
                where = ns or "<top>"
                print(f"  skip duplicate {where}::{name}: 0x{hex_addr} (kept 0x{seen[key]})",
                      file=sys.stderr);
            continue;
        seen[key] = hex_addr;

        access_m = RE_ACCESS.search(block, name_m.end());

        def cut(seg):
            e = RE_DESC_END.search(seg);
            return clean(seg[:e.start()] if e else seg);

        if access_m:
            desc = cut(block[access_m.end():]) or clean(block[name_m.end():access_m.start()]);
        else:
            desc = cut(block[name_m.end():]);

        yield ns, name, hex_addr, desc;


def _decl(name, hex_addr, desc, indent):
    comment = f" /* {desc} */" if desc else "";
    return f"{indent}static constexpr auto {name} = 0x{int(hex_addr, 16):X};{comment}\n";


def main():
    if len(sys.argv) != 2:
        sys.exit("usage: python x86_intel_msr_builder.py sdm.pdf");

    rows = list(parse(read_text(sys.argv[1])))
    name_addrs = {};
    for ns, name, addr, desc in rows:
        name_addrs.setdefault(name, set()).add(addr);

    top, fams, order, placed = [], {}, [], set();
    for ns, name, addr, desc in rows:
        conflicting = len(name_addrs[name]) >= 2;
        # Conflicting name map to its family namespace
        scope = ns if (conflicting and ns) else "";
        key = (scope, name);
        if key in placed:
            continue;
        placed.add(key);
        if scope == "":
            top.append((name, addr, desc));
        else:
            if scope not in fams:
                fams[scope] = [];
                order.append(scope);
            fams[scope].append((name, addr, desc));

    with open("output.hpp", "w", encoding="utf-8") as f:
        
        f.write("#pragma once\n");
        f.write("#ifdef LURAMAS_TARGET_X86\n");
        f.write("#include <cstdint>\n\n");
        f.write("/* Generated by scripts/x86_intel_msr_builder/x86_intel_msr_builder.py */\n");
        f.write("namespace msrs::intel {\n\n");

        for n, a, d in top:
            f.write(_decl(n, a, d, "      "));

        for ns in order:
            f.write(f"\n      namespace {ns} {{\n");
            for n, a, d in fams[ns]:
                f.write(_decl(n, a, d, "            "));
            f.write("      }\n");

        f.write("\n}\n");
        f.write("#endif\n");

    print(f"done: wrote {len(top)} MSRs "
          f"and {sum(len(v) for v in fams.values())} across {len(order)} families -> output.hpp",
          file=sys.stderr);


if __name__ == "__main__":
    main();

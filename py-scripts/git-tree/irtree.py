import re, sys, difflib

SPLIT = re.compile(r"^(?:ENDING|NON MUTATED) PASS ON .+ =+$", re.M)
HEAD = re.compile(r"^ENDED PASS ON (.+), ([\d.]+), (\d+)$", re.M)
NOTE = re.compile(r"^(?:REMOVING|INSERTED|REPLACED|MUTATED ON FILE) .*", re.M)


def blocks(text):
    chunks = SPLIT.split(text)
    marks = SPLIT.findall(text)
    return zip(chunks, marks)


def parse(text):
    for chunk, mark in blocks(text):
        h = HEAD.search(chunk)
        if not h:
            continue
        name, _, count = h.groups()
        yield (
            name,
            count,
            NOTE.findall(chunk[: h.start()]),
            chunk[h.end() :].strip().splitlines(),
            "NON" not in mark,
        )


def main(src, dst=None):
    runs = list(
        parse(open(src, encoding="utf8", errors="replace").read().replace("\r", ""))
    )
    out, prev = [], []
    for i, (name, count, notes, ir, claimed) in enumerate(runs):
        diff = list(difflib.unified_diff(prev, ir, n=0, lineterm=""))[2:] if i else []
        tag = "" if bool(diff) == claimed or not i else "  <<< MISMATCH"
        out.append(
            "* %04d %-38s %-12s n=%-5s d=%d%s"
            % (i, name, "mutated" if claimed else "NON-MUTATED", count, len(diff), tag)
        )
        out += ["  ; " + n[:150] for n in notes]
        out += ["  " + d for d in diff]
        prev = ir
    dst = dst or src.rsplit(".", 1)[0] + ".tree.txt"
    open(dst, "w", encoding="utf8").write("\n".join(out) + "\n")
    bad = sum(1 for l in out if "MISMATCH" in l)
    print("%d runs, %d mismatches -> %s" % (len(runs), bad, dst), file=sys.stderr)


main(*sys.argv[1:3])

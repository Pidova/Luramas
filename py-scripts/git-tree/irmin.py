import re, sys, itertools, collections

HEAD = re.compile(
    r"^\* (\d+) (.+?)\s{2,}(mutated|NON-MUTATED)\s+n=(\S+)\s+d=(\d+)(.*)$"
)
CAP, WIDTH = 12, 110


def commits(path):
    cur = None
    for line in open(path, encoding="utf8"):
        h = HEAD.match(line.rstrip())
        if h:
            if cur:
                yield cur
            cur = (h, [])
        elif cur and line.strip():
            cur[1].append(line[2:].rstrip())
    if cur:
        yield cur


def squash(body, full):
    notes = collections.Counter(b for b in body if b.startswith("; "))
    diff = [b if full else b[:WIDTH] for b in body if b[:1] in "-+"]
    out = ["%s x%d" % (n, c) if c > 1 else n for n, c in notes.items()]
    out += (
        diff
        if full or len(diff) <= CAP
        else diff[:CAP] + ["... %d more" % (len(diff) - CAP)]
    )
    return out


def main(src, dst=None):
    out = []
    for noop, grp in itertools.groupby(commits(src), lambda c: c[0].group(5) == "0"):
        grp = list(grp)
        if noop:
            names = collections.Counter(h.group(2) for h, _ in grp)
            out.append(
                "~ %s-%s noop x%d: %s"
                % (
                    grp[0][0].group(1),
                    grp[-1][0].group(1),
                    len(grp),
                    ", ".join(
                        "%s%s" % (k, "*%d" % v if v > 1 else "")
                        for k, v in names.items()
                    ),
                )
            )
            continue
        for h, body in grp:
            bad = "!" in h.group(6) or "MISMATCH" in h.group(6)
            out.append(
                "%s %s %s d=%s%s"
                % (
                    h.group(1),
                    h.group(2),
                    h.group(3)[0],
                    h.group(5),
                    "  <<<MISMATCH" if bad else "",
                )
            )
            out += ["  " + b for b in squash(body, bad)]
    dst = dst or src.rsplit(".", 1)[0] + ".min.txt"
    open(dst, "w", encoding="utf8").write("\n".join(out) + "\n")
    print("%s -> %s" % (src, dst), file=sys.stderr)


main(*sys.argv[1:3])

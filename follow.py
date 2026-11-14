
import re

grammar = {}

n = int(input("Enter number of productions: "))

def tokenize(s):
    s = s.replace("ε", "#")
    return re.findall(r"[A-Z][a-z0-9_]*'?|[a-z][a-z0-9_]*|[^\s]", s)

for _ in range(n):
    lhs, rhs = input("Enter production: ").split("->")
    grammar.setdefault(lhs.strip(), []).extend(
        tokenize(p.strip()) for p in rhs.split("|")
    )

first = {nt: set() for nt in grammar}
follow = {nt: set() for nt in grammar}

def find_first():
    changed = True

    while changed:
        changed = False

        for nt in grammar:
            for prod in grammar[nt]:
                if prod == ["#"]:
                    if "#" not in first[nt]:
                        first[nt].add("#")
                        changed = True
                else:
                    nullable = True

                    for ch in prod:
                        if ch not in grammar:
                            if ch not in first[nt]:
                                first[nt].add(ch)
                                changed = True
                            nullable = False
                            break

                        old = len(first[nt])
                        first[nt].update(first[ch] - {"#"})

                        if len(first[nt]) != old:
                            changed = True

                        if "#" not in first[ch]:
                            nullable = False
                            break

                    if nullable and "#" not in first[nt]:
                        first[nt].add("#")
                        changed = True

def first_string(s):
    result = set()

    for ch in s:
        if ch not in grammar:
            result.add(ch)
            return result

        result.update(first[ch] - {"#"})

        if "#" not in first[ch]:
            return result

    result.add("#")
    return result

def find_follow():
    start = next(iter(grammar))
    follow[start].add('$')

    changed = True

    while changed:
        changed = False

        for nt in grammar:
            for prod in grammar[nt]:
                for i, ch in enumerate(prod):
                    if ch in grammar:
                        temp = first_string(prod[i + 1:])
                        old = len(follow[ch])

                        follow[ch].update(temp - {"#"})

                        if "#" in temp:
                            follow[ch].update(follow[nt])

                        if len(follow[ch]) != old:
                            changed = True

find_first()
find_follow()

print("\nFIRST SETS:")
for nt in grammar:
    print(f"FIRST({nt}) = {first[nt]}")

print("\nFOLLOW SETS:")
for nt in grammar:
    print(f"FOLLOW({nt}) = {follow[nt]}")

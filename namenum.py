"""
ID: alextsin2
LANG: PYTHON3
TASK: namenum
"""
import itertools

touch_tone = {
    '2': ['A', 'B', 'C'],
    '3': ['D', 'E', 'F'],
    '4': ['G', 'H', 'I'],
    '5': ['J', 'K', 'L'],
    '6': ['M', 'N', 'O'],
    '7': ['P', 'R', 'S'],
    '8': ['T', 'U', 'V'],
    '9': ['W', 'X', 'Y']}

infile = open("namenum.in", "r")
number = infile.readlines()[0].strip()

with open("dict.txt", "r") as file:
    D = set(line.strip() for line in file.readlines())

tnames = itertools.product(*[touch_tone[d] for d in number])
names = set(map(''.join, tnames))

valid_names = D.intersection(names)

with open("namenum.out", "w") as file:
    if not valid_names:
        file.write("NONE\n")
    else:
        for name in sorted(valid_names):
            file.write(f"{name}\n")

print("Done!")

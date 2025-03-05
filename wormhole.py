"""
ID: alextsin2
LANG: PYTHON3
TASK: wormhole
"""

def read(file):
    N = int(file.readline().strip())
    pos = []
    for i in range(N):
        line = file.readline().strip().split(' ')
        x, y = tuple(int(c) for c in line)
        l = chr(ord('A')+i)
        pos.append(Wormhole(x,y,l))
    return pos

def write(file, result):
    file.write(f"{result}\n")

with open("wormhole.in", "r") as fin, open("wormhole.out", "w") as fout:
    whs = read(fin)
    

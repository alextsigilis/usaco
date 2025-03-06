"""
ID: alextsin2
LANG: PYTHON3
TASK: wormhole
"""
import pdb
from itertools import combinations
from collections import defaultdict

def read(file):
    N = int(file.readline().strip())
    pos = []
    for i in range(N):
        line = file.readline().strip().split(' ')
        x, y = tuple(int(c) for c in line)
        pos.append((x,y))
    return pos

def write(file, result):
    file.write(f"{result}\n")

def gen_next(positions):
    nxt = []
    for x1, y1 in positions:
        x2 = min((x for x,y in positions if (x>x1) and (y==y1)),
                 default=None)
        if x2 is not None:
            a = (x1, y1)
            b = (x2, y1)
            nxt.append((a,b))
        else:
            nxt.append(((x1,y1), None))
    return nxt

def cycle_from(start, nxt, partner, length=0):
    w = start
    for _ in nxt.keys():
        if w is None:
            return False
        w = nxt[partner[w]]
    return w is not None


def contains_cycle(nxt, partner):
    for start in nxt.keys():
        if cycle_from(start, nxt, partner):
            return 1
    return 0

def count_cyclic_pairings(whs, nxt, pairs=[], paired=[]):
    N = len(whs)
    if N == 0:
        return contains_cycle(nxt, dict(pairs))
    count = 0
    f = whs[0]
    for i in range(1, N):
        s = whs[i]
        paired.append(s)
        count += count_cyclic_pairings(whs[1:i]+whs[i+1:],
                                       nxt,
                                       pairs + [(f,s), (s,f)],
                                       paired + [f,s])
    return count


with open("wormhole.in", "r") as fin, open("wormhole.out", "w") as fout:
    pstns = read(fin)
    letter = {wh: i+1 for i,wh in enumerate(pstns)}
    letter[None] = None
    nxt = {letter[u]: letter[w] for u,w in gen_next(pstns)}
    pairings = []
    whs = [w for w in letter.values() if w is not None]
    res = count_cyclic_pairings(whs, nxt)
    print(res)
    write(fout, res)

"""
ID: alextsin2
LANG: PYTHON3
TASK: wormhole
"""
from dataclasses import dataclass

@dataclass
class Wormhole:
    x: int
    y: int
    name: str
    
    def next(self, whs):
        next_whs = [wh for wh in whs if (wh.y == self.y) and (wh.x > self.x)]
        return min(next_whs) if next_whs!=[] else None

    def enter(self, pairs):
        for w1, w2 in pairs:
            if self == w1: return w2
            if self == w2: return w1
        raise Exception("No pair found!")


    def __hash__(self):
        return (self.x, self.y).__hash__()
    
    def __repr__(self):
        return self.name

    def __lt__(self, other):
        if self.y < other.y:
            return True
        elif self.y == other.y:
            return self.x < other.x
        else:
            return False

    def __eq__(self, other):
        return (self.x, self.y) == (other.x, other.y)

    def __le__(self, other):
        return (self < other) or (self == other)

    def __gt__(self, other):
        return not self <= other

    def __ge__(self, other):
        return not self < other

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

def gen_pairings(elements):
    N = len(elements)
    if N == 2:
        return [[set(elements)]]
    first = elements[0]
    pl = []
    for i in range(1, N):
        p = {first, elements[i]}
        remaining = elements[1:i] + elements[i+1:]
        for rest in gen_pairings(remaining):
            pl.append([p] + rest)
    return pl

def walk_from(start, whs, pairs, vis=[]):
    if start is None:
        return vis + [None]
    if start in vis:
        return vis + [start]
    end = start.enter(pairs)
    return walk_from(end.next(whs),
                      whs,
                      pairs,
                      vis = vis + [start, end])

def is_cycle(path):
    return path[-1] is not None

def exists_cycle(whs, pairs):
    for wh in whs:
        path = walk_from(wh, whs, pairs)
        if is_cycle(path):
            return True
    return False

with open("wormhole.in", "r") as fin, open("wormhole.out", "w") as fout:
    whs = read(fin)
    
    for wh in sorted(whs):
        print(f"{wh.name} ", end="")
        if wh.next(whs) is None:
            print()

    count = 0
    for pairs in gen_pairings(whs):
        if exists_cycle(whs, pairs):
            count += 1

    write(fout, count)

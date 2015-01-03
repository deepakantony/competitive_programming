l=10**10
from math import*
def d(p,q):return sqrt((p[0]-q[0])**2+(p[1]-q[1])**2)
def golf(holes):
    start=(0,0)
    t=[l]*5
    return min([d((0,0),h)+g(holes,h,t) for h in holes])

if __name__ == "__main__":
    assert golf({(2, 2), (2, 8), (8, 8), (8, 2), (5, 5)}) == 23.31
    assert golf({(2, 2), (4, 4), (6, 6), (8, 8), (9, 9)}) == 12.73

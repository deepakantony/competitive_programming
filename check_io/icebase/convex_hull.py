import cmath
from functools import cmp_to_key

to_vec=lambda p,q: (q[0]-p[0], q[1]-p[1])
cross=lambda p,q: (p[0]*q[1] - p[1]*q[0])
turn=lambda p,q,r: cross(to_vec(p,q), to_vec(p,r))

def angle_cmp(p,q): 
    # angle and distance
    p_a,p_d = p[0],p[1]
    q_a,q_d = q[0],q[1]
    return q_a - p_a if p_a != q_a else p_d - q_d

def checkio(data):
    """list[list[int, int],] -> list[int,]
    Find the convex hull.
    """
    l = len(data)
    if l < 2: return [range(l)]
    elif l == 2: return [ data.index(x) for x in sorted(data) ]

    # left most bottom point
    px,py = lm = min(data)
    # sort all points by angle and if equal by distance
    angle_dist_data = [ [cmath.phase(p[0]-px+1j*(p[1]-py)), abs(p[0]-px+1j*(p[1]-py)), p] for p in data if lm != p ]
    angle_dist_data = sorted( angle_dist_data, key=cmp_to_key(angle_cmp))

    #print(angle_dist_data)
    ch = [lm, angle_dist_data[0][2]]
    pi,pi_1 = ch[0],ch[1]
    i = 1
    while i < len(angle_dist_data):
        p = angle_dist_data[i][2]
        #print(ch, pi,pi_1,p, turn(pi,pi_1,p))
        
        if turn(pi,pi_1,p) <= 0:
            ch.append(p)
            i += 1
        else: ch.pop()
        pi,pi_1 = ch[-2],ch[-1]

    # add colinear points of the last segment because they were discarded
    ch += [p for a,d,p in angle_dist_data[::-1] if p!= ch[-1] and turn(lm, p, ch[-1]) == 0]

    # get indices
    return [data.index(x) for x in ch]

if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    assert checkio(
        [[7, 6], [8, 4], [7, 2], [3, 2], [1, 6], [1, 8], [4, 9]]
    ) == [4, 5, 6, 0, 1, 2, 3], "First example"
    assert checkio(
        [[3, 8], [1, 6], [6, 2], [7, 6], [5, 5], [8, 4], [6, 8]]
    ) == [1, 0, 6, 3, 5, 2], "Second example"
    assert checkio([[1,1],[2,2],[3,3],[3,1]]) == [0,1,2,3], "third example"
    assert checkio([[1,1],[2,2],[3,3],[1,4]]) == [0,3,2,1], "fourth example"

#import sys # not allowed in checkio
large_num = 10**9
def cross(v1, v2): return v1[0] * v2[1] - v1[1] * v2[0]
def ccw(p1, p2, p3):
    r = cross( (p2[0]-p1[0], p2[1]-p1[1]), (p3[0]-p2[0], p3[1]-p2[1]) )
    return r if r == 0 else ( -1 if r < 0 else 1 )

def colinear(p1, p2, p3): return cross( (p2[0]-p1[0], p2[1]-p1[1]), (p3[0]-p2[0], p3[1]-p2[1]) ) == 0
def is_point_on_line(p, lp1, lp2): 
    zipped = tuple(zip(lp1,lp2))
    return colinear(p, lp1, lp2) and \
        max(zipped[0]) >= p[0] >= min(zipped[0]) and \
        max(zipped[1]) >= p[1] >= min(zipped[1])

def lines_intersect( p1, p2, q1, q2 ):
    # a hack to avoid counting intersection at a vertex
    if p2[1] == q2[1] or p1[1] == q2[1]: q1 = (q1[0], q1[1]+1e-6); q2 = (q2[0], q2[1]+1e-6)

    if ccw(p1,p2,q1) != ccw(p1,p2,q2) and ccw(q1,q2,p1) != ccw(q1,q2,p2):
        return True

    # colinears
    if colinear(p1,p2,q1) and colinear(q2, p1, p2) and (is_point_on_line(p1, q1, q2) or is_point_on_line(p2, q1, q2)): return True

    return False

def is_inside(polygon, point):
    # point on vertex
    if point in polygon: return True
    # point on edge
    if any( [ colinear( p, polygon[(index+1)%(len(polygon))], point ) and is_point_on_line(point, p, polygon[(index+1)%(len(polygon))]) for index, p in enumerate(polygon) ] ): return True
    return sum( [ lines_intersect( p, polygon[(index+1)%(len(polygon))], point, (large_num, point[1]) ) for index, p in enumerate(polygon) ] ) % 2 == 1


if __name__ == '__main__':
    assert is_inside(((1, 1), (1, 3), (3, 3), (3, 1)),
                     (2, 2)) == True, "First"
    assert is_inside(((1, 1), (1, 3), (3, 3), (3, 1)),
                     (4, 2)) == False, "Second"
    assert is_inside(((1, 1), (4, 1), (2, 3)),
                     (3, 2)) == True, "Third"
    assert is_inside(((1, 1), (4, 1), (1, 3)),
                     (3, 3)) == False, "Fourth"
    assert is_inside(((2, 1), (4, 1), (5, 3), (3, 4), (1, 3)),
                     (4, 3)) == True, "Fifth"
    assert is_inside(((2, 1), (4, 1), (3, 2), (3, 4), (1, 3)),
                     (4, 3)) == False, "Sixth"
    assert is_inside(((1, 1), (3, 2), (5, 1), (4, 3), (5, 5), (3, 4), (1, 5), (2, 3)),
                     (3, 3)) == True, "Seventh"
    assert is_inside(((1, 1), (1, 5), (5, 5), (5, 4), (2, 4), (2, 2), (5, 2), (5, 1)),
                     (4, 3)) == False, "Eighth"
    assert is_inside(((1, 4), (4, 5), (5, 2), (2, 1)),
                     (2, 2)) == True, "Ninth"
    assert is_inside(((1, 1),(1, 3),(3, 3),(3, 1)),
                     (1, 1)) == True, "Tenth"
    assert is_inside(((0,0),(0,2),(2,2),(2,0)),
                     (0, 1)) == True, "Eleventh"


def spiral_to_cartesian(spiral_p):
    if spiral_p <= 1: return (0,0)

    # get the distance of p from the center of spiral
    distance_from_center = 0
    spiral_covered_sofar = 1
    while spiral_p > spiral_covered_sofar:
        distance_from_center += 1
        side = 2 * distance_from_center
        spiral_covered_sofar += (4*side) # the coverage of every square box

    side = 2 * distance_from_center
    spiral_sq_start = spiral_covered_sofar - (4*side)
    d = distance_from_center
    sides = [ (-d+1,d), (d,d-1), (d-1,-d), (-d,-d+1) ]
    x = y = 0
    for index, s in enumerate(sides):
        if spiral_p <= (spiral_sq_start + side):
            loc = spiral_p - spiral_sq_start - 1
            loc = loc if index == 0 or index == 3 else -loc
            x, y = (s[0], s[1] + loc) if index % 2 else (s[0] + loc, s[1])
            break
        spiral_sq_start += side

    return (x,y)

def manhattan_distance(p1, p2):
    return abs(p1[0]-p2[0]) + abs(p1[1] - p2[1])

def find_distance(first, second):
    first_cartesian = spiral_to_cartesian(first)
    second_cartesian = spiral_to_cartesian(second)
    return manhattan_distance(first_cartesian, second_cartesian)

if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    assert find_distance(1, 9) == 2, "First"
    assert find_distance(9, 1) == 2, "Reverse First"
    assert find_distance(10, 25) == 1, "Neighbours"
    assert find_distance(5, 9) == 4, "Diagonal"
    assert find_distance(26, 31) == 5, "One row"
    assert find_distance(50, 16) == 10, "One more test"

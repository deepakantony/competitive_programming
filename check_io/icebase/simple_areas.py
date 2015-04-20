import math

def simple_areas(*args):
    if len(args) == 1:
        return math.pi * args[0] * args[0] / 4.0
    if len(args) == 2:
        return args[0] * args[1]
    if len(args) == 3:
        p_2 = 0.5 * sum(args)
        return math.sqrt( p_2 * (p_2 - args[0]) * (p_2 - args[1]) * (p_2 - args[2]) )
    return 0

if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    def almost_equal(checked, correct, significant_digits=2):
        precision = 0.1 ** significant_digits
        return correct - precision < checked < correct + precision

    assert almost_equal(simple_areas(3), 7.07), "Circle"
    assert almost_equal(simple_areas(2, 2), 4), "Square"
    assert almost_equal(simple_areas(2, 3), 6), "Rectangle"
    assert almost_equal(simple_areas(3, 5, 4), 6), "Triangle"
    assert almost_equal(simple_areas(1.5, 2.5, 2), 1.5), "Small triangle"

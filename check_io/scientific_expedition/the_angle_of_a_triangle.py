from math import acos, pi, asin, sin
def checkio(a, b, c):
    if c >= (a+b) or a >= (b+c) or b >= (a+c): return [0, 0, 0]

    # cosine law
    C = int(round(acos( (a*a + b*b - c*c)/(2*a*b) ) * 180.0/pi))
    # sine law
    B = int(round(asin( sin(C * pi / 180.0 ) * b / c ) * 180.0/pi))
    # triangle sum of anges
    A = 180 - B - C
    return sorted( [A, B, C] )

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    assert checkio(4, 4, 4) == [60, 60, 60], "All sides are equal"
    assert checkio(3, 4, 5) == [37, 53, 90], "Egyptian triangle"
    assert checkio(2, 2, 5) == [0, 0, 0], "It's can not be a triangle"

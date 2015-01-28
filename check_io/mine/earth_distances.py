R = 6371

from math import acos,cos,sin,radians
import re
def toradians(pos3d):
    m = re.search( '(?P<deg>\d+).(?P<min>\d+).(?P<sec>\d+).(?P<dir>.)', pos3d )
    sign = -1 if m.group('dir').upper() in ('S','E') else 1
    deg = (int(m.group('deg')) + int(m.group('min')) / 60.0 + int(m.group('sec')) / 3600.0 ) * sign
    return radians( deg )

def distance(first, second):
    lat1, long1 = tuple(map(toradians, first.replace(',',' ').strip().split()))
    lat2, long2 = tuple(map(toradians, second.replace(',',' ').strip().split()))
    arcdist = R * acos( sin(lat1) * sin(lat2) + ( cos(lat1) * cos(lat2) * cos(abs(long1-long2)) ) )
    return arcdist


if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    def almost_equal(checked, correct, significant_digits=1):
        precision = 0.1 ** significant_digits
        return correct - precision < checked < correct + precision

    assert almost_equal(
        distance(u"51°28′48″N 0°0′0″E", u"46°12′0″N, 6°9′0″E"), 739.2), "From Greenwich to Geneva"
    assert almost_equal(
        distance(u"90°0′0″N 0°0′0″E", u"90°0′0″S, 0°0′0″W"), 20015.1), "From South to North"
    assert almost_equal(
        distance(u"33°51′31″S, 151°12′51″E", u"40°46′22″N 73°59′3″W"), 15990.2), "Opera Night"


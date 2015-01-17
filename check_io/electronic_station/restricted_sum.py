def checkio(data):
    return data[0] if len(data) == 1 else checkio(data[:-1]) + data[-1]

assert checkio([1,2,3]) == 6, "First"
assert checkio([1]) == 1, "second"
assert checkio([1,2,3,4,5,6,7,8,9,10]) == 55, "third"
    

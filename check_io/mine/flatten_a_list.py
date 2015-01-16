def flat_list(array):
    res = []
    for x in array: res += flat_list(x) if type(x) is list else [x]
    return res

assert flat_list([1,2,[3,4,5]]) == [1,2,3,4,5], "simple"
assert flat_list([1,2,[3,[4],3,5]]) == [1,2,3,4,3,5], "simple"

def golf(c):
 if c:c=sorted(c);n=c[-1];r=golf(c[:-1]);return[r+n,r][r<n]
 else:return 1

# recursive solution
# -> sort the array
# -> remove the last item and call golf recursively
# -> terminating condition happens when size is 1 (can be done with 0 too i think), 
# -> then at the top level the return value is golf(c[:-1]) + last item if >= this value else return golf(c[:-1])

assert golf([1]) == 2
assert golf([2]) == 1
assert golf([1,2,3,4,5,6,7,8,9,10]) == 56
assert golf([1,1,1,1,1,1,1]) == 8
assert golf([9, 2, 2, 1]) == 6
assert golf([1, 1, 1, 1]) == 5
assert golf([1, 2, 3, 4, 5]) == 16

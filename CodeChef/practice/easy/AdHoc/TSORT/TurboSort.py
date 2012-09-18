
# Even counting sort is slow for python.
t = int(raw_input())
count = [0]*1000001
for n in xrange(t):
	count[int(raw_input())] += 1
for num, c in enumerate(count):
	for y in xrange(c):
		print num

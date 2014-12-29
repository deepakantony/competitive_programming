# first solution using sieve
m=98690
s=[0]*m
s[0]=s[1]=1
e=enumerate
for i,v in e(s):
 if v == 0:
  for j in range(2*i,m,i):
   s[j]=1
p=[i for i,v in e(s) if v==0 and int(str(i)[::-1])==i]
def golf1(n):
 for v in p:
  if v>n:return v

# 2nd solution less optimized for speed and more for golf and needs python2
r=range
def golf2(n):
 for x in r(n+1,9**7):
  if all(x%y for y in r(2,x))&(`x`[::-1]==`x`):return x

# 3rd solution using lambda
r=range
golf1=lambda n:next(x for x in r(n+1,9**7)if`x`[::-1]==`x`*all(x%y for y in r(2,x)))

# 4th trying while
def golf(n):
 n+=1
 while`n`!=`n`[::-1]*all(n%y for y in range(2,n)):n+=1
 return n

# using wilsons algo for testing prime num


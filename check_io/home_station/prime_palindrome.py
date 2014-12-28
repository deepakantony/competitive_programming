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

# 2nd solution less optimized for speed and more for golf
r=range
m=98690
def p(n):
 for x in r(2,n/2):
  if n%x==0: return False
 return True
def golf(n):
 for x in r(n+1,m):
  if p(x) and int(str(x)[::-1])==x:return x
        
    

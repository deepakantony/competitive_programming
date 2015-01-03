#m={'fib':(0,1,1,1,1,0),'tri':(0,1,1,1,1,1),'luc':(2,1,3,1,1,0),'jac':(0,1,1,1,2,0),'pel':(0,1,2,2,1,0),'per':(3,0,2,0,1,1),'pad':(0,1,1,0,1,1)}

def fibgolf(t,n):
    m={'ib':'011110','ri':'011111','uc':'213110','ac':'011120','el':'012210','er':'302011','ad':'011011'}
    f,g,h,a,b,c=t=list(map(int,m[t[1:3]]))
    while n>2:
        h,g,f=a*h+b*g+c*f,h,g
        n-=1
    return (h,t[n])[n<2]

if __name__ == '__main__':
    assert fibgolf('fibonacci', 10) == 55
    assert fibgolf('tribonacci', 10) == 149
    assert fibgolf('lucas', 10) == 123
    assert fibgolf('jacobsthal', 10) == 341
    assert fibgolf('pell', 10) == 2378
    assert fibgolf('perrin', 10) == 17
    assert fibgolf('padovan', 10) == 9
    assert fibgolf('fibonacci', 407) == 5110749320570476684599671752998282949163016220605901117918011486570203288606148368113
    assert fibgolf('fibonacci', 367) == 22334640661774067356412331900038009953045351020683823507202893507476314037053
    assert fibgolf('lucas', 2) == 3
    assert fibgolf('lucas', 1) == 1
    assert fibgolf('lucas', 0) == 2

golf=lambda s,a=0,b=0:min(abs(a-x[0]+1j*(b-x[1]))+golf(s-{x},*x)for x in s)if s else 0

def feq(a,b): print(a,b); return (a-0.01)<b<(a+0.01)
if __name__ == "__main__":
    assert feq(golf({(2, 2), (2, 8), (8, 8), (8, 2), (5, 5)}), 23.31)
    assert feq(golf({(2, 2), (4, 4), (6, 6), (8, 8), (9, 9)}), 12.73)

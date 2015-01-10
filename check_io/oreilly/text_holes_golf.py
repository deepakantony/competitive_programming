# store a set of points that are spaces and then do a check
e=enumerate
def golf(t):
 s={(r+1,c+1) for r,a in e(t[1:-1])for c,b in e(a[1:-1])if b==' '}
 a=sum(1 for x,y in s if all((x+i,y+j)not in s for i,j in zip([1,-1,0]*3,[1,-1]*3+[0,0])))
 print(a,s)
 print([(x,y) for x,y in s if all((x+i,y+j)not in s for i,j in zip([1,-1,0]*3,[1,-1]*3+[0,0]))])
 return a


# this algo goes through all spaces and checks if it's surround
z=range
l=len
golf1=lambda t:sum(t[r][c]==' '*all(c+j<l(t[r+i])and t[r+i][c+j]!=' 'for i,j in zip([1,-1,0]*3,[1,-1]*3+[0,0]))for r in z(1,l(t)-1)for c in z(1,l(t[r])-1))

 
if __name__ == "__main__":
 assert golf(["How are you doing?",
              "I'm fine. OK. Test",
              "Lorem Ipsum?",
              "Of course!!!",
              "1234567890",
              "0        0",
              "1234567890",
              "Fine! good buy!"]) == 3, "Test 1"
 print()
 assert golf(["Lorem ipsum dolor",
              "sit amet,",
              "consectetuer",
              "adipiscing elit.",
              "Aenean commodo",
              "ligula eget dolor.",
              "Aenean massa. Cum",
              "sociis natoque",
              "penatibus et magnis",
              "dis parturient",
              "montes, nascetur",
              "ridiculus mus. Donec",
              "quam felis,",
              "ultricies nec,",
              "pellentesque eu,",
              "pretium quis, sem.",
              "Nulla consequat",
              "massa quis enim.",
              "Donec pede justo,",
              "fringilla vel,"]) == 11, "Test 2"

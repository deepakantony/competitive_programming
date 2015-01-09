n=[(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]
e=enumerate
def golf(t,a=0):
 for r,l in e(t):
  for c,v in e(l):
   if(v==' 'and all(0<=(r+i)<len(t)and 0<=(c+j)<len(t[r+i])and t[r+i][c+j]!=' 'for i,j in n)):
    print(v,r,c)
    a+=1
 return a

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

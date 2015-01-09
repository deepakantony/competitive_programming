n=[(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)]
def golf(t,a=0,r=1):
 while r+1<len(t):
  c=1
  while c+1<len(t[r]):a+=t[r][c]==' '*all(c+j<len(t[r+i])and t[r+i][c+j]!=' 'for i,j in n);c+=1
  r+=1
 return a

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

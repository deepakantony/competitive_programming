def checkio(expression):
    stack = []
    bracket_map = {"(":")","{":"}","[":"]"}
    for e in expression:
        if e in "({[": stack.append(e)
        elif e in ")}]" and ( not stack or e != bracket_map[stack.pop()] ): return False

    return False if stack else True

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    assert checkio("((5+3)*2+1)") == True, "Simple"
    assert checkio("{[(3+1)+2]+}") == True, "Different types"
    assert checkio("(3+{1-1)}") == False, ") is alone inside {}"
    assert checkio("[1+1]+(2*2)-{3/3}") == True, "Different operators"
    assert checkio("(({[(((1)-2)+3)-3]/3}-3)") == False, "One is redundant"
    assert checkio("2+3") == True, "No brackets, no problem"

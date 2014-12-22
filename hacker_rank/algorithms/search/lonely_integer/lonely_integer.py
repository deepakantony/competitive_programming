#!/usr/bin/py
# Head ends here
def lonelyinteger(a):
    answer = 0
    a_list = list(a)
    for entry in a_list:
        if a_list.count(entry) == 1:
            answer = entry
    return answer

# Tail starts here
if __name__ == '__main__':
    a = int(input())
    b = map(int, input().strip().split(" "))
    print(lonelyinteger(b))

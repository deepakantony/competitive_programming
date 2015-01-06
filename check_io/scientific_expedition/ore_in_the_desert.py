# get radius from (0,0), (9,0) and (9,5)
def checkio(previous):
    if len(previous) == 0: return (0,0)
    if len(previous) == 1: return (9,0)
    
    r0,r1 = previous[0][2], previous[1][2]
    x = 
    if 

if __name__ == '__main__':
    #This part is using only for self-testing.
    def check_solution(func, ore):
        recent_data = []
        for step in range(4):
            row, col = func([d[:] for d in recent_data])  # copy the list
            if row < 0 or row > 9 or col < 0 or col > 9:
                print("Where is our probe?")
                return False
            if (row, col) == ore:
                return True
            dist = round(((row - ore[0]) ** 2 + (col - ore[1]) ** 2) ** 0.5)
            recent_data.append([row, col, dist])
        print("It was the last probe.")
        return False

    assert check_solution(checkio, (1, 1)), "Example"
    assert check_solution(checkio, (9, 9)), "Bottom right"
    assert check_solution(checkio, (6, 6)), "Center"
    assert check_solution(checkio, (0, 2)), "First row at 2"
    assert check_solution(checkio, (0, 5)), "First row at 5"
    assert check_solution(checkio, (0, 6)), "First row at 6"
    assert check_solution(checkio, (0, 7)), "First row at 7"

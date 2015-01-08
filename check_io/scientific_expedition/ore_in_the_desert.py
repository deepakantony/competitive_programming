# get radius from (0,0), (9,0) 
# eq for center (0,0) -> r0**2 = x**2 + y**2
# eq for center (d,0) -> r1**2 = (x-d)**2 + y**2
# eq for center (i,j) -> r2**2 = (x-i)**2 + (y-j)**2
def checkio(previous):
    if len(previous) == 0: return (0,0)

    clamp = lambda k: max(0,min(k,9))
    
    d = r0 = previous[0][2]
    d = clamp(d)
    if len(previous) == 1: return (d,0)

    r1 = previous[1][2]

    x_real_1 = (r0**2 - r1**2 + d**2) / (2 * d)
    y_real_1 = (r0**2 - x_real_1**2) ** 0.5

    i,j = clamp(round(x_real_1)), clamp(round(y_real_1))
    if len(previous) == 2: return (i,j)
    
    r2 = previous[2][2]

    neighbors = {(-1,-1), (0,-1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)}
    for n in neighbors:
        row,col = i+n[0],j+n[1]
        if 0 <= row <= 9 and 0 <= col <= 9:
            if r0 == round((row**2 + col**2)**0.5) and \
               r1 == round(((row-d)**2 + col**2)**0.5) and \
               r2 == round(((row-i)**2 + (col-j)**2)**0.5):
                return (row,col)
    
    # i've got nothing I'm just returning previous
    return (i,j)

if __name__ == '__main__':
    #This part is using only for self-testing.
    def check_solution(func, ore):
        recent_data = []
        for step in range(4):
            row, col = func([d[:] for d in recent_data])  # copy the list
            #print(row,col, ore)
            if row < 0 or row > 9 or col < 0 or col > 9:
                print("Where is our probe?")
                return False
            if (row, col) == ore:
                return True
            dist = round(((row - ore[0]) ** 2 + (col - ore[1]) ** 2) ** 0.5)
            recent_data.append([row, col, dist])
        print("It was the last probe.")
        return False

    for x in range(10):
        for y in range(10): assert check_solution(checkio, (x,y)), str((row,col))


    assert check_solution(checkio, (1, 1)), "Example"
    assert check_solution(checkio, (9, 9)), "Bottom right"
    assert check_solution(checkio, (6, 6)), "Center"
    assert check_solution(checkio, (0, 2)), "First row at 2"
    assert check_solution(checkio, (0, 5)), "First row at 5"
    assert check_solution(checkio, (0, 6)), "First row at 6"
    assert check_solution(checkio, (0, 7)), "First row at 7"

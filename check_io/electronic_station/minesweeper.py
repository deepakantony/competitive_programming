from random import randint, choice

neighbors = { (-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1) }

def count_marked_mines(field,row,col):
    count = 0
    for r,c in neighbors:
        if 0 <= row+r < len(field) and 0 <= col+c < len(field[0]):
            if field[row+r][col+c] == 9: count += 1
    return count

def count_unopened_squares(field,row,col):
    count = 0
    for r,c in neighbors:
        if 0 <= row+r < len(field) and 0 <= col+c < len(field[0]):
            if field[row+r][col+c] == -1: count += 1
    return count

def get_first_unopened_square(field,row,col):
    for r,c in neighbors:
        if 0 <= row+r < len(field) and 0 <= col+c < len(field[0]):
            if field[row+r][col+c] == -1: return (row+r,col+c)
    return (0,0)


def pattern_search(field):
    # basic pattern search; should be good enough for beginner minesweeper setups
    for row,row_data in enumerate(field):
        for col,x in enumerate(row_data):
            marked_mines = count_marked_mines(field,row,col)
            unopened_squares = count_unopened_squares(field,row,col)
            if unopened_squares > 0 and x == (unopened_squares + marked_mines):
                # find an unopened square and return True
                r,c = get_first_unopened_square(field,row,col)
                return [True, r, c]

            if x == marked_mines and unopened_squares > 0:
                # find an unopened square and return False
                r,c = get_first_unopened_square(field,row,col)
                return [False, r, c]
    return None

def checkio(field):
    res = None
    if all( x < 0 for row in field for x in row ):
        res = [False, 0, 0]
    else:
        ps = pattern_search(field)
        if ps: res = ps
    
    if not res:
        # leave it for luck
        luck = [ choice([True,False]), randint(0,len(field)), randint(0,len(field[0])) ]
        res = luck
        
    return res

#This part is using only for self-testing
if __name__ == '__main__':

    def check_is_win_referee(input_map):
        unopened = [1 for x in range(10) for y in range(10) if input_map[x][y] == -1]
        return not unopened

    def build_map(input_map, mine_map, row, col):
        opened = [(row, col)]
        while opened:
            i, j = opened.pop(0)
            neighs = [(i + x, j + y) for x, y in [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
                      if 0 <= i + x < 10 and 0 <= j + y < 10]
            value = sum([mine_map[k][l] for k, l in neighs])
            input_map[i][j] = value
            if not value:
                for k, l in neighs:
                    if input_map[k][l] == -1 and (k, l) not in opened:
                        opened.append((k, l))
        return input_map

    def check_solution(func, mine_map):
        input_map = [[-1] * 10 for _ in range(10)]
        while True:

            is_mine, row, col = func([row[:] for row in input_map])  # using copy
            if input_map[row][col] != -1:
                print("You tried to uncover or mark already opened cell.")
                return False
            if is_mine and not mine_map[row][col]:
                print("You marked the wrong cell.")
                return False
            if not is_mine and mine_map[row][col]:
                print("You uncovered a mine. BANG!")
                return False
            if is_mine:
                input_map[row][col] = 9
            else:
                build_map(input_map, mine_map, row, col)
            if check_is_win_referee(input_map):
                return True
        return False

    assert check_solution(checkio, [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 1, 0, 1, 0, 0, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 1, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 1, 0, 1, 0, 0, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]), "Simple"

    assert check_solution(checkio, [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 1, 1, 0, 0, 0, 1, 1, 1, 0],
        [0, 1, 0, 0, 0, 0, 0, 0, 1, 0],
        [0, 1, 0, 0, 0, 0, 0, 0, 1, 0],
        [0, 1, 0, 0, 0, 0, 0, 0, 1, 0],
        [0, 1, 0, 0, 0, 0, 0, 0, 1, 0],
        [0, 1, 0, 0, 0, 0, 0, 0, 1, 0],
        [0, 1, 1, 1, 1, 1, 1, 1, 1, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]), "Gate"

    assert check_solution(checkio, [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
        [0, 0, 1, 1, 0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 1, 0, 0, 0, 0, 1, 0, 0],
        [0, 0, 0, 0, 0, 1, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 1, 0],
        [0, 0, 1, 0, 0, 0, 1, 0, 0, 0],
        [0, 1, 0, 0, 0, 0, 0, 0, 0, 0]]), "Various"

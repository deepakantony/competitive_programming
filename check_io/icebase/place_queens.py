COLS = "abcdefgh"
ROWS = "12345678"

THREATS = {c + r: set(
    [c + ROWS[k] for k in range(8)] +
    [COLS[k] + r for k in range(8)] +
    [COLS[k] + ROWS[i - j + k] for k in range(8) if 0 <= i - j + k < 8] +
    [COLS[k] + ROWS[- k + i + j] for k in range(8) if 0 <= - k + i + j < 8])
           for i, r in enumerate(ROWS) for j, c in enumerate(COLS)}

def invalid_queens(placed):
    for p in placed:
        if any( pl in THREATS[p] for pl in placed if pl != p ):
            return True
    return False

def get_first_row_not_occupied(placed):
    occupied_rows = [x[1] for x in placed]
    for r in ROWS:
        if r not in occupied_rows: return r
    return str(len(ROWS)+1) # all rows are occupied

def place_queens(placed):
    res = set()
    if invalid_queens(placed): return res

    row = get_first_row_not_occupied(placed)
    if int(row) > len(ROWS):
        res = placed
    else:
        for col in COLS:
            res = place_queens(placed.union({col+row}))
            if res: break;

    return res


if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    from itertools import combinations

    def check_coordinate(coor):
        c, r = coor
        return c in COLS and r in ROWS

    def checker(func, placed, is_possible):
        user_set = func(placed.copy())
        print ( placed, "=>", user_set )
        
        if not all(isinstance(c, str) and len(c) == 2 and check_coordinate(c) for c in user_set):
            print("Wrong Coordinates")
            return False
        threats = []

        for f, s in combinations(user_set.union(placed), 2):
            if s in THREATS[f]:
                threats.append([f, s])
        if not is_possible:
            if user_set:
                print("Hm, how did you place them?")
                return False
            else:
                return True
        if is_possible and len(user_set) != 8:
            print("You've not placed all 8 queens.")
            return False
        if not all(p in user_set for p in placed):
            print("You forgot about placed queens.")
            return False
        if is_possible and threats:
            print("I see some problems in this placement.")
            return False
        return True

    assert checker(place_queens, {"b2", "c4", "d6", "e8"}, True), "1st Example"
    assert checker(place_queens, {"b2", "c4", "d6", "e8", "a7", "g5"}, False), "2nd Example"
    assert checker(place_queens, {"b2", "f7"}, True), "bug finder2"
    assert checker(place_queens, {"b3", "d4", "f5"}, False), "bug finder1"
    


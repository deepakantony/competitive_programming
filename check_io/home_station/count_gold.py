def dp_count_gold(pyramid, dp_table, row, col):
    len_pyramid = len(pyramid)
    
    if row >= len_pyramid or col >= len(pyramid[row]): return 0
    if dp_table[row][col] == -1: 
        dp_table[row][col] = pyramid[row][col] + \
                             max( dp_count_gold(pyramid, dp_table, row+1, col), \
                                  dp_count_gold(pyramid, dp_table, row+1, col+1) )
    return dp_table[row][col]
    

def count_gold(pyramid):
    """
    Return max possible sum in a path from top to bottom
    """
    len_pyramid = len(pyramid)
    dp_table = [ [-1 for col in range(len_pyramid)] for row in range(len_pyramid)]
    output = dp_count_gold(pyramid, dp_table, 0, 0)
    #replace this for solution
    return output


if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    assert count_gold((
        (1,),
        (2, 3),
        (3, 3, 1),
        (3, 1, 5, 4),
        (3, 1, 3, 1, 3),
        (2, 2, 2, 2, 2, 2),
        (5, 6, 4, 5, 6, 4, 3)
    )) == 23, "First example"
    assert count_gold((
        (1,),
        (2, 1),
        (1, 2, 1),
        (1, 2, 1, 1),
        (1, 2, 1, 1, 1),
        (1, 2, 1, 1, 1, 1),
        (1, 2, 1, 1, 1, 1, 9)
    )) == 15, "Second example"

def print_state_from_graph(G, min_row, min_col, max_row, max_col):
    print(G)
    for row in range(min_row, max_row+1):
        for col in range(min_col, max_col+1):
            print( "1 " if (row,col) in G else "0 ", end='' ) 
        print()

def print_states( G, cells_dying, cells_new ):
    min_row = min( n[0] for n in G.union(cells_dying) )
    min_col = min( n[1] for n in G.union(cells_dying) )
    max_row = max( n[0] for n in G.union(cells_dying) )
    max_col = max( n[1] for n in G.union(cells_dying) )
    print("Graph")
    print_state_from_graph(G,min_row,min_col,max_row,max_col)
    print("Cells dying")
    print_state_from_graph(cells_dying,min_row,min_col,max_row,max_col)
    print("Cells born")
    print_state_from_graph(cells_new,min_row,min_col,max_row,max_col)

import itertools

neighbors = {(-1,-1), (0,-1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)}

def count_neighbors(G, node):
    c = itertools.count()
    for row,col in neighbors:
        if (node[0]+row,node[1]+col) in G: next(c)
    return next(c)

def game_of_life(G):
    cells_dying = { node for node in G if not (2 <= count_neighbors(G,node) <= 3) }
    cells_new = { (n[0]+node[0], n[1]+node[1]) for node in G for n in neighbors if count_neighbors(G, (n[0]+node[0], n[1]+node[1])) == 3 }
    #print_states( G.union( cells_new ) - cells_dying, cells_dying, cells_new )
    return G.union( cells_new ) - cells_dying

def convert_to_graph(state):
    return { (row,col) for row, row_data in enumerate(state) for col, v in enumerate(row_data) if v }

def life_counter(state, tick_n):
    G = convert_to_graph(state)
    for x in range(tick_n): G = game_of_life(G)
    return len(G)

if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    assert life_counter(((0, 1, 0, 0, 0, 0, 0),
                         (0, 0, 1, 0, 0, 0, 0),
                         (1, 1, 1, 0, 0, 0, 0),
                         (0, 0, 0, 0, 0, 1, 1),
                         (0, 0, 0, 0, 0, 1, 1),
                         (0, 0, 0, 0, 0, 0, 0),
                         (1, 1, 1, 0, 0, 0, 0)), 4) == 15, "Example"
    assert life_counter(((0, 1, 0, 0, 0, 0, 0),
                         (0, 0, 1, 0, 0, 0, 0),
                         (1, 1, 1, 0, 0, 0, 0),
                         (0, 0, 0, 0, 0, 1, 1),
                         (0, 0, 0, 0, 0, 1, 1),
                         (0, 0, 0, 0, 0, 0, 0),
                         (1, 1, 1, 0, 0, 0, 0)), 15) == 14, "Little later"
    assert life_counter(((0, 1, 0),
                         (0, 0, 1),
                         (1, 1, 1)), 50) == 5, "Glider"
    assert life_counter(((1, 1, 0, 1, 1),
                         (1, 1, 0, 1, 1),
                         (0, 0, 0, 0, 0),
                         (1, 1, 0, 1, 1),
                         (1, 1, 0, 1, 1)), 100) == 16, "Stones"
    assert life_counter(((1, 1, 1, 0, 0, 0),
                         (1, 0, 0, 0, 0, 0),
                         (0, 1, 0, 0, 1, 0),
                         (0, 0, 0, 0, 0, 1),
                         (0, 0, 0, 1, 1, 1)), 1000) == 10, "Gliders"
    

    

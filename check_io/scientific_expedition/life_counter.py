import itertools

def game_of_life(G):
    pass

def convert_to_graph(state):
    neighbors = {(-1,-1), (0,-1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)}
    v = itertools.count()
    state_with_vertex_index = [ [next(v) if x == 1 else -1 for x in row_data] for row_data in state ]
    G = [ [] for vertex in range(next(v)) ]
    for row,row_data in enumerate(state_with_vertex_index):
        for col,vertex in enumerate(row_data):
            if vertex >= 0:
                for x,y in neighbors:
                    n1,n2=row+x,col+y
                    if n1 >= 0 and n2 >= 0 and n1 < len(state) and n2 < len(row_data):
                        neighbor_v = state_with_vertex_index[n1][n2]
                        if neighbor_v >= 0: G[vertex].append(neighbor_v)
    for x in state_with_vertex_index: print(x)
    for x in G: print(x)
    return G

def life_counter(state, tick_n):
    G = convert_to_graph(state)
    # TODO: use expr
    for x in range(tick_n): game_of_life(G)
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

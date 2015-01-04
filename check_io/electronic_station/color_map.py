
def dfs_color_map(G, colors, cur_node):
    if not G or colors[cur_node] != -1: return
    
    colors_set = {1,2,3,4}
    neigh_colors = set()
    for neigh in G[cur_node]:
        neigh_colors.add(colors[neigh])
    c = min(colors_set-neigh_colors)

    colors[cur_node] = c

    for neigh in G[cur_node]:
        dfs_color_map(G, colors, neigh)

def construct_graph(region):
    country_count = 1+max(map(max,region))
    G = [ set() for c in range(country_count) ]
    neigh = { (0,1),(1,0),(0,-1),(-1,0) }
    for i,row in enumerate(region):
        for j,c in enumerate(row):
            for n in neigh:
                n1,n2 = i+n[0],j+n[1]

                if n1 >= 0 and n1 < len(region) and n2 >= 0 and n2 < len(row):
                    nc = region[n1][n2]
                    if nc != c: G[c].add(nc)
    return G

def color_map(region):
    G = construct_graph(region)
    colors = [-1]*len(G)
    dfs_color_map(G, colors, 0)
    print( G, colors )
    return colors

if __name__ == '__main__':
    #These "asserts" using only for self-checking and not necessary for auto-testing
    NEIGHS = ((-1, 0), (1, 0), (0, 1), (0, -1))
    COLORS = (1, 2, 3, 4)
    ERROR_NOT_FOUND = "Didn't find a color for the country {}"
    ERROR_WRONG_COLOR = "I don't know about the color {}"

    def checker(func, region):
        user_result = func(region)
        if not isinstance(user_result, (tuple, list)):
            print("The result must be a tuple or a list")
            return False
        country_set = set()
        for i, row in enumerate(region):
            for j, cell in enumerate(row):
                country_set.add(cell)
                neighbours = []
                if j < len(row) - 1:
                    neighbours.append(region[i][j + 1])
                if i < len(region) - 1:
                    neighbours.append(region[i + 1][j])
                try:
                    cell_color = user_result[cell]
                except IndexError:
                    print(ERROR_NOT_FOUND.format(cell))
                    return False
                if cell_color not in COLORS:
                    print(ERROR_WRONG_COLOR.format(cell_color))
                    return False
                for n in neighbours:
                    try:
                        n_color = user_result[n]
                    except IndexError:
                        print(ERROR_NOT_FOUND.format(n))
                        return False
                    if cell != n and cell_color == n_color:
                        print("Same color neighbours.")
                        return False
        if len(country_set) != len(user_result):
            print("Excess colors in the result")
            return False
        return True
    assert checker(color_map, (
        (0, 0, 0),
        (0, 1, 1),
        (0, 0, 2),
    )), "Small"
    assert checker(color_map, (
        (0, 0, 2, 3),
        (0, 1, 2, 3),
        (0, 1, 1, 3),
        (0, 0, 0, 0),
    )), "4X4"
    assert checker(color_map, (
        (1, 1, 1, 2, 1, 1),
        (1, 1, 1, 1, 1, 1),
        (1, 1, 0, 1, 1, 1),
        (1, 0, 0, 0, 1, 1),
        (1, 1, 0, 4, 3, 1),
        (1, 1, 1, 3, 3, 3),
        (1, 1, 1, 1, 3, 5),
    )), "6 pack"

    assert checker(color_map, (
        (11,0,0,0,0,0,7,0,),
        (0,0,0,0,0,0,7,0,),
        (0,0,4,4,4,0,7,0,),
        (0,0,0,0,0,0,0,0,),
        (0,0,1,0,1,0,0,0,),
        (5,5,1,2,1,6,6,0,),
        (0,0,1,0,1,0,0,0,),
        (0,0,0,0,0,0,0,0,),
        (0,0,3,3,3,0,8,0,),
        (0,0,10,10,9,0,8,0,),
        (0,0,0,10,9,9,8,0,),
    )), "fail"

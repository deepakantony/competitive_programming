#Your code here
#You can import some modules or create additional functions

from collections import deque

def construct_path(path_map, start_pos, end_pos):
    MOVE = { (1,0): 'S', (-1,0): 'N', (0,1): 'E',(0,-1): 'W' }
    pit_pos = (-1, -1)
    if path_map[end_pos[0]][end_pos[1]] == pit_pos: 
        return ""

    path = ""
    cur_pos = end_pos
    while cur_pos != start_pos:
        if cur_pos == pit_pos: return "" # invalid move
        path_prev = path_map[cur_pos[0]][cur_pos[1]]
        if cur_pos == path_prev: return "" # incorrect path map; should only terminate at start pos
        if cur_pos[0] != path_prev[0] and cur_pos[1] != path_prev[1]: return "" # invalid move
        diff_prev_to_cur = cur_pos[0] - path_prev[0], cur_pos[1] - path_prev[1]
        move = MOVE.get(diff_prev_to_cur)
        if not move: return ""
        path += move 
        #if path_prev[0] == (cur_pos[0] - 1): # moving south
        #path += 'S'
        #elif path_prev[0] == (cur_pos[0] + 1): # moving north
        #    path += 'N'

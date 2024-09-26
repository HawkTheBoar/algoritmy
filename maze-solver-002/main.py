from enum import Enum
maze = [
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [1, 1, 1, 1]
]
N = len(maze[0])
x, y = (0, 0)
print("length: ",N)
def is_valid_move(x, y):
    return maze[y][x] == 1
def step(x, y):
    maze[y][x] = 2
    if(x == N - 1 and y == N - 1):
        return True
    for dx, dy in [(0, 1), (1, 0), (-1, 0), (0, -1)]:
        if(x+dx < 0 or x+dx > N - 1 or y+dy < 0 or y + dy > N - 1):
            continue
        if(is_valid_move(x+dx, y+dy)):
            return step(x+dx, y+dy)
    return False
def print_maze(maze):
    for y in range(len(maze)):
        for x in range(len(maze[y])):
            tile = maze[y][x];

            if tile == 1:
                print("\033[32m", end="")  # Green for path
            elif tile == 2:
                print("\033[34m", end="")  # Blue for visited
            else:
                print("\033[31m", end="")  # Red for walls
            print("███", end="")
        print()
print(step(x, y))
print_maze(maze)

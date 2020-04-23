puzzle = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 0, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
]
guess = [
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0]
]


def draw():
    for j in puzzle:
        for i in j:
            print(i, end=" ")
        print("\n")


def find_free():
    for i in range(9):
        for j in range(9):
            if (puzzle[i][j] == 0):
                l = [i, j]
                guess[i][j] = 1
                return l
    return False


def is_valid(n, x, y):
    for i in range(9):
        if (puzzle[x][i] == n or puzzle[i][y] == n):
            return False
    x_square = (x // 3) * 3
    y_square = (y // 3) * 3
    for i in range(x_square, x_square + 3):
        for j in range(y_square, y_square + 3):
            if (puzzle[i][j] == n):
                return False
    return True


def solve():
    l = find_free()
    if (l == False):
        return True
    x = l[0]
    y = l[1]
    for i in range(1, 10):
        if (is_valid(i, x, y)):
            puzzle[x][y] = i
            if (solve()):
                return True
            puzzle[x][y] = 0
    return False


if (solve()):
    draw()
else:
    print("I can not solve it! wow....\n")

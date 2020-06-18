puzzle = [
    [],
    [],
    [],
    [],
    [],
    [],
    [],
    [],
    []
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
def check_a(a,col,row):
    while len(a)>1 or a.isdigit() == False :
        print("oh your number is unaccepetable.pleas enter a good number:)")
        for col in range(col,col+1):
            a=input("[row"+str(row+1)+"]"+"[col"+str(col+1)+"]:")
    else:
        return a

def get_puzzle():
    for row in range(9):
        for col in range(9):
            a=input("[row"+str(row+1)+"]"+"[col"+str(col+1)+"]:")
            b=check_a(a,col,row)
            b=int(b)
            r = puzzle[row]
            r.insert(col,b)

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
get_puzzle()

if (solve()):
    draw()
else:
    print("I can not solve it! wow....\n")

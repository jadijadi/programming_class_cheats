import numpy as np
import re

class Board:
    def __init__(self, data):
        self.data = data
        self.marked = np.zeros((5,5))

    def mark(self, num):
        for i in range(5):
            for j in range(5):
                if self.data[i,j] == num:
                    self.marked[i,j] = 1

    def win(self):
        for i in range(5):
            won = True
            for j in range(5):
                if self.marked[i,j] == 0:
                    won = False
            if won:
                return True
        for j in range(5):
            won = True
            for i in range(5):
                if self.marked[i,j] == 0:
                    won = False
            if won:
                return True
        return False

    def score(self, called):
        score = 0
        for i in range(5):
            for j in range(5):
                if self.marked[i,j] == 0:
                    score += self.data[i,j]
        return score * called

with open("input.txt") as f:
    lines = f.readlines()

lines = [ l.strip() for l in lines]

rands = lines[0].split(',')
rands = [ int(r) for r in rands ]

boards = []

for i in range(100):
    this_board = np.zeros((5,5))
    for j in range(5):
        this_line = lines[i*6+j+2]
        this_row = re.sub(' +', ' ', this_line).strip().split(' ')
        this_board[j] = [ int(n) for n in this_row ]
    boards.append(Board(this_board))

for r in rands:
    for board in boards:
        board.mark(r)
        if board.win():
            print(board.score(r))
            exit()



















#!/usr/bin/env python

import curses
import random
import time

hardness_level = 0.95
food_count = 10
player_char = '🚢'
food_char = "🍕"
enemy_char = '🌚'
food_age = 500
enemy_count = 3

stdscr = curses.initscr()
curses.noecho()
curses.curs_set(0);
curses.cbreak()
stdscr.keypad(True)
stdscr.nodelay(True)

score = 0
world = []
food = []
enemy = []
maxl = curses.LINES - 1
maxc = curses.COLS - 1

player_l = 0
player_c = 0

def random_position():
    l = random.randint(0, maxl-1)
    c = random.randint(0, maxc-1)
    while world[l][c] != ' ': # TODO: a bug if the whole world is occupied
        l = random.randint(0, maxl)
        c = random.randint(0, maxc)
    return l, c

def init():
    global player_l, player_c
    for i in range(-1, maxl+1):
        world.append([])
        for j in range(-1, maxc+1):
            world[i].append(' ' if random.random() > 0.1 else '.')

    for _ in range(food_count):
        l, c = random_position()
        a = random.randint(food_age, food_age*5)
        food.append((l, c, a))

    for _ in range(enemy_count):
        l, c = random_position()
        enemy.append((l,c))

    player_l, player_c = random_position()

def draw():
    # draw the world
    for i in range(maxl):
        for j in range(maxc):
            stdscr.addch(i, j, world[i][j])

    stdscr.addstr(1, 1, f"Score: {score}")

    # show the food
    for f in food:
        l, c, a = f
        stdscr.addch(l, c, food_char)

    # draw enemy
    for e in enemy:
        l, c = e
        stdscr.addch(l, c, enemy_char)

    # draw the player
    stdscr.addch(player_l, player_c, player_char)
    stdscr.refresh()

def force_in_range(v, vmin, vmax):
    if v > vmax:
        return vmax
    if v < vmin:
        return vmin
    return v

def move(c):
    # moved the player based on c, which can be any of asdw
    global player_l, player_c

    if c == 'w' and player_l>0 and world[player_l-1][player_c] != '.':
        player_l -= 1
    elif c == 'a'and world[player_l][player_c-1] != '.':
        player_c -= 1
    elif c == 'd' and world[player_l][player_c+1] != '.':
        player_c += 1
    elif c == 's' and world[player_l+1][player_c] != '.':
        player_l += 1 
    
    player_l = force_in_range(player_l, 0, maxl-1)
    player_c = force_in_range(player_c, 0, maxc-1)


def check_enemy():
    global playing
    for i in range(len(enemy)):
        l, c = enemy[i]
        if l == player_l and c == player_c:
            stdscr.addstr(maxl//2, maxc//2, "YOU DIED")
            stdscr.refresh()
            time.sleep(3)
            playing = False
        else:
            if random.random() > hardness_level:
                if l > player_l:
                    l -= 1
            if random.random() > hardness_level:
                if l < player_l:
                    l += 1
            if random.random() > hardness_level:
                if c > player_c:
                    c -= 1
            if random.random() > hardness_level:
                if c < player_c:
                    c += 1
            
            l = force_in_range(l, 0, maxl-1)
            c = force_in_range(c, 0, maxc-1)
            enemy[i] = (l, c)

def check_food_status():
    global score
    for i in range(len(food)):
        l, c, a = food[i]
        a -= 1
        if l == player_l and c == player_c:
            score += 10
            nl, nc = random_position()
            na = random.randint(food_age, food_age*5)
            food[i] = (nl, nc, na)
        elif a <= 0:
            nl, nc = random_position()
            na = random.randint(food_age, food_age*5)
            food[i] = (nl, nc, na)
        else:
            food[i] = (l, c, a)


try:
    init()

    playing = True
    while playing:
        # read the keyboard
        try:
            c = stdscr.getkey()
        except:
            c = ''

        if c in 'asdw':
            move(c)
        elif c == 'q':
            playing = False  # Exit the while loop

        check_enemy()
        check_food_status()

        time.sleep(0.03)

        draw()

    stdscr.addstr(maxl//2, maxc//2, "Thanks for playing")
    stdscr.refresh()
    time.sleep(1)
except:
        pass
finally:
    stdscr.clear()
    curses.nocbreak()
    curses.curs_set(1);
    stdscr.keypad(False)
    curses.echo()
    curses.endwin();

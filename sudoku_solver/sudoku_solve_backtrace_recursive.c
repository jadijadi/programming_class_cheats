#include <stdio.h>
#include <string.h>

#include "boxing.h"

char puzzle[9][9] = {
    
	{5, 3, 0, 0, 7, 0, 0, 0, 0},
	{6, 0, 0, 1, 9, 5, 0, 0, 0},
	{0, 9, 8, 0, 0, 0, 0, 6, 0},
	{8, 0, 0, 0, 6, 0, 0, 0, 3},
	{4, 0, 0, 8, 0, 3, 0, 0, 1},
	{7, 0, 0, 0, 2, 0, 0, 0, 6},
	{0, 6, 0, 0, 0, 0, 2, 8, 0},
	{0, 0, 0, 4, 1, 9, 0, 0, 5},
	{0, 0, 0, 0, 8, 0, 0, 7, 9}
};

// keep guessed cells to know after solving the puzzle
char guess[9][9];

void draw()
{
    int ch;
    int i = 0;
    int j = 0;
    
    // window handler
    WINDOW *local_win;
    // creating a window in center of the screen
    local_win = newwin(19, 37, (LINES - 19) / 2, (COLS - 37)/2);
    
    // creating a color with number #2
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    // creating upper part of the table
    box_up(local_win);
    
 	for (i=0; i<9; i++) {
 		for (j=0; j<9; j++) {
            if (j % 3 == 0)
                wattron(local_win, COLOR_PAIR(3) | A_BOLD);
            waddch(local_win, ACS_VLINE);
            wattroff(local_win, COLOR_PAIR(3) | A_BOLD);
            if (guess[i][j])    // solved charactor will be colorfull
                wattron(local_win, COLOR_PAIR(2));
            
            wprintw(local_win, " %d ", puzzle[i][j]);
            wattroff(local_win, COLOR_PAIR(2));
        }
 		waddch(local_win, COLOR_PAIR(3) | ACS_VLINE | A_BOLD);
        if (i < 8){
            if ((i + 1) % 3 == 0)
                wattron(local_win, COLOR_PAIR(3) | A_BOLD);
            box_line(local_win);
            wattroff(local_win, COLOR_PAIR(3) | A_BOLD);
        }
 	}
 	
	// creating lower part of the table
	box_down(local_win);
    
	// refreshing screen
    refresh();
    
    // refreshing local_win
	wrefresh(local_win);
    
    // waiting for F1 to exit
	while((ch = getch()) != KEY_F(1)){}
	
	// destoying memory of local_win
	delwin(local_win);
}

char find_free(int *x, int *y)
{
	for (int i=0; i<9; i++) 
		for (int j=0; j<9; j++)
			if (puzzle[i][j]==0) {
				*x = i;
				*y = j;
				guess[i][j] = 1;
				return 1;
			}
	return 0;
}

char is_valid(int n, int x, int y)
{
	for (int i=0; i<9; i++)
		if (puzzle[x][i] == n || puzzle[i][y] == n)
			return 0;

	int x_square = (x/3) * 3;
	int y_square = (y/3) * 3;
	for (int i=x_square; i<x_square+3; i++) 
		for (int j=y_square; j<y_square+3; j++)
			if (puzzle[i][j] == n)
				return 0;
	return 1;
}

int solve()
{
	int x, y;

	if (find_free(&x, &y) == 0)
		return 1;

	for (int i=1; i<=9; i++)
		if (is_valid(i, x, y)) {
			puzzle[x][y] = i;
			if (solve())
				return 1;
			puzzle[x][y] = 0;
		}
	return 0;
}

int main ()
{
    char prompt[] = "Press F1 to exit\n";
    char err[] = "I can not solve it! wow....\n";
    
    // initiation of curse mode
    initscr();
    
    // disabling buffer for input (do not need to press enter)
    raw();
    
    // getch() wont show charactor
    noecho();
    
    // enabling F(1-12) keys
    keypad(stdscr, TRUE);
    
    // hiding cursur
    curs_set(0);
    
    // enabling color mode
    start_color();
    
    // creating a color with number #1
    init_pair(1, COLOR_RED, COLOR_BLACK);
    
    // adding color #1 attribute to stdscr
    attron(COLOR_PAIR(1));
    mvprintw(2, (COLS - strlen(prompt)) / 2, "%s", prompt);
    
	if (solve())
		draw();
	else
		mvprintw(2, (COLS - strlen(err)) / 2, "%s", err);
    
    // color #1 disable for stdscr at the end.
    attroff(COLOR_PAIR(1));

    // exit from curse mode
    endwin();
    
	return 0;
}

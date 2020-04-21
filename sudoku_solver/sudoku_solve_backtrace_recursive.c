#include <stdio.h>
#include "boxing.h"

char puzzle[9][9] = {
    
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// keep guessed cells to know after solving the puzzle
char guess[9][9];

void draw(WINDOW *win);
char find_free(int *x, int *y);
char is_valid(int n, int x, int y);
int solve();

int main ()
{

    char prompt[] = "Press F1 to exit\n";
    char err[] = "I can not solve it! wow....\n";
    
    WINDOW *win;
    
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
    
    // creating colors #1-5
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);

    // adding color #1 attribute to stdscr
    attron(COLOR_PAIR(1));
    mvprintw(0, (COLS - strlen(prompt)) / 2, "%s", prompt);
    
    win = draw_empty_table();      // draws an empty table
    win = get_input(win, puzzle);  // user can input numbers in the table
    
	if (solve())
		draw(win);  // draws the solved table
	else
		mvprintw(3, (COLS - strlen(err)) / 2, "%s", err);
    
    // color #1 disable for stdscr at the end.
    attroff(COLOR_PAIR(1));

    // exit from curse mode
    endwin();
    
	return 0;
}

void draw(WINDOW *win)
{
    int ch;
    int i = 0;
    int j = 0;
    int ky = 1;
    int kx = 2;
    
 	for (i=0, ky=1; i<9; i++, ky+=2) {
 		for (j=0, kx=2; j<9; j++, kx+=4) {
            if (guess[i][j]){    // solved charactor will be colorfull
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, ky, kx, "%d", puzzle[i][j]);
            }
            else{
                wattron(win, COLOR_PAIR(5) | A_BOLD);
                mvwprintw(win, ky, kx, "%d", puzzle[i][j]);
            }
            wattroff(win, COLOR_PAIR(2) | COLOR_PAIR(5) | A_BOLD);
        }
 	}
    
    // refreshing win
    wrefresh(win);
    
	// refreshing screen
    refresh();
    
    // waiting for F1 to exit
	while((ch = getch()) != KEY_F(1)){}
	
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
	// destoying memory of local_win
	delwin(win);
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

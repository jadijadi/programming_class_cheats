#include "boxing.h"

void box_up(WINDOW* win){
    wattron(win, COLOR_PAIR(3) | A_BOLD);
    waddch(win, ACS_ULCORNER);
    for (int k = 0; k < 8; ++k){
        waddch(win, ACS_HLINE);
        waddch(win, ACS_HLINE);
        waddch(win, ACS_HLINE);
        waddch(win, ACS_TTEE);
    }
    waddch(win, ACS_HLINE);
    waddch(win, ACS_HLINE);
    waddch(win, ACS_HLINE);
    waddch(win, ACS_URCORNER);
    wattroff(win, COLOR_PAIR(3) | A_BOLD);
}

void box_down(WINDOW* win){
    wattron(win, COLOR_PAIR(3) | A_BOLD);
    waddch(win, ACS_LLCORNER);
    for (int k = 0; k < 8; ++k){
        waddch(win, ACS_HLINE);
        waddch(win, ACS_HLINE);
        waddch(win, ACS_HLINE);
        waddch(win, ACS_BTEE);
    }
    waddch(win, ACS_HLINE);
    waddch(win, ACS_HLINE);
    waddch(win, ACS_HLINE);
    waddch(win, ACS_LRCORNER);
    wattroff(win, COLOR_PAIR(3) | A_BOLD);
}

void box_line(WINDOW* win){
    waddch(win, COLOR_PAIR(3) | ACS_LTEE | A_BOLD);
    for (int k = 0; k < 8; ++k){
        waddch(win, ACS_HLINE);
        waddch(win, ACS_HLINE);
        waddch(win, ACS_HLINE);
        if ((k+1) % 3 == 0)
            waddch(win, COLOR_PAIR(3) | ACS_PLUS | A_BOLD);
        else
            waddch(win, ACS_PLUS);
    }
    waddch(win, ACS_HLINE);
    waddch(win, ACS_HLINE);
    waddch(win, ACS_HLINE);
    waddch(win, COLOR_PAIR(3) | ACS_RTEE | A_BOLD);
}


WINDOW *draw_empty_table(){
    
    int i = 0;
    int j = 0;
    
    // window handler
    WINDOW *local_win;
    
    // creating a window in center of the screen
    local_win = newwin(19, 37, (LINES - 19) / 2, (COLS - 37)/2);

    // creating upper part of the table
    box_up(local_win);
    
 	for (i=0; i<9; i++) {
 		for (j=0; j<9; j++) {
            if (j % 3 == 0)
                wattron(local_win, COLOR_PAIR(3) | A_BOLD);
            waddch(local_win, ACS_VLINE);
            wattroff(local_win, COLOR_PAIR(3) | A_BOLD);
            wprintw(local_win, "   ");
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
    
    return local_win;
}

WINDOW *get_input(WINDOW* win, char puzzle[][9]){
    
    int input;
    int y = 1;
    int x = 2;
    int iindx = 0;
    int jindx = 0;
    
    int or = y;
    int oc = x;
    
    char prompt1[] = "Enter the sudoku and press (F2) to solve\n";
    char prompt2[] = "default value is 0\n";
    WINDOW *tmp;
    tmp = newwin(2, strlen(prompt1), 1, (COLS - strlen(prompt1)) / 2);
    wprintw(tmp, "%s", prompt1);
    wprintw(tmp, "%s", prompt2);
    wrefresh(tmp);

    mvwchgat(win, y, x, 1, A_BLINK, 4, NULL);
    wrefresh(win);
    while ((input = getch()) != KEY_F(2)){
        or = y;
        oc = x;
        switch(input){
            case KEY_UP:
                ((y-=2) == -1) ? y = 17 : y;
                (iindx-- == -1) ? iindx = 9 : iindx;
                break;
            case KEY_DOWN:
                ((y+=2) == 19) ? y = 1 : y;
                (iindx++ == 10) ? iindx = 0 : iindx;
                break;
            case KEY_RIGHT:
                ((x+=4) == 38) ? x = 2 : x;
                (jindx++ == 10) ? jindx = 0 : jindx;
                break;
            case KEY_LEFT:
                ((x-=4) == -2) ? x = 34 : x;
                (jindx-- == -1) ? jindx = 9 : jindx;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
                mvwaddch(win, y, x, input);
                wrefresh(win);
                puzzle[iindx][jindx] = (input - 48);
                break;
            default:
                break;
        }
        mvwchgat(win, or, oc, 1, A_NORMAL, 5, NULL);
        mvwchgat(win, y, x, 1, A_BLINK, 4, NULL);
        wrefresh(win);
    }
    
    wborder(tmp, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(tmp);
    delwin(tmp);
    
    return win;
}

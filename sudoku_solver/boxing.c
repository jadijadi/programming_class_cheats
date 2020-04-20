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

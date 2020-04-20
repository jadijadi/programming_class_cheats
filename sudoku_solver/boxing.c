#include "boxing.h"

void box_up(WINDOW* win){
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
}

void box_down(WINDOW* win){
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
}

void box_line(WINDOW* win){
    waddch(win, ACS_LTEE);
    for (int k = 0; k < 8; ++k){
        waddch(win, ACS_HLINE);
        waddch(win, ACS_HLINE);
        waddch(win, ACS_HLINE);
        waddch(win, ACS_PLUS);
    }
    waddch(win, ACS_HLINE);
    waddch(win, ACS_HLINE);
    waddch(win, ACS_HLINE);
    waddch(win, ACS_RTEE);
}



    

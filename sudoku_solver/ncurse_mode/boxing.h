#ifndef _BOXING_H
#define _BOXING_H

#include <ncurses.h>
#include <string.h>

extern void box_up(WINDOW *win);
extern void box_down(WINDOW *win);
extern void box_line(WINDOW *win);
extern WINDOW *draw_empty_table();
extern WINDOW *get_input(WINDOW *win, char puzzle[][9]);

#endif // _BOXING_H

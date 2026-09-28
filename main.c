// gcc -Wall -Wextra -Werror -o "resize" resize.c -lcurses
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

int main(void) {
	int nlines = 0;
    int ncols = 0;
	int key = 0;

	initscr();
	noecho();
	cbreak();
	curs_set(0);

	clear();
	refresh();

	getmaxyx(stdscr, nlines, ncols);
	WINDOW *win = newwin(nlines, ncols, 0, 0);
	keypad(win, TRUE);
	box(win, 0, 0);
	mvwaddstr(win, 0, 2, "box");
	wrefresh(win);

	while((key = wgetch(win)) != 27) {
		wmove(win, 2, 2);
		if(key == KEY_RESIZE) {
			resize_term(LINES, COLS);
			clear();
			refresh();
			getmaxyx(stdscr, nlines, ncols);
			wresize(win, nlines, ncols);
			werase(win);
			box(win, 0, 0);
			mvwaddstr(win, 0, 2, "box");
			wrefresh(win); 
		}
		else {
			waddch(win, key);
			wrefresh(win); 
		}
	}
	curs_set(1);
	delwin(win);
	endwin();
	return EXIT_SUCCES;
}

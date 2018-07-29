#include <curses.h>
#include <stdlib.h>
#include <dirent.h>
#include "fn.h"

#define COL 34
#define ROW 22

void show_dir(WINDOW *win, char *path, int *last){
    DIR *dir;
    struct dirent *de;
    int y, x;

    if((dir = opendir(path)) == NULL){
        wprintw(win, "wrong way to dir!");
        wrefresh(win);
    }
    
    while(de = readdir(dir)){
        getyx(win, y, x);
        if(y == (ROW - 1)){
            wmove(win, 0, 1);
            wclear(win);
        }
        wprintw(win, " %s\n", de->d_name);
    }
    *last = y;
    wrefresh(win);
    closedir(dir);
}

void show_focus(WINDOW *win, int index, int max){
    for(int i = 0; i <= max; i++)
    {
        wmove(win, i, 0);
        if(i == index)
            wprintw(win, ">");
        else wprintw(win, " ");
    }
}

void clear_focus(WINDOW *win){
    for(int i = 0; i < COL; i++)
    {
        wmove(win, i, 0);
        wprintw(win, " ");
    }
    wrefresh(win);
}

int jump_dir(WINDOW *win, int index){
    int last_row;
    char *buff;

    //???stat(d_name);

    //chdir(buff);

    show_dir(win, ".", &last_row);

    return last_row;
}

int main(int argc, char const *argv[]){
    WINDOW *wnd;
    WINDOW *win[2];

    initscr();

    noecho();
    curs_set(false);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    wnd = newwin(24, 80, 0, 0);
    wbkgd(wnd, COLOR_PAIR(1));

    for(int i = 1; i >= 0; i--){
        win[i] = derwin(wnd, ROW, COL, 1, 3 + i*39);
        wbkgd(win[i], COLOR_PAIR(2));
        wrefresh(win[i]);

        keypad(win[i], true);
    }

    

    char ch;
    int RUN = 1, focus = 0, y, x, point_row[2] = {0, 0}, last_row[2] = {0, 0};


        show_dir(win[0], "/", &last_row[0]);
        show_dir(win[1], ".", &last_row[1]);

    while(RUN){
        

        show_focus(win[focus], point_row[focus], last_row[focus]);
        wrefresh(win[focus]);

        ch = wgetch(win[focus]);
        getyx(win[focus], y, x);

        //wprintw(win[0],"%d", (int)ch);
        //wprintw(win[focus], "%d\n", point_win[focus]);


        switch (ch){
            case 10:
                //last_row[focus] = jump_dir(win[focus], point_row[focus]);
                break;
            case 3:
                if(point_row[focus] == 0)
                    point_row[focus] = last_row[focus];
                else point_row[focus]--;
                break;
            case 2:
                if(point_row[focus] == last_row[focus])
                    point_row[focus] = 0;
                else point_row[focus]++;
                break;
            case 4:
                clear_focus(win[focus]);
                focus = 0;
                break;
            case 5:
                clear_focus(win[focus]);
                focus = 1;
                break;
            default:
                break;
        }
    }

    delwin(win[0]);
    delwin(win[1]);
    delwin(wnd);

    endwin();
    exit(EXIT_SUCCESS);
    return 0;
}

#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "fn.h"

#define MISS 0
#define OPEN 1
#define SAVE 2
#define EXIT 3

#define ROW 22
#define COL 78

int RUN = 1;
char path[256] = {};
FILE *fd;

void read_to_win(WINDOW * win);

void move_in_win(WINDOW *win, int y, int x, char step)
{
     switch ((int)step)
        {   
            case 'a':
            case KEY_LEFT:
                if(x == 0)
                    if(y == 0)
                        wmove(win, ROW - 1, COL - 1);
                    else wmove(win, y - 1, COL - 1);
                else wmove(win, y, x-1);
                break;
            case 'd':
            case KEY_RIGHT:
                if(x == COL - 1)
                    if(y == ROW - 1)
                        wmove(win, 0, 0);
                    else wmove(win, y + 1, 0);
                else wmove(win, y, x + 1);
                break;
            case 'w':
            case KEY_UP:
                if(y == 0)
                    wmove(win, ROW - 1, x);
                else wmove(win, y - 1, x);
                break;
            case 's':
            case KEY_DOWN:
                if(y == ROW - 1)
                    wmove(win, 0, x);
                else wmove(win, y + 1, x);
                break;
            case 10:
                if(y == (ROW-1))
                    wmove(win, 0, 0);
                else wmove(win, y + 1, 0);
            default:
                break;
        }
}

int button_OSE(int y, int x)
{
    if(y == (ROW+1))
    {
        if((x > 14)&&(x < 19)) return OPEN;
        if((x > 39)&&(x < 44)) return SAVE;
        if((x > 64)&&(x < 69)) return EXIT;
    }
    return MISS;
}

void mouse_click(WINDOW *win, int target)
{
    char ch;
    int y, x, i = 0;
    getyx(win, y, x);
    
    switch (target)
    {
        case OPEN:
            wclear(win);
            wprintw(win, "in path to file: ");
            
            while((ch = wgetch(win)) != 10){
                path[i] = ch;
                i++;
            }
            
            if((fd = fopen(path, "r")) == NULL){
                wclear(win);
                wprintw(win, "fail!\n wrong path: %s", path);
            }else{
                wclear(win);
                read_to_win(win);
                fclose(fd);
            }
            break;
        case SAVE:
            if(fd){
                fd = fopen (path, "a");
                for (int l = 0; l < ROW - 1; l++) {
                    for (int i = 0; i < COL - 1; i++)
                        putc (mvwinch (win, l, i) & A_CHARTEXT, fd);
                    putc('\n', fd);
                }
                fclose(fd);
                wmove(win, 0, 0);
            }else{
                wmove(win, 0, 0);
                wprintw(win, "fail!\nyou didn`t open file!");
            }
            break;
        case EXIT:
            RUN = 0;
            break;
        default:
            break;
    }
}

void read_to_win(WINDOW * win){
    if(fd){
        char buff[77];
        int y, x;
    
        wmove(win, 0, 0);
    
        while(fgets(buff, (COL-1), fd) != NULL){
            wprintw(win, "%s", buff);
            
            getyx(win, y, x);
            if(y == (ROW-1)){
                wclear(win);
                wmove(win, 0, 0);
            }else
                wmove(win, y + 1, 0);
        }
        wrefresh(win);
    }
}

int main(int argc, char ** argv)
{
    WINDOW *wnd;
    WINDOW *wnd_txt;
    MEVENT event;

    initscr();
    
    start_color();
    init_pair(1, COLOR_RED, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
   
    wnd = newwin(24, 80, 0, 0);
    wbkgd(wnd, COLOR_PAIR(1));
    wmove(wnd, 23, 15);
    wprintw(wnd, "OPEN");
    wmove(wnd, 23, 40);
    wprintw(wnd, "SAVE");
    wmove(wnd, 23, 65);
    wprintw(wnd, "EXIT");
    wrefresh(wnd);

    wnd_txt = derwin(wnd, ROW, COL, 1, 1);
    wbkgd(wnd_txt, COLOR_PAIR(2));
    wrefresh(wnd_txt);

    //open file for terminal
    if(argc == 2){
        strcpy(path, argv[1]);
        fd = fopen(path, "r");
        read_to_win(wnd_txt);
        fclose(fd);
    }

    keypad(wnd_txt, true);

    mousemask(BUTTON1_CLICKED, NULL);
    
    char ch;
    int y, x;
    
    while(RUN){
        getyx(wnd_txt, y, x);
        if((y == (ROW-1))&&(x == (COL-1))) wmove(wnd_txt, 0, 0);

        ch = wgetch(wnd_txt);

        move_in_win(wnd_txt, y, x, ch);
        
        //work with mouse
        getmouse(&event);
        mouse_click(wnd_txt, button_OSE(event.y, event.x));        
    }

    delwin(wnd_txt);
    delwin(wnd);

    endwin();
    exit(EXIT_SUCCESS);
}

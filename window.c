
#include <sys/ioctl.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

struct fields{
	char my_field[10][10];
	char opponent_field[10][10];
	char status[256];
};

int painter(struct fields fld){
    WINDOW * mainW;
    WINDOW * wndusr;
    WINDOW * wndoppos; 
    initscr();
    curs_set(FALSE);
    start_color();
    refresh();
    init_pair(5, COLOR_YELLOW, COLOR_YELLOW);//изначальный желтый фон
    init_pair(1, COLOR_CYAN, COLOR_CYAN);//изначальный фон
    init_pair(4, COLOR_RED, COLOR_RED);//фон ошибки
    init_pair(3, COLOR_BLUE, COLOR_BLUE);//корабль
    init_pair(2, COLOR_BLACK, COLOR_BLACK);//корабль подбит
    mainW = newwin(20, 64, 2, 2);
    wndusr = newwin(10, 20, 8, 8);
    wndoppos = newwin(10, 20, 8, 40);
    wbkgd(mainW, COLOR_PAIR(5));
    wrefresh(mainW);
    wbkgd(wndusr, COLOR_PAIR(1));
    wbkgd(wndoppos, COLOR_PAIR(1));
   for(int i=0; i<10; i++){
        for(int t=0; t<10; t++){
            switch (fld.my_field[i][t]){
                case '0': {
                            wattron (wndusr, COLOR_PAIR(1));
                            wprintw(wndusr, "  ", fld.my_field[i][t]);
                            wattroff (wndusr, COLOR_PAIR(1));
                            };break;
                case '1': {
                            wattron (wndusr, COLOR_PAIR(3));
                            wprintw(wndusr, "  ", fld.my_field[i][t]);
                            wattroff (wndusr, COLOR_PAIR(3));
                           };break;
                case '2': {
                            wattron (wndusr, COLOR_PAIR(2));
                            wprintw(wndusr, "  ", fld.my_field[i][t]);
                            wattroff (wndusr, COLOR_PAIR(2));
                           };break;
                default:{
                            wattron (wndusr, COLOR_PAIR(4));
                            wprintw(wndusr, "  ", fld.my_field[i][t]);
                            wattroff (wndusr, COLOR_PAIR(4));
                        }
            }
        }
    }

    wrefresh(wndusr);

   for(int i=0; i<10; i++){
        for(int t=0; t<10; t++){
            switch (fld.opponent_field[i][t]){
                case '0': {
                            wattron (wndoppos, COLOR_PAIR(1));
                            wprintw(wndoppos, "  ", fld.opponent_field[i][t]);
                            wattroff (wndoppos, COLOR_PAIR(1));
                            };break;
                case '1': {
                            wattron (wndoppos, COLOR_PAIR(3));
                            wprintw(wndoppos, "  ", fld.opponent_field[i][t]);
                            wattroff (wndoppos, COLOR_PAIR(3));
                           };break;
                case '2': {
                            wattron (wndoppos, COLOR_PAIR(2));
                            wprintw(wndoppos, "  ", fld.opponent_field[i][t]);
                            wattroff (wndoppos, COLOR_PAIR(2));
                           };break;
                default:
                        {
                            wattron (wndoppos, COLOR_PAIR(4));
                            wprintw(wndoppos, "  ", fld.opponent_field[i][t]);
                            wattroff (wndoppos, COLOR_PAIR(4));
                        }
            }
        }
    }
    
    wrefresh(wndoppos);
    delwin(mainW);
    delwin(wndusr);
    delwin(wndoppos);
    getch();
    endwin();
    return 1;

}


/*int main()
{
   struct fields fld;
   for(int i=0; i<10; i++){
        for(int t=0; t<10; t++){
            fld.my_field[i][t]='0';
            if(i==3&&(t==5||t==6||t==7)) fld.my_field[i][t]='1';
            if(i==3&&(t==8)) fld.my_field[i][t]='4';
        }
    }

    for(int i=0; i<10; i++){
        for(int t=0; t<10; t++){
            fld.opponent_field[i][t]='0';
            if(i==3&&(t==5||t==6||t==7)) fld.opponent_field[i][t]='1';
        }
    }  
    printf("%c", fld.my_field[2][5]); 
    while(1){
    painter(fld);
    }
    return 0;
}*/






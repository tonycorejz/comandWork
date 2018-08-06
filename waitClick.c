#include "head.h"


int *  wait_click(int win_number ){
    static int mas[2];
    keypad(stdscr, 1);
    mousemask(BUTTON1_CLICKED, NULL);
    move(2,2);
    refresh();
   
    switch(win_number){
        case 0: { while((mas[1]<8||mas[1]>27||mas[0]<8||mas[0]>17)&&wgetch(stdscr)==KEY_MOUSE){
                    MEVENT event;
                    getmouse(&event);
                    move(0, 0);
                    mas[0]=event.y;
                    mas[1]=event.x;
                    refresh();
                }
                mas[1]-=8;
                mas[1]/=2;
                mas[0]-=8;
                
        };break;
        case 1:{    while((mas[1]<40||mas[1]>59||mas[0]<8||mas[0]>17)&&wgetch(stdscr)==KEY_MOUSE){
                        MEVENT event;
                        getmouse(&event);
                        move(0, 0);
                        mas[0]=event.y;
                        mas[1]=event.x;
                        refresh();
                    }
                   mas[1]-=40;
                   mas[1]/=2;
                   mas[0]-=8;
                   
                };break;
        default:{ 
                    endwin();
                    printf("wrong number of Windows");
                    return 0;
                }
    }
 
return mas; 

}

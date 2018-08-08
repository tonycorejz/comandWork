#include "head.h"

int main (int argc, char *argv[])
{
    struct fields ships_fields;
    struct connect_struct  con_st;
    char  opponent_addr[256];
    int sock_id;
    int auto_reposition=0;
	
    strcpy(opponent_addr,"");
    if(argc>1)
	    for(int i=1;i<argc;i++){
            printf("%s\n",argv[i]);
            if(!strcmp(argv[i],"-help")){
                // printf("%s\n","Помощь спешит!");
                printf("%s\n","ключ -addr <IP адрес оппонента> (формат 192.168.2.138)\n ключ - -ar - автоматическая расстановка кораблей");
                return 0;
            }
			//if(!check_valid_addr[strcmp(argv[i+1]))
            if(!strcmp(argv[i],"-addr")){
                strcpy(opponent_addr,argv[i+1]);
                // printf("%s %s\n",argv[i+1],"IP адрес не соответсвует формату 192.168.2.138");
			}
            if(!strcmp(argv[i],"-ar")){
               auto_reposition=1;
			}
        }
    // sleep(2);
    if(auto_reposition)
        ships_fields=set_rand_ships(ships_fields);// автоматическая расстановка кораблей на поле
    con_st=connect_est (opponent_addr);
    printf ("Подключен %s ход %i\n",con_st.ip_port,con_st.stroke);
    //инициализируем окно ncurses
    initscr();
    start_color();
    keypad (stdscr, TRUE);
    if(!auto_reposition)
	    ships_fields=set_ships_by_hand(ships_fields);// ручная расстановка кораблей на своем 
    window(ships_fields);
    sleep(2);
    battle(ships_fields,con_st.sock_id,con_st.stroke);
    sleep(2);
    endwin();// разрушаем окно ncurses

    return 0;
}

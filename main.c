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
            if(!strcmp(argv[i],"-help")){
                // printf("%s\n","Помощь спешит!");
                printf("%s\n","ключ -addr <IP адрес оппонента> (формат 192.168.2.138)\n<    -addr 127.0.0.1 > подключение с локальному серверу\nключ - -ar - автоматическая расстановка кораблей");
                return 0;
            } else  if(!strcmp(argv[i],"-addr")){
                        strcpy(opponent_addr,argv[i+1]);
			i++;
                        // printf("%s %s\n",argv[i+1],"IP адрес не соответсвует формату 192.168.2.138");
		    } else  if(!strcmp(argv[i],"-ar")){
                               auto_reposition=1;
			    }else 
			    {  
			    printf("Недопустимый ключ запуска. Для помощи используйте -help\n");
			    return 0;
			    }
        }
    // sleep(2);
    if(auto_reposition)
        ships_fields=set_rand_ships(ships_fields);// расставили корабли на своем поле
    con_st=connect_est (opponent_addr);
    printf ("Подключен %s\n",con_st.ip_port);
    //инициализируем окно ncurses
    initscr();
    start_color();
    keypad (stdscr, TRUE);
    if(!auto_reposition)
	    ships_fields=set_ships_by_hand(ships_fields);// расставили корабли на своем поле
    window(ships_fields);
    sleep(2);
    battle(ships_fields,con_st.sock_id,con_st.stroke);
    sleep(2);
    endwin();// разрушаем окно ncurses

    return 0;
}

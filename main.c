#include "head.h"

int main (int argc, char *argv[])
{
    struct fields ships_fields;
     char  opponent_addr[256];
     int sock_id;
	
     strcpy(opponent_addr,"");
     if(argc>1)
	for(int i=1;i<argc;i++)
	{
		printf("%s\n",argv[i]);
		if(!strcmp(argv[i],"-help")){
		  printf("%s\n","Помощь спешит!");
		return 0;
		}
		
	}
    sleep(2);
  // sock_id=connect (opponent_addr);

   //инициализируем окно ncurses
      initscr();
      start_color();
      keypad (stdscr, TRUE);

  // ships_fields=reposition(ships_fields);// расставили корабли на своем поле

   // battle(ships_fields);
//sleep(2);
    endwin();// разрушаем окно ncurses
return 0;
}

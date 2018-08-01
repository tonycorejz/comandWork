#include "head.h"

int main (int argc, char *argv[])
{
    struct fields ships_fields;
     char  opponent_addr[256];
     int sock_id;

	strcpy(opponent_addr,"");

  // sock_id=connect (opponent_addr);

   //инициализируем окно ncurses
      initscr();
      start_color();
      keypad (stdscr, TRUE);

  // ships_fields=reposition(ships_fields);// расставили корабли на своем поле

   // battle(ships_fields);
sleep(2);
    endwin();// разрушаем окно ncurses
return 0;
}

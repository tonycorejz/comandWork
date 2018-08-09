#include "head.h"

#define GOT_SHOT 1

/* Функция check выполняет проверку победил ли игрок
 * если находит не побитое поле возвращает 1, для 
 * продолжения игры
 * */
int check(char opponent_field[10][10])
{
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(opponent_field[i][j] == 1)
				return 1;
		}
	}		
	return 0;
}

int milkis(char field[10][10], int buf_coord[7])
{
    int x = buf_coord[0];
    int y = buf_coord[1];

    if((field[x][y - 1] == 1 && y > 0) ||
        (field[x][y + 1] == 1 && y < 9) ||
        (field[x - 1][y] == 1 && x > 0) ||
        (field[x + 1][y] == 1 && x < 9)){
        return 1;
    }else{
        return 0;
    }

}

/* Функция battle реализует сам игровой процесс
 * Морского боя. На вход получает структуру с полями
 * игроков, завершается когда один из игроков выйграл
 * */
int battle(struct fields field, int sock_fd, int stroke)
{
    int repeat_move; 
    int buf_coord[7];
    int for_milkis;
    int mas[16];
    buf_coord[4] = 0;
    int x, y;
    int x_first, x_last, y_first, y_last;

    int *b; //для получения координат от waitClick
    while(1){
		/* Получаем от второго игрока координаты ячейки
		 * отправляем второму игроку на проверку  
		 * Ожидаем сообщения от второго игрока
		 * получаем либо 0 - пусто, либо 1 - есть корабль
		 * соответственно ставится ничего или 2 (подбил)
		 */
        if(stroke == 1){ //игрок атакует
            repeat_move = 1;
            strcpy(field.status, "You move"); 
            window(field);
            while(repeat_move == GOT_SHOT){
                b = wait_click(1);
                buf_coord[0] = b[0];
                buf_coord[1] = b[1];
                send(sock_fd, buf_coord, sizeof(buf_coord), 0);
                recv(sock_fd, buf_coord, sizeof(buf_coord), 0);
/*                if(buf_coord[4] == 7){
                    strcpy(field.status, "Ship has been killed");
                    window(field);
                    sleep(1);
                    strcpy(field.status, "You move");
                    window(field);
                    if(buf_coord[0] >= buf_coord[5]){
                        x_first = buf_coord[5];
                        x_last = buf_coord[0];
                    }else{
                        x_first = buf_coord[0];
                        x_last = buf_coord[5];
                    }
                    if(buf_coord[1] >= buf_coord[6]){
                        y_first = buf_coord[6];
                        y_last = buf_coord[1];
                    }else{
                        y_first = buf_coord[1];
                        y_last = buf_coord[6];
                    }
                    while(y_first <= y_last){ //Двигаемся вправо
                        if(y_first < y_last){
                            field.opponent_field[x_first - 1][y_first] = 3;
                            y_first++;
                        }
                        if(y_first == y_last){
                            field.opponent_field[x_first - 1][y_first] = 3;
                            field.opponent_field[x_first - 1][y_first + 1] = 3;
                            break;
                        }

                    }
                    while(x_first <= x_last){ //Двигаемся вниз
                        if(x_first < x_last){
                            field.opponent_field[x_first - 1][y_first + 1] = 3;
                            x_first++;
                        }
                        if(x_first == x_last){
                            field.opponent_field[x_first - 1][y_first + 1] = 3;
                            field.opponent_field[x_first][y_first + 1] = 3;
                            field.opponent_field[x_first + 1][y_first + 1] = 3;
                            break;
                        }
                    }
                    y_first = buf_coord[1];
                    while(y_last >= y_first){ //Двигаемся влево
                        if(y_last > y_first){
                            field.opponent_field[x_last + 1][y_last] = 3;
                            y_last--;
                        }
                        if(y_last == y_first){
                            field.opponent_field[x_last + 1][y_last] = 3;
                            field.opponent_field[x_last + 1][y_last - 1] = 3;
                            break;
                        }
                    }
                    x_first = buf_coord[0];
                    while(x_last >= x_first){ //Двигаемся вверх
                        if(x_last > x_first){
                            field.opponent_field[x_last][y_last - 1] = 3;
                            field.opponent_field[x_last - 1][y_last - 1] = 3;
                            x_last--;
                        }
                        if(x_last == x_first){
                            field.opponent_field[x_last - 1][y_last - 1] = 3;
                            field.opponent_field[x_last][y_last - 1] = 3;
                            break;
                        }
                    }
                    
                    buf_coord[4] = 0;

                }
*/
                switch(buf_coord[2]){
                    case 0:
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 3;
                        window(field);
                        repeat_move = 0;
                        break;

                    case 1:
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 2;
                        if(buf_coord[4] == 7){
                            strcpy(field.status, "Ship has been killed");
                            window(field);
                            sleep(1);
                            strcpy(field.status, "You move");
                            window(field);
                            buf_coord[4] = 0;
                        }
                        window(field);
                        break;

                    case 2:
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 4;
                        window(field);
                        usleep(500000);
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 2;
                        window(field);
                        break;

                    case 3:
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 4;
                        window(field);
                        usleep(500000);
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 3;
                        window(field);
                        break;
				
                    default:
                        printf("Что-то пошло не так");
                        break;
                }
                if(buf_coord[3] == 0)
                    break;
            }
        }else{  //игрок принимает атаку
            /* Получаем ячейку куда был выстрел 
             * Ставим в свой массив, если было 1 то ставится 2
             * если 0 то ставится 3, так же обрабатывается ошибка
             * */
            repeat_move = 1;
            strcpy(field.status, "Opponent's move"); 
            window(field);
            while(repeat_move == GOT_SHOT){
                recv(sock_fd, buf_coord, sizeof(buf_coord), 0);
                switch(field.my_field[buf_coord[0]][buf_coord[1]]){
                    case 0:
                        field.my_field[buf_coord[0]][buf_coord[1]] = 3;
                        window(field);
                        buf_coord[2] = 0;
                        repeat_move = 0;
                        break;

                    case 1:
                        field.my_field[buf_coord[0]][buf_coord[1]] = 2;
                        window(field);
                        
                        for_milkis = milkis(field.my_field, buf_coord);
                        if(for_milkis == 0){
                            x = buf_coord[0];
                            y = buf_coord[1];
                            if(field.my_field[x][y - 1] == 2){
                                while(field.my_field[x][y - 1] == 2){
                                    y--;
                                }
                            }else{
                                while(field.my_field[x][y + 1] == 2){
                                    y++;
                                }
                            }
                            if(field.my_field[x - 1][y] == 2){
                                while(field.my_field[x - 1][y] == 2){
                                    x--;
                                }
                            }else{
                                while(field.my_field[x + 1][y] == 2){
                                    x++;
                                }
                            }
                            buf_coord[4] = 7;
                        }

                        buf_coord[2] = 1;
                        buf_coord[3] = check(field.my_field);
                        buf_coord[5] = x;
                        buf_coord[6] = y;
                        if(buf_coord[3] == 0)
                            repeat_move = 0;
                        break;

                    case 2:
                        buf_coord[2] = 2;
                        break;

                    case 3:
                        buf_coord[2] = 3;
                        break;
                    
                    default:
                        printf("Что-то пошло не так");
                        break;
                }
                
                send(sock_fd, buf_coord, sizeof(buf_coord), 0);
                if(buf_coord[4] == 7){
                    buf_coord[4] = 0;
                }
            }
        }

        if(buf_coord[3] == 0){
            if(stroke == 1){
                strcpy(field.status, "You win");
                window(field);
                sleep(10);
                return 0;
            }else{
                strcpy(field.status, "You lose");
                window(field);
                sleep(10);
                return 1;
            }
        }

        stroke = stroke ^ 1;
    }
}

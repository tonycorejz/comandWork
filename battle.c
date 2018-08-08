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

/* Функция battle реализует сам игровой процесс
 * Морского боя. На вход получает структуру с полями
 * игроков, завершается когда один из игроков выйграл
 * */
int battle(struct fields field, int sock_fd, int stroke)
{
//    struct sockaddr_in client;
//    socklen_t addrlen = sizeof(client);

//    client.sin_family = AF_INET;
//    client.sin_port = htons(8679);    
    
    int repeat_move;
    int buf_coord[4];
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
//                sendto(sock_fd, buf_coord, sizeof(buf_coord), 0, (struct sockaddr*)&client, addrlen);
//                recvfrom(sock_fd, buf_coord, sizeof(buf_coord), 0, (struct sockaddr*)&client, &addrlen);
                send(sock_fd, buf_coord, sizeof(buf_coord), 0);
                recv(sock_fd, buf_coord, sizeof(buf_coord), 0);
                if(buf_coord[3] == 0)
                    break;
                switch(buf_coord[2]){
                    case 0:
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 3;
                        window(field);
                        repeat_move = 0;
                        break;

                    case 1:
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 2;
                        window(field);
                        break;

                    case 2:
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 4;
                        window(field);
                        sleep(1);
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 2;
                        window(field);
                        break;

                    case 3:
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 4;
                        window(field);
                        sleep(1);
                        field.opponent_field[buf_coord[0]][buf_coord[1]] = 3;
                        window(field);
                        break;
				
                    default:
                        printf("Что-то пошло не так");
                        break;
                }
            }
        }else{  //игрок принимает атаку
            /* Получаем ячейку куда был выстрел 
             * Ставим в свой массив, если было 1 то ставится 2
             * если 0 то ЧТО-ТО
             * */
            repeat_move = 1;
            strcpy(field.status, "Opponent's move"); 
            window(field);
            while(repeat_move == GOT_SHOT){
//                recvfrom(sock_fd, buf_coord, sizeof(buf_coord), 0, (struct sockaddr*)&client, &addrlen);
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
                        buf_coord[2] = 1;
                        buf_coord[3] = check(field.my_field);
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
//                sendto(sock_fd, buf_coord, sizeof(buf_coord), 0, (struct sockaddr*)&client, addrlen);
                send(sock_fd, buf_coord, sizeof(buf_coord), 0);
            }
        }

        if(buf_coord[3] == 0){
            if(stroke == 1)
                return 0;
            else
                return 1;
        }

        stroke = stroke ^ 1;
    }
}

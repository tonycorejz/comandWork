#include "head.h"

#define GOT_SHOT 1

void print(char field[10][10])
{
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			printf("%d ", field[i][j]);
		}
		printf("\n");
	}
}

/* Заполняю массивы для проверки, при совмещении
 * с основным проектом удалю
 * */
void fill(int sock_fd, int stroke)
{
	struct fields field;

	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			field.my_field[i][j] = 0;
			field.opponent_field[i][j] = 0;
		}
	}
	//5
	field.my_field[2][2] = 1;		
	field.my_field[2][3] = 1;		
	field.my_field[2][4] = 1;		
	field.my_field[2][5] = 1;		
	field.my_field[2][6] = 1;		
	//4
	field.my_field[3][9] = 1;		
	field.my_field[4][9] = 1;		
	field.my_field[5][9] = 1;		
	field.my_field[6][9] = 1;		
	//3
	field.my_field[5][7] = 1;		
	field.my_field[6][7] = 1;		
	field.my_field[7][7] = 1;		
	//2
	field.my_field[5][1] = 1;		
	field.my_field[6][1] = 1;		
	//1
	field.my_field[8][2] = 1;		

	//5
	field.opponent_field[0][0] = 1;
	field.opponent_field[1][0] = 1;
	field.opponent_field[2][0] = 1;
	field.opponent_field[3][0] = 1;
	field.opponent_field[4][0] = 1;
	//4
	field.opponent_field[5][2] = 1;
	field.opponent_field[6][2] = 1;
	field.opponent_field[7][2] = 1;
	field.opponent_field[8][2] = 1;
	//3
	field.opponent_field[2][4] = 1;
	field.opponent_field[2][5] = 1;
	field.opponent_field[2][6] = 1;
	//2
	field.opponent_field[5][5] = 1;
	field.opponent_field[6][5] = 1;
	//1
	field.opponent_field[7][8] = 1;
	
	battle(field, sock_fd, stroke);
}

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
	print(field.my_field);
	printf("\n");
	print(field.opponent_field);
	
	int x, y;
    int repeat_move;
    int buf_coord[4];
    while(1){
		//Ход игрока 
		/* Получаем от игрока координаты ячейки
		 * отправляем второму игроку на проверку  
		 * Ожидаем сообщения от второго игрока
		 * получаем либо 0 - пусто, либо 1 - есть корабль
		 * соответственно ставится ничего или 2 (подбил)
		 */
        if(stroke == 1){
            repeat_move = 1;
            //проверка на атакующий или нет 
            while(repeat_move == GOT_SHOT){
                printf("\nTBoe :");
	    	    scanf("%d %d", &x, &y); //функция вызова координат 
                //Шлю координаты
		        buf_coord[0] = x;
                buf_coord[1] = y;
                send(sock_fd, buf_coord, sizeof(buf_coord), 0);
                //Получаю ответ второго игрока о состоянии этой ячейки 
                recv(sock_fd, buf_coord, sizeof(buf_coord), 0);
                if(buf_coord[3] == 0)
                    break;
                x = buf_coord[0];
                y = buf_coord[1];
                switch(buf_coord[2]){
    			    case 0:
	    			    //Функция выставления точки 
		    		    field.opponent_field[x][y] = 3;
                        repeat_move = 0;
			        	break;

    			    case 1:
	    		    	//Отрисовка что выстрел
		    	    	field.opponent_field[x][y] = 2;    
                        break;

			        case 2:
				        //Функция ошибки, сюда уже били
			    	    break;

    			    case 3:
	    		    	//Функция ошибки, сюда уже били
		    	    	break;
				
		        	default:
		    	    	printf("Что-то пошло не так");
		    		    break;
                }	
		    }
        }else{  //проверка на атакующий или нет 
			    //Ход противника
			    /* Получаем ячейку куда был выстрел 
			     * Ставим в свой массив, если было 1 то ставится 2
			     * если 0 то ЧТО-ТО
			     * */
            repeat_move = 1;
            while(repeat_move == GOT_SHOT){
                printf("\nBrag : ");
                recv(sock_fd, buf_coord, sizeof(buf_coord), 0);
                x = buf_coord[0];
                y = buf_coord[1];
                switch(field.my_field[x][y]){
                    case 0:
			        	//Функция выставления точки 
				        field.my_field[x][y] = 3;
                        buf_coord[0] = x;
                        buf_coord[1] = y;
                        buf_coord[2] = 0;
				        repeat_move = 0;
                        break;

			        case 1:
				        //Отрисовка что выстрел
				        field.my_field[x][y] = 2;
                        buf_coord[0] = x;
                        buf_coord[1] = y;
                        buf_coord[2] = 1;
                        buf_coord[3] = check(field.my_field);
                        if(buf_coord[3] == 0)
                            repeat_move = 0;
				        break;

			        case 2:
				        //Функция ошибки, сюда уже били
				        break;

			        case 3:
				        //Функция ошибки, сюда уже били
				        break;
				
			        default:
				        printf("Что-то пошло не так");
				        break;
                }
                //Передаю второму игроку о состоянии клетки
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
	    print(field.my_field);
	    printf("\n");
	    print(field.opponent_field);
    }
}
/*
int main()
{
	fill();

	return 0;
}*/

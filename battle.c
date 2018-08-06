//#include "head.h"
#include <stdio.h>

#define GOT_SHOT 1

struct fields{
	char my_field[10][10];
	char opponent_field[10][10];
	char status[256];
};

int battle(struct fields field);

/* Вывод. Так же удалю */
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
void fill()
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
	
	battle(field);
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
int battle(struct fields field)
{
	/* Соединение со вторым игроком */

	print(field.my_field);
	printf("\n");
	print(field.opponent_field);
	
	int x, y;
    int reapit_move;
    while(1){
		//Ход игрока 
		/* Получаем от игрока координаты ячейки
		 * отправляем второму игроку на проверку  
		 * Ожидаем сообщения от второго игрока
		 * получаем либо 0 - пусто, либо 1 - есть корабль
		 * соответственно ставится ничего или 2 (подбил)
		 */
        reapit_move = GOT_SHOT;
        //проверка на атакующий или нет 
        while(reapit_move == GOT_SHOT){
            printf("\nTBoe :");
	    	scanf("%d %d", &x, &y); //функция вызова координат 
		    //Шлю координаты
            //Получаю ответ второго игрока о состоянии этой ячейки 
		    switch(field.opponent_field[x][y]){
			    case 0:
				    //Функция выставления точки 
				    field.opponent_field[x][y] = 3;
                    reapit_move = 0;
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
        //проверка на атакующий или нет 
			//Ход противника
			/* Получаем ячейку куда был выстрел 
			 * Ставим в свой массив, если было 1 то ставится 2
			 * если 0 то ЧТО-ТО
			 */
        reapit_move = 0;
            while(reapit_move != GOT_SHOT){
                printf("\nBrag : ");
                scanf("%d %d", &x, &y); //функция получения координат от противника 
                switch(field.my_field[x][y]){
                    case 0:
			        	//Функция выставления точки 
				        field.my_field[x][y] = 3;
				        reapit_move = 1;
                        break;

			        case 1:
				        //Отрисовка что выстрел
				        field.my_field[x][y] = 2;
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

                if(!check(field.my_field){
                    //отправляю второму игроку что он победил
                }
            }

	    print(field.my_field);
	    printf("\n");
	    print(field.opponent_field);
    }
}

int main()
{
	fill();

	return 0;
}

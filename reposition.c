#define X 0
#define Y 1
#define N 10
#include <stdio.h>
#include <stdlib.h>
#include "head.h"

/* Проверяет возможность размещения
 * Возвращает 1, если можно поставить корабль
 *            0, если нельзя
 * */

int placement_check(int map[N][N], int dir, int *coord, int length){
	if(dir == X){
		for(int y = coord[Y]-1; y <= coord[Y]+1; y++)
			for(int x = coord[X]-1; x <= coord[X]+length; x++){
				if(map[x][y] == 1){
				    return 0;
				}
			}	
	}
	if(dir == Y){
        for(int x = coord[X]-1; x <= coord[X]+1; x++)
            for(int y = coord[Y]-1; y <= coord[Y]+length; y++){
                if(map[x][y] == 1){
                    return 0;
                }
            }
	}
	return 1;
}

/* Ставит корабль
 * Возвращает 0, если проблемы с направлением
 *            1, если все вроде норм
 * */

int ship_setting(int map[N][N], int dir, int *coord, int length){
    int x = coord[X];
    int y = coord[Y];
    if(dir == X) {
        for (int i = 0; i < length; i++, x++) map[x][y] = 1;
    }
    if(dir == Y){
        for (int i = 0; i < length; i++, y++) map[x][y] = 1;
    }else
        return 0;
    return 1;
}

/* Рандомно расставляет корабли:
 * 		Рандомит координаты и направление
 * 		Проверяет возможность постановки
 * 		Если удалось поставить, переходим к следующему кораблю
 * */

void set_rand_ships(int map[N][N]) {

	int coord[2];//определяет первичную координату
	int dir; // 0 = горизонтально, 1 = вертикально
	int ship_length = 5;

	srand(time(NULL));

	while(ship_length != 0) {
		coord[X] = rand() % 10;
		coord[Y] = rand() % 10;
		dir = rand() % 2;

		if (placement_check(map, dir, coord, ship_length)) {
			if(ship_setting(map, dir, coord, ship_length)){
				ship_length--;
			}
		} else {
			printf("Ship cant be placed here!\n");
		}
	}
}


/* Получаем координаты клика
 * Проверяем, ставим горизонтальный корбль
 * Пока получаем клики по одной точке:
 * 		Меняем направление
 * 		Проверяем можно ли поставить корабль в этом направлении
 * 		Удаляем поставленный корабль
 * 		Ставим корабль в этом направлении
 * При клике по другой точке, переходим на следующий корабль
 * */

void set_ships_by_hand(int map[N][N]) {
	int coord[2] = wait_click(0);
	// В процессе...
}
#define X 1
#define Y 0
#define N 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "head.h"

/* Проверяет возможность размещения
 * Возвращает 1, если можно поставить корабль
 *            0, если нельзя
 * */

int placement_check(struct fields map, int dir, int *coord, int length){
	if(dir == X){
		for(int y = coord[Y]-1; y <= coord[Y]+1; y++)
			for(int x = coord[X]-1; x <= coord[X]+length; x++){
				if(map.my_field[x][y] == 1){
				    return 0;
				}
			}	
	}
	if(dir == Y){
        for(int x = coord[X]-1; x <= coord[X]+1; x++)
            for(int y = coord[Y]-1; y <= coord[Y]+length; y++){
                if(map.my_field[x][y] == 1){
                    return 0;
                }
            }
	}
	return 1;
}

/* Ставит корабль
 * Принимает val, как значение для заполнения
 *      1 - заполняем клетками корабля
 *      0 - заполняем пустыми клетками (удаляем корабль)
 * Возвращает 0, если проблемы с направлением
 *            1, если все вроде норм
 * */

struct fields ship_setting(struct fields map, int dir, int *coord, int length, int val){
    int x = coord[X];
    int y = coord[Y];
    if(dir == X) {
        for (int i = 0; i < length; i++, x++) map.my_field[y][x] = val;
    }
    if(dir == Y){
        for (int i = 0; i < length; i++, y++) map.my_field[y][x] = val;
    }
    return map;
}

/*
 * Заполняет оба поля нулями
 * */

struct fields init(struct fields map){
	for(int x = 0; x < N; x++)
		for(int y = 0; y < N; y++) {
			map.my_field[x][y] = 0;
			map.opponent_field[x][y] = 0;
		}
	return map;
}

/* Рандомно расставляет корабли:
 * 		Рандомит координаты и направление
 * 		Проверяет возможность постановки
 * 		Если удалось поставить, переходим к следующему кораблю
 * */

struct fields set_rand_ships(struct fields map) {
	map = init(map);

	int coord[2];//определяет первичную координату
	int dir; // 0 = горизонтально, 1 = вертикально
	int ship_length = 5;

	srand(time(NULL));

	while(ship_length != 0) {
		coord[X] = rand() % 10;
		coord[Y] = rand() % 10;
		dir = rand() % 2;

		if (placement_check(map, dir, coord, ship_length)) {
			map = ship_setting(map, dir, coord, ship_length, 1);
				ship_length--;

		} 
	}
	return map;
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

struct fields set_ships_by_hand(struct fields map) {
	map = init(map);
	strcpy (map.status, "Place your ships");
	int dir = 0; // 1 = горизонтально, 0 = вертикально
	int ship_length = 5;
	int *coord, cach_coord[2] = {11, 11};
	while(ship_length != 0) {		
		window(map);
		coord = wait_click(0);
		
		if(coord[Y] == cach_coord[Y] && coord[X] == cach_coord[X]){
			if (placement_check(map, Y, coord, ship_length)){
				ship_length++;
				map = ship_setting(map, X, coord, ship_length, 0);
				map = ship_setting(map, Y, coord, ship_length, 1);
				ship_length--;
				window(map);
        		}
		}else{
			if (placement_check(map, X, coord, ship_length)){
				map = ship_setting(map, X, coord, ship_length, 1);
				ship_length--;
				window(map);
			}
		}
		cach_coord[0] = coord[0];
		cach_coord[1] = coord[1];
		
	}
	return map;
}

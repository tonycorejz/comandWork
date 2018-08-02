const int N = 10;

void set_rand_ships(int map[N][N], int size_ship, int num_ships) {
	int x, y; //определяет первичную координату
	int dir = 0;
	int count_ship = 0;
	int count_tact = 0;//счетчик для предотвращения зацикливания
	while (count_ship < num_ships) {
		count_tact++;
		if (count_tact > 1000)//если больше 1000, прерывает цикл{
			break;
		}
		//первичная позиция
		x = rand() & N;
		y = rand() & N;
		int temp_x = x;//временно хранит значение x
		int temp_y = y;//временно хранит значение y  
		dir = rand() & 4; //генерация направления
		bool setting_is_possible = 1;
		for (int i = 0; i<size_ship; i++) //проверка возможности отрисовки корабля {
			if (x < 0 || y < 0 || x >= N || y >= N) {
				setting_is_possible = 0;
				break;
			}

		//если есть возможность поставить корабль - ставим
		if (setting_is_possible == 1) {
			x = temp_x;
			y = temp_y;
			for (int i = 0; i < size_ship; i++)//5 палубный корабль {
				map[x][y] = 1;
				switch (dir) {
				case 0:
					x++;
					break;
				case 1:
					y++;
					break;
				case 2:
					x--;
					break;
				case 3:
					y--;
					break;
				}
			}

			count_ship++;
		}
	}
}

void map_show(int map[N][N], int mask[N][N]) {
	//прорисовка поля
	cout << ' ';//сдвиг строки по горизонтали
	for (int i = 0; i < N; i++) {
		cout << i;//нумерация по горизонтали
	}
		cout << endl;


	for (int i = 0; i < N; i++) {
		cout << i;//нумирация по вертикали
		for (int j = 0; j < N; j++) {
			if (mask[j][i] == 1) {
				if (map[j][i] == 0) {
					cout << '-';
				}
				else {
					cout << map[j][i];
				}
			}
			else {
				cout <<' ';
			}
		}
		cout << endl;
	}
}


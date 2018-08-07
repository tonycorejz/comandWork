#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <signal.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct fields{
	char my_field[10][10];
	char opponent_field[10][10];
	char status[256];
};

struct connect_struct{
    char *ip_port; 
    int sock_id;
    /* Переменная для определения каким по счету
     * подключился игрок.
     * Если первым то 1
     * Если вторым то 0
     * */
    int stroke; 
};

struct connect_struct connect_est (char *ip_port);                    //возвращает структуру, порт 8679

struct fields set_rand_ships(struct fields field); // возвращает структуру c заполненными полями

struct fields set_ships_by_hand(struct fields field);

int window (struct fields field);             //отрисовывает окна
int *  wait_click(int win_number );// 0 - для своего окна, 1 - для окна противника
int battle(struct fields field, int sock_fd, int stroke); // возвращает исход боя

#endif

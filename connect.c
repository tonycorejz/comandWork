#include "head.h"

int connect_est (char *ip_port){
    struct  sockaddr_in me, opponent;
    socklen_t length = sizeof(struct sockaddr_in);
    int sock_d;

    if ((sock_d = socket(AF_INET, SOCK_DGRAM,0)) < 0) {
        perror("Can't create socket");
        exit(1);
    }

   // memset(&me, 0, length);
    me.sin_family = AF_INET;
    me.sin_port = htons(8679);
	  me.sin_addr.s_addr=htonl(INADDR_ANY);
    if (bind(sock_d,(struct sockaddr *) &me, length) < 0) {
        perror("Can't bind socket");
        exit(2);
    }
    if(ip_port!="")
          me.sin_addr.s_addr = inet_addr(ip_port);
    else     
	  me.sin_addr.s_addr=inet_addr("192.168.2.255");
    int val=1;
    setsockopt(sock_d,SOL_SOCKET,SO_BROADCAST,&val,sizeof(int));
    char mes[256]="Hello, play SaeBattle?",buf[1500];
    sendto(sock_d, mes, strlen(mes), 0, (struct sockaddr *)&me, sizeof(me));
    recvfrom(sock_d, buf, 1024, 0, (struct sockaddr *) &me, &length);// получаю свое сообщение. Надо решить проблему

		printf("receive from %s:%i: %s  \n",inet_ntoa(me.sin_addr),htons(me.sin_port),buf);
    if(!strcmp(buf,"Hello, play SeaBattle?")) // получили запрос на соединение
    {
	    strcpy(mes,"Ok, play SeaBattle");
	    sendto(sock_d, mes, strlen(mes), 0, (struct sockaddr *)&me, sizeof(me));
            if (bind(sock_d,(struct sockaddr *) &me, length) < 0) {
                perror("Can't bind socket");
                exit(4);
             }
    }
    if(!strcmp(buf,"Ok, play SeaBattle")) // получили запрос на соединение
       if (bind(sock_d,(struct sockaddr *) &me, length) < 0) {
                perror("Can't bind socket");
                exit(4);
             }
return sock_d;
}

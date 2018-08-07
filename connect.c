#include "head.h"

struct connect_struct connect_est (char *ip_port){
    struct  sockaddr_in me, opponent;
    struct connect_struct con_st;
    socklen_t length = sizeof(struct sockaddr_in);
    int sock_d,sock_Broad;

    if ((sock_d = socket(AF_INET, SOCK_DGRAM,0)) < 0)
         {  perror("Can't create socket");   exit(1);  }

    if ((sock_Broad = socket(AF_INET, SOCK_DGRAM,0)) < 0)
         {   perror("Can't create socket");   exit(1);  }

   // memset(&me, 0, length);
    me.sin_family = AF_INET;
    me.sin_port = htons(8679);
    me.sin_addr.s_addr=htonl(INADDR_ANY);
    if (bind(sock_d,(struct sockaddr *) &me, length) < 0) 
        {    perror("Can't bind socket");   exit(2);   }
    char mes[256]="Hello, play SeaBattle?",buf[1500];
    if(strlen(ip_port)!=0){  // ip адрес передан
          printf("Отправлен запрос на подключение к  %s\n",ip_port);
          me.sin_addr.s_addr = inet_addr(ip_port);
          sendto(sock_d, mes, strlen(mes), 0, (struct sockaddr *)&me, sizeof(me));
    }
    else  {     
	    printf("%s\n","Broad");
	  me.sin_addr.s_addr=inet_addr("192.168.2.255"); // широковещательный адрес
          int val=1;
          setsockopt(sock_Broad,SOL_SOCKET,SO_BROADCAST,&val,sizeof(int));
          sendto(sock_Broad, mes, strlen(mes), 0, (struct sockaddr *)&me, sizeof(me));
          close(sock_Broad);
          recvfrom(sock_d, buf, 1024, 0, (struct sockaddr *) &me, &length);// получаю свое сообщение. Надо решить проблему
	//	printf("receive from %s:%i: %s  \n",inet_ntoa(me.sin_addr),htons(me.sin_port),buf);

          }
    while(1){
     memset(buf, 0, sizeof(buf));
     length=sizeof(me);
    recvfrom(sock_d, buf, 1024, 0, (struct sockaddr *) &me, &length);// ждем ответ оппонента
		printf("receive from %s:%i: %s  \n",inet_ntoa(me.sin_addr),htons(me.sin_port),buf);
    if(!strcmp(buf,"Hello, play SeaBattle?")) // получили запрос на соединение
      {
	    me.sin_port = htons(8679);
	    strcpy(mes,"Ok, play SeaBattle");
	    connect(sock_d, (struct sockaddr *)&me, sizeof(me)); // подсоединяемся к серверу
	   // sendto(sock_d, mes, strlen(mes), 0,(struct sockaddr *)&me, sizeof(me));
	    send(sock_d, mes, strlen(mes), 0);
	   con_st.stroke=1;
	    break;
      }
    if(!strcmp(buf,"Ok, play SeaBattle")){ // получили подтверждение
    	   con_st.stroke=0;
	   connect(sock_d, (struct sockaddr *)&me, sizeof(me)); // подсоединяемся к серверу
	    break;    }
    }
    con_st.ip_port=inet_ntoa(me.sin_addr);
    con_st.sock_id=sock_d;
return con_st;
}

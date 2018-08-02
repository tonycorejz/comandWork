#include "head.h"

int connect_est (char *ip_port){
    struct  sockaddr_in me, opponent;
    socklen_t length = sizeof(struct sockaddr_in);
    int sock_d;

    if ((sock_d = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("Can't create socket");
        exit(1);
    }

    memset(&me, 0, length);
    me.sin_family = AF_INET;
    me.sin_addr.s_addr = inet_addr(ip_port);
    me.sin_port = htons(8679);

    if (bind(sock_d, &me, length) < 0) {
        perror("Can't bind socket");
        exit(2);
    }


    return sock_d;
}

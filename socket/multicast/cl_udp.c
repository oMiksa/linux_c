#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/in.h>

int main()
{
    int sock, bytes_read;
    struct sockaddr_in addr, cl;
    char mesg[1024];

    if(sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) < 0){
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("bind");
        exit(2);
    }

    struct ip_mreqn mreq;

    inet_aton(ip_addr, &(mreq.imr_multicast));
    mreq.imp_interface.s_addr = htonl("224.0.0.1");


    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, )

    bytes_read = recvfrom(sock, mesg, sizeof(mesg), 0, (struct sockaddr *)&cl, sizeof(cl));
    mesg[bytes_read] = '\0';
    printf("%s\n", mesg); 
    
    close(sock);

    return 0;
}
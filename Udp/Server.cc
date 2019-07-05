#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<cstring>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
using namespace std;

int main(int argc,char* argv[])
{
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0){
        cerr << "sock error : " << sock <<endl;
        return 1;
    }
    cout << "sock: " << sock <<endl;

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[2]));
    local.sin_addr.s_addr = inet_addr(argv[1]);

    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
    {
        cerr << "bind error" <<endl;
        return 2;
    }
    char buff[1024] = {0};
    for(;;){
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        ssize_t r = recvfrom(sock,buff,sizeof(buff)-1,0,(sockaddr*)&peer,&len);
        if(r > 0){
            buff[r] = 0;
            cout << "client# " << buff <<endl;
        }
        sendto(sock,buff,strlen(buff),0,(sockaddr*)&peer,len);
    }
    close(sock);
    return 0;
}

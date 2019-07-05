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

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    char buff[1024] = {0};
    for(;;){
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        cout << "please enter #" <<" ";
        cin >> buff;
        sendto(sock,buff,strlen(buff),0,(sockaddr*)&server,sizeof(server));

        ssize_t r = recvfrom(sock,buff,sizeof(buff)-1,0,(sockaddr*)&peer,&len);
        if(r > 0){
            buff[r] = 0;
            cout << "server  echo # " << buff <<endl;
        }
    }
    close(sock);
    return 0;
}

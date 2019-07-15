#include<iostream>
#include<string>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<cstring>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;
class TcpClient{
    private:
        int sock;
        string ip;
        int port;
    public:
        TcpClient(string _ip, int _port):ip(_ip),port(_port),sock(-1)
        {}
        void InitClient()
        {
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if(sock < 0){
                cerr << "socket error" <<endl;
                exit(2);
            }
        }
        void Start()
        {
            struct sockaddr_in peer;
            bzero(&peer,sizeof(peer));
            peer.sin_family = AF_INET;
            peer.sin_port = htons(port);
            peer.sin_addr.s_addr = inet_addr(ip.c_str());
            if(connect(sock,(struct sockaddr*)&peer, sizeof(peer)) < 0){
                cerr << "connect error"<<endl;
                exit(3);
            }
            char buf[1024];
            string in;
            while(1){
                cout << "Please Enter# ";
                cin >> in;
                write(sock,in.c_str(),in.size());
                ssize_t s = read(sock, buf, sizeof(buf)-1);
                if(s > 0){
                    buf[s] = 0;
                    cout << "Server Echo # " << buf << endl;
                }
            }
        }
        ~TcpClient()
        {
            if(sock > 0)
            {
                close(sock);
            }
        }
};

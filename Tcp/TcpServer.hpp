#include<iostream>
#include<string>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<cstring>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<pthread.h>
#include"ThreadPool.hpp"
using namespace std;

class TcpServer;
class Arg{
    public:
        string iip;
        int pport;
        int ssock;
        TcpServer* tsp;
};
class TcpServer{
    private:
        int listen_sock;
        int port;
        ThreadPool pool;
    public:
        TcpServer(int _port):port(_port),listen_sock(-1)
        {}
        void InitServer()
        {
            listen_sock = socket(AF_INET, SOCK_STREAM, 0);
            if(listen_sock < 0){
                cerr << "listen_sock error" <<endl;
                exit(2);
            }
            int opt = 1;
            setsockopt(listen_sock,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            struct sockaddr_in local;
            bzero(&local,sizeof(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(port);
            local.sin_addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY
            if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local)) < 0){
                cout << "bind error " << endl;
                exit(3);
            }
            if(listen(listen_sock,5) < 0){
                cout << "listen error" <<endl;
                exit(4);
            }
            signal(SIGCHLD,SIG_IGN);
            pool.InitThreadPool();
        }
        static void Service(int sock)
        {
            char buf[1024];
            while(1){
                ssize_t s = read(sock,buf, sizeof(buf)-1);
                if(s > 0){
                    buf[s] = 0;
                    write(sock, buf, strlen(buf));
                }
                else if(s == 0){
                    cout << "client quit!" <<endl;
                    break;
                }
                else{
                    cerr << "read error" <<endl;
                    break;
                }
            }
            close(sock);
        }
        //static void* Run(void* arg)//-> service
        //{
        //    pthread_detach(pthread_self());
        //    Arg* sarg = (Arg*)arg;
        //    sarg->tsp->Service(sarg->ssock, sarg->iip, sarg->pport);
        //    delete sarg;
        //}
        void Start()
        {
            struct sockaddr_in peer;
            socklen_t len;
            for(;;){
                len = sizeof(peer);
                int sock = accept(listen_sock,(struct sockaddr*)&peer, &len);
                if(sock < 0){
                    cerr << "accept error" << endl;
                    continue;
                }
                std::cout << " Get a new client " << sock <<endl;
                Task t;
                t.InitTask(sock,Service);
                pool.PushTask(t);
                //int port_ = ntohs(peer.sin_port);
                //string ip_ = inet_ntoa(peer.sin_addr);

                //pthread_t tid;
                //Arg* arg = new Arg;
                //arg->iip = ip_;
                //arg->ssock = sock;
                //arg->pport = port_;
                //arg->tsp = this;

                //pthread_create(&tid, NULL, Run, (void*)arg);

                //pid_t id = fork();
                //if(id < 0){
                //    cout << "fork error" <<endl;
                //    close(sock);
                //}
                //else if(id == 0){
                //    //if(fork() > 0){
                //    //    exit(1);
                //    //}
                //    close(listen_sock);
                //    Service(sock);
                //    exit(0);
                //}
                //else{
                //    close(sock);
                //}
            }
        }
        ~TcpServer()
        {
            if(listen_sock > 0)
                close(listen_sock);
        }
};

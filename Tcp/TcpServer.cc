#include"TcpServer.hpp"

void Usage(string proc)
{
    cout << "Usage : " << " prot" <<endl;
}
int main(int argc, char* argv[])
{
    if(argc != 2){
        Usage(argv[1]);
        exit(1);
    }
    int port = atoi(argv[1]);
    TcpServer* tsp = new TcpServer(port);
    tsp->InitServer();
    tsp->Start();
    return 0;
}

#include"TcpClient.hpp"

void Usage(string proc)
{
    cout << "Usage : " << proc << " ip prot" <<endl;
}
int main(int argc, char* argv[])
{
    if(argc != 3){
        Usage(argv[0]);
        exit(1);
    }
    int port = atoi(argv[2]);
    string ip = argv[1];
    TcpClient* tsp = new TcpClient(ip, port);
    tsp->InitClient();
    tsp->Start();
    return 0;
}

.PHONY:all
all: TcpServer TcpClient

TcpClient:TcpClient.cc
	g++ -o $@ $^
TcpServer:TcpServer.cc
	g++ -o $@ $^ -lpthread -std=c++11
.PHONY:clean
clean:
	rm -f TcpServer TcpClient

.PHONY:all
all: Client Server

Client:Client.cc
	g++ -std=c++11 -o $@ $^
Server:Server.cc
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -f Client Server

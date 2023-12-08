#ifndef SRC_SERVERSOCKET_H_
#define SRC_SERVERSOCKET_H_

#include "Socket.h"

namespace pr {

class ServerSocket {
	int socketfd;

public :
	// Demarre l'ecoute sur le port donne
	ServerSocket(int port);

	int getFD() { return socketfd;}
	bool isOpen() const {return socketfd != -1;}

	Socket accept();

	void close();
};

// CTOR
ServerSocket::ServerSocket(int port){
	socketfd = socket(AF_UNSPEC, SOCK_STREAM, 0);
	if (socketfd == -1) {
		perror("serversocket fd error");
		exit(-1);
	}

	struct addrinfo *result, *rp;
	int s;

	s = getaddrinfo(nullptr, std::to_string(port).c_str(), nullptr, &result);
	if (s != 0) {
		perror("ServerSocket gettaddrinfo");
		exit(-1);
	}

	socketfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

	if (socketfd == -1) {
		perror("socketfd -1");
		exit(-1);
	}

	if (bind(socketfd, rp->ai_addr, rp->ai_addrlen) == -1) {
		perror("bind");
		close();
	}

	listen(socketfd, 50/*taille file d'attente*/);
}

Socket ServerSocket::accept(){
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	int clientFd;
	if(clientFd = ::accept(socketfd, (struct sockaddr *) &addr, &addr_len) == -1) {
		perror("accept");
		exit(-1);
	}

	std::cout << "Connexion..." << std::endl;

	return clientFd; // appel implicite au ctor de Socket
}

void ServerSocket::close(){
	shutdown(socketfd, SHUT_RDWR);
	::close(socketfd);
}

} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */

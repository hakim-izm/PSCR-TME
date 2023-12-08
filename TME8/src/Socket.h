#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <netinet/ip.h>
#include <string>
#include <iosfwd>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

namespace pr {

class Socket {
	int fd;

public :
	Socket():fd(-1){}
	Socket(int fd):fd(fd){}

	// tente de se connecter à l'hôte fourni
	void connect(const std::string & host, int port);
	void connect(sockaddr * addr, socklen_t addr_len);

	bool isOpen() const {return fd != -1;}
	int getFD() { return fd ;}

	void close();
};

std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr){
	char hname[1024];

	if(!getnameinfo((struct sockaddr *) addr, sizeof(*addr), hname, 1024, nullptr, 0, 0)){
		os << hname;
	}

	os << inet_ntoa(addr->sin_addr) << ":" << ntohs(addr->sin_port);

	return os;
}

void Socket::connect(const std::string & host, int port){
	/* Obtain address(es) matching host/port. */

	int s;
	struct addrinfo *result, *rp;

	s = getaddrinfo(host.c_str(), std::to_string(port).c_str(), nullptr, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/*	getaddrinfo() returns a list of address structures.
		Try each address until we successfully bind(2).
		If socket(2) (or bind(2)) fails, we (close the socket
		and) try the next address. */

	// Itération sur les addrinfo (liste chaînée)
	for (rp = result; rp != nullptr; rp = rp->ai_next) {
		fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		if (fd == -1)
			continue;

		if (bind(fd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;                  /* Success */

		::close(fd);
	}

	freeaddrinfo(result);           /* No longer needed */

	connect(result->ai_addr, result->ai_addrlen);

}

void Socket::connect(sockaddr * addr, socklen_t addr_len) {
	if(::connect(fd, addr, addr_len)) {
		::close(fd);
		perror("connection");
		exit(-1);
	}
}

void Socket::close() {
	shutdown(fd, SHUT_RDWR);
	::close(fd);
}

} // namespace pr

#endif /* SRC_SOCKET_H_ */

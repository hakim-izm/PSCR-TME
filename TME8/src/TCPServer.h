#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_

#include <thread>
#include <vector>
#include "ServerSocket.h"
#include "ConnectionHandler.h"

namespace pr {

// un serveur TCP, la gestion des connections est déléguée
class TCPServer : ConnectionHandler {
	ServerSocket * ss; // la socket d'attente si elle est instanciee
	ConnectionHandler * handler; // le gestionnaire de session passe a la constru
	std::vector<std::thread> threads;
public :
	TCPServer(ConnectionHandler * handler): ss(nullptr),handler(handler) {
	}
	~TCPServer() { for (auto &t : threads) t.join(); }
	// Tente de creer une socket d'attente sur le port donné
	bool startServer (int port);

	// stoppe le serveur
	void stopServer () ;

	// fonctions héritées
	void handleConnection(Socket s) override;
};

bool TCPServer::startServer(int port) {
	*ss = ServerSocket(port);

	if(!ss->isOpen()) {
		perror("ss open");
		exit(-1);
	}

	while(true) { // consomme le thread
		std::cout << "En attente..." << std::endl;
		Socket sc = ss->accept();

		threads.emplace_back([&](Socket sc) {
			this->handleConnection(sc);
		}, sc);
	}
}

void TCPServer::handleConnection(Socket s) {
	int i;
	read(s.getFD(), &i, sizeof(i));
	i*=2;
	write(ss->getFD(), &i, sizeof(i));
	s.close();
}

} // ns pr

#endif /* SRC_TCPSERVER_H_ */

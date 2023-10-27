#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	int cpt_fils = 0; // compteur de fils 
	std::cout << "main pid=" << getpid() << std::endl;
	pid_t fils; // pid du fils

	for (int i=1, j=N; i<=N && j==N && (fils=fork())==0 ; i++ ) {
		std::cout << "nouveau fils créé" << std::endl;
		cpt_fils = 0; // ici on est dans un nouveau fils : RAZ
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				std::cout << "nouveau fils créé" << std::endl;
				cpt_fils = 0; // ici on est dans un nouveau fils : RAZ
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			} else {
				cpt_fils++; // père qui vient de créer un fils : +1
			}
		}
	}
	if(fils) // si c'est le père
		cpt_fils++; // père qui vient de créer un fils : +1
	std::cout << "(cpt_fils:" << cpt_fils << ")" << std::endl;

	// attente de la fin des fils créés par le processus
	for (int i=0; i<cpt_fils; i++) {
		wait(nullptr);
		std::cout << "fin d'un fils" << std::endl;
	}

	return 0;
}

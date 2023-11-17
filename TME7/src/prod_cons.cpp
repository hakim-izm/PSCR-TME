#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
#include <fcntl.h>

using namespace std;
using namespace pr;

void producteur (Stack<char> * stack) {
	char c ;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

int main () {
	Stack<char> * s = new Stack<char>();

/*
	const int N = 5; //nb producteurs
	const int M = 10; //nb consommateurs

	// Mémoire partagée
	int fd = shm_open("/shm_prod_cons", O_RDWR, 0600);
	if(fd == -1) {
		perror("shared memory error");
		exit(1);
	}

	if(ftruncate(fd, /*size ?*//*) == -1){
		perror("ftruncate error");
		exit(1);
	}
*/

	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	}

	wait(0);
	wait(0);

	delete s;
	return 0;
}


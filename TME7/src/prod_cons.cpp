#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
#include <fcntl.h>

using namespace std;
using namespace pr;

// VARIABLE GLOBALE
// état du programme (interruption Ctrl+C)
bool interrupt = false;

void producteur (Stack<char> * stack) {
	char c ;
	while(!interrupt && cin.get(c)){

		while (cin.get(c)){
			cout << "producteur interrupt : " << interrupt << endl;
			if(interrupt){
				std::cout<<"j'entre"<<std::endl;
				return;
			}
			stack->push(c);
		}
	}
}

void consomateur (Stack<char> * stack) {
	
		while (!interrupt) {
			cout << "consomateur interrupt : " << interrupt << endl;
			if(interrupt){
				std::cout<<"j'entre 2"<<std::endl;
				return;
			}
			char c = stack->pop();
			cout << c << flush ;
		}
	
}

int main () { while(!interrupt)
	{const int NB_PROD = 10;

	int shared_mem = shm_open("/shared_mem", O_CREAT/*|O_EXCL*/|O_RDWR, 0666);
	if(shared_mem == -1){
		perror("shm_open error");
		exit(1);
	}

	if(ftruncate(shared_mem, sizeof(Stack<char>)) == -1){
		perror("ftruncate error");
		exit(1);
	}

	void *mmap_ptr = mmap(NULL, sizeof(Stack<char>), PROT_READ|PROT_WRITE, MAP_SHARED, shared_mem, 0);
	if(mmap_ptr == MAP_FAILED) {
		perror("mmap error");
		exit(1);
	}

	Stack<char> * s = new (mmap_ptr) Stack<char>(NB_PROD);

	// définition signal
	signal(SIGINT, [](int sig){
		interrupt = true;
		cout << "[PID:" << getpid() << "] interrupt" << interrupt << "->";
		
		cout << interrupt << endl;
	});

	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		cout << "cc1" << endl;
		return 0;
	}
    
	pid_t pc = fork();
	
	if (pc==0) {
		cout << "fils 2" << endl;
		consomateur(s);
		cout << "cc2" << endl;
		return 0;
	}

	cout << "cc3" << endl;
	wait(0);
	wait(0);

	s->~Stack();
	shm_unlink("/shared_mem");
	}
	return 0;
}


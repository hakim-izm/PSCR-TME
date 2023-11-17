#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t *sem_prod;
	sem_t *sem_cons;
public :
	Stack () : sz(0) {
		memset(tab,0,sizeof tab);
		sem_prod = sem_open("sem_prod", O_CREAT|O_EXCL|O_RDWR, 066, 1);
		sem_cons = sem_open("sem_cons", O_CREAT|O_EXCL|O_RDWR, 066, 1);
	}

	~Stack(){
		sem_prod->unlink();
		sem_cons->unlink();
	}

	T pop () {
		// bloquer si vide
		if(sz == 0) {
			sem_cons->wait();
		}
		T toret = tab[--sz];
		// débloquer producteur
		sem_prod->post();
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		if(sz == STACKSIZE){
			sem_prod->wait();
		}

		tab[sz++] = elt;
		// débloquer consommateur
		sem_cons->post();
	}
};

}

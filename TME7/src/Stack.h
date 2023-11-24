#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>

#include <iostream> //  TODO : remove 
#include <unistd.h>

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	const int N;
	T tab [STACKSIZE];
	size_t sz;
	sem_t mutex;
	sem_t sem_prod;
	sem_t sem_cons;
public :
	Stack (int N) : N(N), sz(0) {
		memset(tab,0,sizeof tab);
		sem_init(&mutex, 1, 1);
		sem_init(&sem_cons, 1, 0);
		sem_init(&sem_prod, 1, N);
	}

	~Stack(){
		sem_destroy(&mutex);
		sem_destroy(&sem_cons);
		sem_destroy(&sem_prod);
	}

	T pop () {
		std::cout << std::endl << "[PID:" << getpid() << "] Stack::pop()" << std::endl;

		// bloquer si vide
		sem_wait(&sem_cons);
		sem_wait(&mutex);
		T toret = tab[--sz];
		// débloquer producteur
		sem_post(&mutex);
		sem_post(&sem_prod);
		return toret;
	}

	void push(T elt) {
		std::cout << std::endl << "[PID:" << getpid() << "] Stack::push()" << std::endl;

		//bloquer si plein
		sem_wait(&sem_prod);
		std::cout << "push1" << std::endl;
		sem_wait(&mutex);
		std::cout << "push2" << std::endl;
		tab[sz++] = elt;
		std::cout << "push3" << std::endl;
		// débloquer consommateur
		sem_post(&mutex);
		std::cout << "push4" << std::endl;
		sem_post(&sem_cons);
		std::cout << "push5" << std::endl;
	}

	// faire une méthode stop() pour gérer l'arrêt du programme avec SIGINT.
	// débloque les sémaphores bloquants
};

}

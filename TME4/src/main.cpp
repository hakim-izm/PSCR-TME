#include "Banque.h"
#include <vector>
#include <thread>
#include <iostream>

using namespace std;

const int NB_THREAD = 10;
const int NB_COMPTES = 1;
const int SOLDE_PAR_DEFAUT = 1000;

void question1(pr::Banque b){
	cout << "starting 1000 transferts" << endl;
	// init random seed
	srand (time(NULL));

	for(int index=0; index<1000; ++index){
		// indices de comptes aléatoires
		size_t i = rand() % NB_COMPTES; // compte débiteur aléatoire
		size_t j = rand() % NB_COMPTES; // compte débiteur aléatoire

		// montant aléatoire
		unsigned int m = rand() % 100 + 1;

		// Transaction
		b.transfert(i, j, m);

		// sleep duration (0 -> 20ms)
		size_t sleepDuration = rand() % 21;

		// sleep
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));

		// verbose
		cout << "transferred " << m << " from " << i << " to " << j << endl;
	}

	cout << "finished 1000 transferts" << endl;
}

int main () {
	vector<thread> threads;

	// initialisation de la banque
	pr::Banque banque(NB_COMPTES, SOLDE_PAR_DEFAUT); // paramètres arbitraires

	// TODO : creer des threads qui font ce qui est demandé
	threads.reserve(NB_THREAD);
	for(int index=0; index<NB_THREAD; ++index){
		threads.emplace_back(question1, banque);
		cout << "thread created : " << index << endl;
	}

	for (auto & t : threads) {
		t.join();
		cout << "joined" << endl;
	}

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}

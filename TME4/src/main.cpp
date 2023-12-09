#include "Banque.h"
#include <vector>
#include <thread>
#include <iostream>
#include <atomic>

using namespace std;

const int NB_THREAD = 16; // nb de threads de TRANSFERT
const int NB_COMPTES = 50;
const int SOLDE_PAR_DEFAUT = 1000;

void question1(pr::Banque & b, atomic<int> & activeTransactions){
	cout << "starting 1000 transferts" << endl;
	// init random seed
	srand (time(NULL));

	for(int index=0; index<1000; ++index){
		// indices de comptes aléatoires
		size_t i = rand() % NB_COMPTES; // compte débiteur aléatoire
		size_t j = rand() % NB_COMPTES; // compte créditeur aléatoire

		// montant aléatoire
		unsigned int m = rand() % 100 + 1;

		// Transaction
		b.transfert(i, j, m);

		// sleep duration (0 -> 20ms)
		size_t sleepDuration = rand() % 21;

		// sleep
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));

		// verbose
		// cout << "transferred " << m << " from " << i << " to " << j << endl;
	}

	cout << "finished 1000 transferts" << endl;
	--activeTransactions;
}

int main () {
	vector<thread> threads;
	threads.reserve(NB_THREAD + 1); // +1 pour le thread comptable
	
	
	std::atomic<int> activeTransactions = NB_THREAD;

	// initialisation de la banque
	pr::Banque banque(NB_COMPTES, SOLDE_PAR_DEFAUT); // paramètres arbitraires

	// thread comptable
	threads.emplace_back([&banque, &activeTransactions](){
		while(activeTransactions > 0)
			banque.comptabiliser(SOLDE_PAR_DEFAUT * NB_COMPTES);
	});

	// threads des transferts
	for(int index=0; index<NB_THREAD; ++index){
		threads.emplace_back(question1, std::ref(banque), std::ref(activeTransactions));
	}

	// fermeture propre des threads
	for (auto & t : threads) {
		t.join();
		cout << "joined" << endl;
	}

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
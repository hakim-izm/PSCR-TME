#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {	
	// unique_lock<std::mutex> l(m);
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];

	// verrou des comptes
	if (deb < cred) { // q6 : régler le problème d'interblocage
		debiteur.lock();
		// cout << "debiteur " << deb << " locked" << endl;
		crediteur.lock();
		// cout << "crediteur " << cred << " locked" << endl;
	} else {
		crediteur.lock();
		// cout << "crediteur " << cred << " locked" << endl;
		debiteur.lock();
		// cout << "debiteur " << deb << " locked" << endl;
	}

	// sleep duration (0 -> 20ms)
	size_t sleepDuration = rand() % 21;

	// sleep
	std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));

	// transaction
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}

	// déverrou des comptes
	if (deb < cred) { // q6 : régler le problème d'interblocage
		debiteur.unlock();
		// cout << "debiteur " << deb << " unlocked" << endl;
		crediteur.unlock();
		// cout << "crediteur " << cred << " unlocked" << endl;
	} else {
		crediteur.unlock();
		// cout << "crediteur " << cred << " unlocked" << endl;
		debiteur.unlock();
		// cout << "debiteur " << deb << " unlocked" << endl;
	}
}

size_t Banque::size() const {
	return comptes.size();
}

bool Banque::comptabiliser (int attendu) const {
	// unique_lock<std::mutex> l(m);
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) compte.lock();
	for (const auto & compte : comptes) {
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	for (const auto & compte : comptes) compte.unlock();
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	return bilan == attendu;
}
}

#pragma once
#include <thread>
#include <mutex>

namespace pr {

class Compte {
	mutable std::recursive_mutex m;
	int solde;
public :
	Compte(int solde=0):solde(solde) {}
	Compte(const Compte & other);
	void crediter (unsigned int val) ;
	bool debiter (unsigned int val) ;
	int getSolde() const  ;
	// trois méthodes de q3
	void lock() const;
	void unlock() const;
	bool try_lock() const;
};

}

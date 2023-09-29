//============================================================================
// Name        : TME0.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	// Question 4
	int tab[10] = {0,1,2,3,4,5,6,7,8,9};
	for(int i=0; i<10; ++i)
		cout << tab[i] << endl;

	// Question 5
	for (size_t i=9; i >= 0 ; i--) {
		if (tab[i] - tab[i-1] != 1) {
				cout << "probleme !";
		}
	}

	/*
	 * Question 6
	 *
	 * Le tableau contient les entiers de 0 à 9.
	 * Au fur et à mesure que i décrémente, la valeur de i va atteindre 0.
	 * Une décrémentation par 1 supplémentaire de i va porter sa valeur à la borne maximale d'un entier non signé codé sur 8 octets.
	 * Ainsi, i ne sera jamais inférieur à 0 et la boucle for sera infinie.
	 *
	 * On peut remplacer "size_t i" par "int i" pour régler le problème.
	 *
	 */

	return 0;
}

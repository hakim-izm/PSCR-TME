#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>

// Fonction qui vérifie si un mot est présent dans le vecteur (en parcourant le vecteur)
// retourne 1 si mot déjà lu
// retourne 0 sinon
bool isWordAlreadyRead(const std::string word, const std::vector<std::string> vec){
	for(unsigned int i=0; i<vec.size(); i++){
		if(vec.at(i) == word)
			return true;
	}
	return false;
}

int main () {
	using namespace std;
	using namespace std::chrono;

	// Vecteur qui contient les mots déjà lus
	vector<string> readWords;

	ifstream input = ifstream("./tmp/WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// Vérification si le mot est déjà lu (dans le vecteur readWords)
		if(isWordAlreadyRead(word, readWords)) {
			continue;
		} else { 
			// Ajout du nouveau mot dans le vecteur
			readWords.push_back(word);
			// word est maintenant "tout propre"
			if (nombre_lu % 100 == 0)
				// on affiche un mot "propre" sur 100
				cout << nombre_lu << ": "<< word << endl;
			nombre_lu++;
		}
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;

    return 0;
}



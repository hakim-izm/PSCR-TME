#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <utility>
#include "hashmap.h"

// Fonction qui récupère le nombres d'occurences d'un mot dans le vecteur vec
// retourne le nombre de mots
int getCountForWord(const std::string word, const std::vector<std::pair<std::string, int>>* vec) {
	// Vérification de la présence du mot word dans vec
	for(unsigned int i=0; i<vec->size(); ++i){
		if(vec->at(i).first == word){
			// Le mot existe
			return vec->at(i).second;
		}
	}
	// Le mot n'existe pas
	return 0;
}

// Fonction qui vérifie si un mot est présent dans le vecteur (en parcourant le vecteur)
// Incrémente le compte de 1 si le mot existe déjà
// retourne 1 si mot déjà lu
// retourne 0 sinon
bool isWordAlreadyRead(std::string word, std::vector<std::pair<std::string, int>> * vec){
	// Vérification de la présence du mot word dans vec
	for(unsigned int i=0; i<vec->size(); ++i){
		if(vec->at(i).first == word){
			// Le mot existe
			vec->at(i).second++;
			return true;
		}
	}
	return false;
}

// Fonction générique qui compte le nb d'éléments entre begin et end
// Retourne le nb d'éléments entre les itérateurs begin et end
template<typename T>
// typedef T* iterator; impossible avec un template
// T = iterator
size_t count(T begin, T end){
	size_t count=0;
	while(begin!=end){
		count++;
		begin++;
	}
	return count;
}

int main () {
	using namespace std;
	using namespace std::chrono;

	// Vecteur qui contient les mots déjà lus avec leur nombre d'occurences
	vector<pair<string, int>> readWords;

	// HashMap comportant les mots (key : mot, value : nb d'occurences)
	pr::HashMap<string, int> wordsMap = pr::HashMap<string, int>(600000);

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

		// UTILISATION HASHMAP
		// Vérification si le mot est déjà lu et récupération de son nombre d'occurences
		int wordCount;
		if (wordsMap.get(word) != nullptr) { // le mot est dans la table
			wordCount = *wordsMap.get(word);
		} else { // le mot n'est pas dans la table
			wordCount = 0;
		}

		// Ajout du mot dans la table (ou mise à jour de l'entrée) avec son nombre d'occurences
		wordsMap.put(word, ++wordCount);

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;

		// AVANT UTILISATION DU HASHMAP
		/*
		// Vérification si le mot est déjà lu (dans le vecteur readWords)
		if(isWordAlreadyRead(word, &readWords)) {
			continue; // l'incrément du compte de 1 se fait dans la fonction
		} else { 
			// Ajout du nouveau mot dans le vecteur (compte de 1)
			readWords.push_back(make_pair(word, 1));
		}
		*/
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;

	// Affichage final pour "war", "peace" et "toto"
	// cout << "Compte du mot \"war\" : " << getCountForWord("war", &readWords) << " mots." << endl;
	// cout << "Compte du mot \"peace\" : " << getCountForWord("peace", &readWords) << " mots." << endl;
	// cout << "Compte du mot \"toto\" : " << getCountForWord("toto", &readWords) << " mots." << endl;

	// Affichage du nombre de mots distincts depuis le hashmap
	cout << "Nombre de mots distincts dans la table de hash : " << wordsMap.size() << endl;

	// Affichage final pour "war", "peace" et "toto" AVEC HASHMAP
	cout << "Compte du mot \"war\" : " << ((wordsMap.get("war") != nullptr) ? *wordsMap.get("war") : 0) << " mots." << endl;
	cout << "Compte du mot \"peace\" : " << ((wordsMap.get("peace") != nullptr) ? *wordsMap.get("peace") : 0) << " mots." << endl;
	cout << "Compte du mot \"toto\" : " << ((wordsMap.get("toto") != nullptr) ? *wordsMap.get("toto") : 0) << " mots." << endl;

	// Initalisation du vecteur de la question 7
	vector<pair<string, int>> wordsVector;

	// Copie des entrées dans la table de hash
	// Parcours des buckets
	for(auto it_bucket = wordsMap.begin(); it_bucket != wordsMap.end(); ++it_bucket){
		// Parcours des forward_list<Entry> de chaque bucket
		for(auto it_fwdlst = it_bucket->begin(); it_fwdlst != it_bucket->end(); ++it_fwdlst){
			// Ajout de l'entrée dans le vecteur
			wordsVector.push_back(make_pair(it_fwdlst->key, it_fwdlst->value));
		}
	}

	// question 8 : tri du vecteur par ordre décroissant du nombre d'occurences
	sort(wordsVector.begin(), wordsVector.end(), [](const pair<string, int> & a, const pair<string, int> & b) -> bool { return a.second > b.second; });
	cout << "Les 10 mots les plus fréquents : " << endl;
	for(size_t i=0; i<10; ++i){
		cout << wordsVector.at(i).first << " : " << wordsVector.at(i).second << " occurrences." << endl;
	}

	// Test count
	cout << "Nb d'éléments de readWords : " << count(readWords.begin(), readWords.end()) << endl;

    return 0;
}



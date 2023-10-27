#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>
#include "rsleep.h"

using namespace std;

// variables de jeu globales
unsigned int lives = 3;

void attaque(pid_t adversaire) {
    // installe un handler pour SIGINT
    signal(SIGINT, [](int signal){ //utilisation d'un lambda
        lives--; // handler qui enlève une vie à l'adversaire
        if(lives == 0) { // l'adversaire meurt suite à coup
            exit(-1); // le processus se termine avec -1
        }
    }); 
    // envoi du signal à l'adversaire
    if(kill(adversaire, SIGINT) == -1) { // si le processus adversaire n'existe plus (il est mort)
        exit(0); // on sort avec la valeur 0
    } else { // le processus adversaire est toujours en vie
        randsleep();
    }
}

void defense() {
    // désarme le signal SIGINT
    signal(SIGINT,SIG_IGN);
    // s'endort pour une durée aléatoire
    randsleep();
}

void combat(pid_t adversaire) {
    while(true) {
        defense();
        attaque(adversaire);
    }
}

int main(){
    // vador : processus principal
    pid_t vador, luke;
    vador = getpid();
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, nullptr); //on met toujours un masque avec un fork ! (le fils est créé avec une copie du procma)
    
    luke = fork(); // je crée luke dans le père et non dans le fils vador

    if(luke) { // si je suis le père (vador)
        combat(luke);
    } else { // si je suis le fils (luke)
        combat(vador);
    }

    // Le processus principal attend la mort des deux processus fils (vador et luke)
    if(luke != 0) { // si je suis le père (vador)
        wait(nullptr);
    }
}
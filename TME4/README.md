# TME sujet semaine 4 : thread, atomic, mutex

[Programmation Système Répartie et Concurrente : Homepage](https://pages.lip6.fr/Yann.Thierry-Mieg/PR)

[Sujet du TME en PDF](https://pages.lip6.fr/Yann.Thierry-Mieg/PR/tdtme4.pdf)

To use the project :
*  Go to an empty folder (not your workspace)
```
mkdir -p tme4 ; cd tme4 ;

```
*  Clone the project, 
```
git clone https://github.com/yanntm/PSCR-TME4.git

```
* Reconfigure project.
This project is compatible with [autoconf/automake](https://www.lrde.epita.fr/~adl/autotools.html), after cloning, use the mantra 
```
cd PSCR-TME4
autoreconf -vfi
./configure 
```
in the root folder to build makefiles for your project.
* Import in eclipse or open with your favorite editor
   * For eclipse, `File->Import->General->Existing projects into workspace` and point the folder tme4.
* To build, simply run `make` in the folder 
   * For eclipse use the "hammer" tool or "Project->Build Project".


Look at the contents of "configure.ac", "Makefile.am" and "src/Makefile.am" which are the input to autotools, and are relatively simple and easy to read.

(c) Sorbonne Université 2018-2019

-----------------------
# PSCR - TME4 

# Hakim IZM (21304224)
# ATSAME GUEDOU JOSIAS (21310496)

## Question 1

Voir fonction `question1()` dans `main.cpp`.

## Question 2

Les mutex implémentés sur le Compte nous permettent d'éviter les data races car ce sont les seuls objets que l'on modifie.

Afin que la mise à jour des deux comptes soit atomique, il faudrait bloquer les comptes subissant un crédit ou un débit. Mais il faut faire attention au risque d'interblocage !

## Question 3

Les trois fonctions ont été ajoutées à la classe Compte pour la rendre `Lockable`.

## Question 4

Nous proposons la stratégie suivante : il faut bloquer les deux comptes sur lesquels on effectue une transaction sur la durée de la transaction.

## Question 5

On assiste ici à un cas d'interblocage. En effet, nous bloquons manuellement les comptes avant d'appeler les fonctions `Compte::crediter` et `Compte::debiter` qui eux aussi bloquent le mutex automatiquement. D'où le blocage. Nous utiliserons un `recursive_mutex` à la place

## Question 6

La méthode `Banque::transfert` dans `Banque.cpp` se charge du transfert entre deux comptes en les verrouillant en amont. Cette méthode peut potentiellement conduire à un interblocage si deux threads essaient de verrouiller simultanément les mêmes comptes dans un ordre différent, car chaque thread peut se retrouver bloqué en attendant que l'autre libère son verrou.

Ceci peut arriver si nous avons deux transferts à la suite : (Cpte 1 -> Cpte 2) et (Cpte 2 -> Cpte 1). On a un risque d'interblocage si jamais ce cas arrive. Pour régler ce problème, nous devons faire le verrouillage et le déverrouillage dans le même ordre que précédemment. Nous pouvons utiliser l'index dans le vecteur pour faire ceci.

## Question 7

Le thread chargé de la comptabilité peut effectuer son calcul au moment d'une transaction (entre un débit et un crédit), faussant ainsi le résultat. Cette solution n'est pas satisfaisante avec les synchronisations actuelles.

## Question 8

Ce cas a été observé directement.

## Question 9

L'ajout d'un mutex dans la banque nous permet d'éviter les problèmes de comptabilité mais ceci annule la concurrence dans les transferts, on le remarque bien par la différence dans le temps d'exécution.

## Question 10

Pour régler ce problème dans la fonction `Banque::comptabiliser()`, nous avons ajouté une boucle `for` permettant de bloquer tous les comptes avant la boucle `for` principale de la comptabilité et une dernière boucle pour débloquer tous les comptes. Le résultat est satisfaisant : aucune erreur comptable n'est signalée dans la console et le temps d'exécution est bien meilleur que dans la question 9.

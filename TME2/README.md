# PSCR - TME2

# Hakim IZM (21304224)
# ATSAME GUEDOU JOSIAS (21310496)

## Question 1

Il y a 566 193 mots dans WarAndPeace.txt.

## Question 2

Nous avons ajouté un vecteur qui contient tous les mots que nous lisons une fois et une fonction `isWordAlreadyRead()` qui parcourt le vecteur et renvoie vrai si le mot passé en paramètre est présent et faux s'il est absent (pas encore lu).

On retrouve 20 333 mots uniques dans le fichier texte.

On remarque que ce code n'est pas optimisé car on traverse le vecteur à chaque fois que l'on rencontre un mot. De plus, la taille de ce vecteur augmente avec le nombre de mots uniques lus, ce qui augmente la durée du parcours dans un stade avancé de l'exécution.

## Question 3

Pour la question 2, nous avons fait une erreur en effecutant la copie de notre vecteur en paramètre de la fonction au lieu de passer un pointeur vers le vecteurs que nous manipulons, ce qui augmente considérablement la durée de traitement.

Nous avons remplacé le `vector<string>` par un `vector<pair<string,int>>`. De plus, nous avons ajouté une fonction `getCountFor>ord()` qui retourne le nombre d'occurences d'un mot dans le vecteur vec.

Nous trouvons les résultats suivants pour les mots demandés :

```
Compte du mot "war" : 298 mots.
Compte du mot "peace" : 114 mots.
Compte du mot "toto" : 0 mots.
```

## Question 4

Nous pouvons penser que la complexité algorithmique pour ce programme est très élevée car nous effectuons un parcours intégral du vecteur comportant les mots à chaque lecture de mots.

On aurait pu utiliser une HashMap à la place en stockant en clef le mot et en valeur son nombre d'occurences.

## Question 5

Table de hash implémentée dans `hashmap.h`.

## Question 6

On retrouve bien le même nombre de mots pour "war", "peace" et "toto" en passant par la hashmap.

## Question 7

Pour la copie des entrées de la table de hash, nous avons parcouru les buckets et dans ce parcours, nous avons parcouru les listes chaînées pour copier les entrées dans le nouveau vecteur.

## Question 8

Les 10 mots les plus utilisés sont :

```
the : 34562 occurrences.
and : 22148 occurrences.
to : 16709 occurrences.
of : 14990 occurrences.
a : 10513 occurrences.
he : 9809 occurrences.
in : 8800 occurrences.
his : 7965 occurrences.
that : 7806 occurrences.
was : 7327 occurrences.
```
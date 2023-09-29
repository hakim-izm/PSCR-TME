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

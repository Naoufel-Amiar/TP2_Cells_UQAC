# TP2 – Arborescence génétique

**Université du Québec à Chicoutimi (UQAC)**  
**Cours : 8INF259 – Structures de données**  
**Session : Automne 2026**  
**Langage : C++17**

## 1. Présentation du projet

L'objectif de ce travail pratique est de concevoir une structure de données générique permettant de gérer une population de cellules ainsi que leurs relations génétiques.

Le programme permet de créer, ajouter, combiner et supprimer des individus, de rechercher des ancêtres communs, d'afficher une généalogie ainsi que de sauvegarder et charger une population à partir de fichiers texte.

Trois types de cellules sont pris en charge :

- `ColorCell` : cellules représentées par des composantes RGB.
- `ChromoCell` : cellules représentées par quatre paires de chromosomes.
- `HorlogeCell` : cellules représentées par une heure sur un cadran de 24 heures.

## 2. Choix de conception

### 2.1. Structure génétique

Nous avons choisi de représenter les relations génétiques sous la forme d'un graphe orienté acyclique (DAG).

Chaque individu possède :

- Un identifiant unique.
- Une valeur génétique de type `T`.
- Un pointeur vers son premier parent.
- Un pointeur vers son deuxième parent.

Cette structure se distingue d'un arbre binaire classique par la possibilité de partager un même ancêtre entre plusieurs branches génétiques, sans dupliquer les individus en mémoire.

Les cycles sont évités en imposant que les identifiants des parents soient strictement inférieurs à celui de leur descendant lors du chargement. Cette propriété est également respectée lors de la création de nouveaux individus.

### 2.2. Stockage des individus

Nous utilisons une `std::map` pour stocker les individus au sein de la population :

```cpp
std::map<int, std::unique_ptr<Individu<T>>> individus_;
```

Ce choix permet :

- D'associer chaque individu à son identifiant.
- D'effectuer des recherches en O(log n).
- De conserver les identifiants dans un ordre croissant.
- De faciliter la sauvegarde des populations.
- De centraliser la gestion de la mémoire.

### 2.3. Gestion de la mémoire

La gestion de la mémoire repose sur les pointeurs intelligents `std::unique_ptr` et le principe RAII.

La population est l'unique propriétaire des individus, tandis que les relations parentales utilisent des pointeurs classiques non propriétaires.

Cette séparation permet à plusieurs descendants de référencer un même parent.

Lors de la suppression d'un individu, les références parentales associées sont remplacées par `nullptr` avant la libération de sa mémoire, afin d'éviter les pointeurs pendants.

### 2.4. Programmation générique

Les classes `Population` et `Individu` utilisent des templates afin de rendre la structure indépendante du type de cellule manipulé.

```cpp
Population<ColorCell>
Population<ChromoCell>
Population<HorlogeCell>
```

Chaque type de cellule possède sa propre surcharge des opérateurs `+`, `<<` et `>>`.

Cette approche permet de mutualiser les opérations de gestion des populations sans utiliser l'héritage.

L'intégration du type `HorlogeCell` a ainsi pu être réalisée sans modifier la structure génétique existante.

### 2.5. Séparation des responsabilités

Le projet est organisé autour de plusieurs classes :

| Classe | Responsabilité |
|---|---|
| `Individu<T>` | Représentation d'un individu et de ses liens parentaux |
| `Population<T>` | Gestion de la population et des relations génétiques |
| `TransTerminal` | Lecture, validation et interprétation des transactions |
| `ColorCell` | Gestion des valeurs RGB |
| `ChromoCell` | Gestion des chromosomes |
| `HorlogeCell` | Gestion des horaires |

Cette organisation facilite la maintenance, la compréhension et l'évolution du programme.

## 3. Choix algorithmiques

### 3.1. Affichage de l'ascendance

L'affichage de l'arborescence utilise un parcours récursif en profondeur préfixe (DFS).

L'algorithme affiche l'individu courant, puis parcourt successivement ses deux branches parentales.

L'indentation de l'affichage est proportionnelle à la profondeur généalogique.

Un ancêtre partagé peut apparaître plusieurs fois à l'affichage sans être dupliqué en mémoire.

### 3.2. Recherche d'un ancêtre commun

La recherche d'un ancêtre commun repose sur deux parcours récursifs permettant de collecter les ancêtres des individus ainsi que leurs distances généalogiques minimales.

L'ancêtre sélectionné est celui qui minimise la somme des deux distances.

En cas d'égalité, l'individu possédant le plus petit identifiant est retenu.

### 3.3. Sauvegarde et chargement

Le chargement d'une population s'effectue en deux étapes :

1. Création des individus en mémoire.
2. Reconstruction des liens parentaux à partir de leurs identifiants.

Une population temporaire est utilisée afin de préserver la population courante en cas d'erreur de chargement.

### 3.4. Combinaison des HorlogeCell

Les horaires sont convertis en minutes pour déterminer le milieu du plus court arc entre deux cellules.

L'utilisation du modulo 1440 permet de prendre en compte le caractère circulaire du cadran de 24 heures.

La division entière par 60 et le modulo 60 permettent ensuite de reconstruire les heures et les minutes.

Lorsque les deux horaires sont séparés exactement de 12 heures, le déplacement s'effectue en avançant, conformément à l'énoncé.

## 4. Utilisation des outils d'intelligence artificielle générative

Durant se projet, nous avons utiliser l'ia pour principalement comprendre certain concept que nous avons utiliser durant le tp.

## 5. Compilation et exécution

Le projet utilise le standard C++17 et ne nécessite aucune bibliothèque externe.

La compilation peut être effectuée à l'aide de la commande suivante :

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude main.cpp source/*.cpp -o TP2_Cells
```

Le programme prend en argument le chemin du fichier de transactions :

```bash
./TP2_Cells fichier_transactions.txt
```

## 6. Conclusion

L'utilisation d'une structure générique, associée à une gestion centralisée de la mémoire et à des relations parentales non propriétaires, permet de gérer efficacement les différents types de cellules.

L'ajout du type `HorlogeCell` lors de la séance de remise illustre l'évolutivité de l'architecture retenue.
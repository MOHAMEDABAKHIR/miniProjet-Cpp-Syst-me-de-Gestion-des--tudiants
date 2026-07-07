# Mini Projet C++ - Systeme de Gestion des Etudiants

Ce projet est une application C++ orientee objet pour gerer des etudiants de plusieurs niveaux :
Licence, Master et Doctorat. Le but est de pratiquer l'heritage, le polymorphisme, les conteneurs STL,
les exceptions personnalisees, la persistance dans un fichier texte et, dans la suite du projet,
une interface graphique avec Qt.

## Structure

```text
src/
  models/        Classes Student, UndergraduateStudent, GraduateStudent, PhDStudent
  services/      StudentManager et logique metier
  exceptions/    Exceptions personnalisees
  persistence/   Sauvegarde et chargement des donnees
data/
  students.txt   Fichier de donnees
tests/
  test_main.cpp  Tests console
```

## Compilation

```bash
make clean
make
./program
```

Le programme lance actuellement les tests console du projet.

## Fonctionnalites deja implementees

- Hierarchie de classes avec `Student` abstraite et trois classes derivees.
- Calcul de bourse selon le type d'etudiant.
- Affichage formate des informations d'un etudiant.
- Validation des ID et GPA avec exceptions personnalisees.
- Gestion des etudiants avec `StudentManager` :
  - ajout,
  - suppression,
  - modification,
  - recherche par ID,
  - recherche partielle par nom,
  - tri par GPA,
  - tri par nom,
  - moyenne GPA,
  - nombre d'etudiants par type.
- Sauvegarde et chargement des etudiants avec `PersistenceManager`.
- Tests console couvrant les cas principaux et les erreurs demandees.

## Donnees

Le format de `data/students.txt` est :

```text
Licence|1001|Benali Amira|3.8|Informatique
Master|1002|Cherif Omar|3.5|IA
Doctorat|1003|Meziane Riad|3.9|Dr. Hadj|2
```

Les lignes incorrectes sont ignorees au chargement pour eviter que le programme s'arrete sur un fichier abime.

## Suite du travail

La base console est prete pour brancher l'interface graphique Qt : tableau des etudiants, recherche,
ajout, modification, suppression et affichage des erreurs dans des boites de dialogue.

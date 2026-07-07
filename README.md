# Mini Projet C++ - Systeme de Gestion des Etudiants

Ce projet est une application C++ orientee objet pour gerer des etudiants de plusieurs niveaux :
Licence, Master et Doctorat. Le but est de pratiquer l'heritage, le polymorphisme, les conteneurs STL,
les exceptions personnalisees, la persistance dans un fichier texte et une interface graphique avec Qt.

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

### Tests console

```bash
make clean
make
./program
```

Le programme console lance les tests du projet.

### Interface Qt

Avec Qt5 ou Qt6 installe :

```bash
qmake Student_Manager.pro
make
./Student_Manager
```

L'application charge automatiquement `data/students.txt` au demarrage et sauvegarde apres chaque
ajout, modification ou suppression.

## Fonctionnalites

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
- Interface Qt :
  - tableau ID, nom, type, GPA et bourse,
  - recherche dynamique,
  - ajout, modification et suppression,
  - messages d'erreur via boites de dialogue,
  - barre de statut avec nombre d'etudiants et moyenne GPA.
- Tests console couvrant les cas principaux, les erreurs demandees et la persistance.

## Donnees

Le format de `data/students.txt` est :

```text
Licence|1001|Benali Amira|3.8|Informatique
Master|1002|Cherif Omar|3.5|IA
Doctorat|1003|Meziane Riad|3.9|Dr. Hadj|2
```

Les lignes incorrectes sont ignorees au chargement pour eviter que le programme s'arrete sur un fichier abime.

## Tests couverts

- Creation des trois types d'etudiants.
- Calcul des bourses.
- Ajout, modification, suppression et recherche.
- Tri par GPA et par nom.
- Exceptions : ID invalide, GPA invalide, ID duplique, etudiant introuvable.
- Sauvegarde, rechargement, fichier absent et lignes corrompues.

## Notes pour le rendu

Pour completer le rendu final, il reste surtout la partie hors code :

- ajouter les noms du binome dans ce README ;
- enregistrer la video de demonstration ;
- preparer le rapport PDF avec UML, captures d'ecran et tableau de tests.

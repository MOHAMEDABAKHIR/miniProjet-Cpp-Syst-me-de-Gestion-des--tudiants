#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "src/exceptions/StudentExceptions.h"
#include "src/models/GraduateStudent.h"
#include "src/models/PhDStudent.h"
#include "src/models/UndergraduateStudent.h"
#include "src/persistence/PersistenceManager.h"
#include "src/services/StudentManager.h"

using namespace std;

void check(bool condition, const string& message) {
    if (!condition) {
        throw runtime_error(message);
    }
    cout << "[OK] " << message << endl;
}

void testModels() {
    UndergraduateStudent licence("Benali Amira", 1001, 3.8f, "Informatique");
    GraduateStudent master("Cherif Omar", 1002, 3.5f, "IA");
    PhDStudent doctorant("Meziane Riad", 1003, 3.9f, "Dr. Hadj", 2);

    check(licence.getType() == "Licence", "type Licence");
    check(master.getType() == "Master", "type Master");
    check(doctorant.getType() == "Doctorat", "type Doctorat");

    check(licence.computeScholarship() == 500, "bourse Licence avec bon GPA");
    check(master.computeScholarship() == 1050, "bourse Master calculee avec le GPA");
    check(doctorant.computeScholarship() == 1200, "bourse Doctorat fixe");
}

StudentManager createManager() {
    StudentManager manager;
    manager.add(make_shared<UndergraduateStudent>("Benali Amira", 1001, 3.8f, "Informatique"));
    manager.add(make_shared<GraduateStudent>("Cherif Omar", 1002, 3.5f, "IA"));
    manager.add(make_shared<PhDStudent>("Meziane Riad", 1003, 3.9f, "Dr. Hadj", 2));
    manager.add(make_shared<UndergraduateStudent>("Nouri Sara", 1004, 2.9f, "Maths"));
    manager.add(make_shared<GraduateStudent>("Alaoui Yassine", 1005, 3.1f, "Reseaux"));
    return manager;
}

void testManager() {
    StudentManager manager = createManager();

    check(manager.count() == 5, "ajout de cinq etudiants");
    check(manager.findById(1002)->getName() == "Cherif Omar", "recherche par ID");
    check(manager.findByName("am").size() == 1, "recherche partielle par nom");
    check(manager.findByName("BENALI").size() == 1, "recherche par nom sans tenir compte de la casse");
    check(manager.countByType("Licence") == 2, "statistique par type");

    manager.update(1004, make_shared<UndergraduateStudent>("Nouri Sara", 1004, 3.2f, "Maths"));
    check(manager.findById(1004)->getGpa() == 3.2f, "modification d'un etudiant");

    manager.remove(1005);
    check(manager.count() == 4, "suppression d'un etudiant");

    vector<shared_ptr<Student> > byGpa = manager.sortByGpa();
    check(byGpa.front()->getGpa() >= byGpa.back()->getGpa(), "tri GPA decroissant");

    vector<shared_ptr<Student> > byName = manager.sortByName();
    check(byName.front()->getName() == "Benali Amira", "tri alphabetique par nom");

    check(manager.averageGpa() > 3.0, "calcul de la moyenne GPA");
}

void testExceptions() {
    try {
        UndergraduateStudent badId("Test", 42, 3.0f, "Info");
        check(false, "ID invalide detecte");
    } catch (const InvalidIDException&) {
        check(true, "ID invalide detecte");
    }

    try {
        UndergraduateStudent badGpa("Test", 1200, 5.5f, "Info");
        check(false, "GPA invalide detecte");
    } catch (const InvalidGradeException&) {
        check(true, "GPA invalide detecte");
    }

    StudentManager manager;
    manager.add(make_shared<GraduateStudent>("Cherif Omar", 1002, 3.5f, "IA"));

    try {
        manager.add(make_shared<GraduateStudent>("Autre Etudiant", 1002, 3.2f, "BD"));
        check(false, "ID duplique detecte");
    } catch (const DuplicateIDException&) {
        check(true, "ID duplique detecte");
    }

    try {
        manager.update(1002, make_shared<GraduateStudent>("Autre Etudiant", 1002, 3.1f, "BD"));
        manager.add(make_shared<UndergraduateStudent>("Benali Amira", 1003, 3.6f, "Info"));
        manager.update(1003, make_shared<UndergraduateStudent>("Benali Amira", 1002, 3.6f, "Info"));
        check(false, "ID duplique detecte pendant une modification");
    } catch (const DuplicateIDException&) {
        check(true, "ID duplique detecte pendant une modification");
    }

    try {
        manager.remove(9999);
        check(false, "etudiant introuvable detecte");
    } catch (const StudentNotFoundException&) {
        check(true, "etudiant introuvable detecte");
    }
}

void testPersistence() {
    const string path = "data/test_students.txt";
    StudentManager manager = createManager();
    PersistenceManager::save(manager, path);

    StudentManager loaded;
    PersistenceManager::load(loaded, path);

    check(loaded.count() == manager.count(), "chargement du meme nombre d'etudiants");
    check(loaded.findById(1003)->getType() == "Doctorat", "chargement d'un doctorant");
    check(loaded.findById(1001)->getName() == "Benali Amira", "chargement des donnees correctes");

    remove(path.c_str());

    StudentManager missing = createManager();
    PersistenceManager::load(missing, "data/fichier_absent.txt");
    check(missing.count() == 0, "fichier absent charge une liste vide");

    const string corruptPath = "data/test_students_corrupt.txt";
    ofstream corruptFile(corruptPath.c_str());
    corruptFile << "Licence|1008|Etudiant Correct|3.7|Info\n";
    corruptFile << "Ligne vraiment incomplete\n";
    corruptFile << "Doctorat|44|ID Trop Petit|3.5|Dr. Test|2\n";
    corruptFile << "Master|1009|GPA Faux|6.2|IA\n";
    corruptFile.close();

    StudentManager corruptLoaded;
    PersistenceManager::load(corruptLoaded, corruptPath);
    check(corruptLoaded.count() == 1, "lignes corrompues ignorees au chargement");
    check(corruptLoaded.findById(1008)->getType() == "Licence", "ligne correcte conservee apres erreurs");

    remove(corruptPath.c_str());
}

int main() {
    try {
        cout << "Tests du systeme de gestion des etudiants" << endl;
        testModels();
        testManager();
        testExceptions();
        testPersistence();
        cout << "Tous les tests sont passes." << endl;
        return 0;
    } catch (const exception& e) {
        cerr << "[ECHEC] " << e.what() << endl;
        return 1;
    }
}

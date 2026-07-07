#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

class Student {
protected:
    string name;    // Nom complet de l’étudiant
    int id;    // Identifiant unique (>= 1000)
    float gpa;    // Note globale entre 0.0 et 4.0

public:
    Student(const string& name, int id, float gpa);

    // Méthodes pures : chaque classe dérivée DOIT les implémenter
    virtual void display() const = 0;
    virtual string getType() const = 0;
    virtual double computeScholarship() const = 0;

    // Accesseurs
    string getName() const;
    int getID() const;
    int getId() const;
    float getGpa() const;

    // Mutateurs avec validation interne
    void setName(const string& n);
    void setGpa(float g); // Lance InvalidGradeException si hors [0,4]

    virtual ~Student() {}
};

#endif

#include "student.h"
#include "../exceptions/StudentExceptions.h"

Student::Student(const string& name , int id , float gpa):
    name(name), id(id), gpa(gpa){
    if (id < 1000) {
        throw InvalidIDException(id);
    }
    if (gpa < 0.0f || gpa > 4.0f) {
        throw InvalidGradeException(gpa);
    }
}

void Student::setName(const string& nom){
    name=nom;
}

void Student::setGpa(float moyenne){
    if (moyenne < 0.0f || moyenne > 4.0f) {
        throw InvalidGradeException(moyenne);
    }
    gpa=moyenne;
}

string Student::getName() const {
    return name;
}

int Student::getID() const {
    return id;
}

int Student::getId() const {
    return id;
}

float Student::getGpa() const {
    return gpa;
}



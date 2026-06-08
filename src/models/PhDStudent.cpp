#include "PhDStudent.h"
#include <iostream>
PhDStudent::PhDStudent(const string& name, int id, float gpa,const string& supervisor,int yearOfStudy):
    Student(name, id, gpa),supervisor(supervisor),yearOfStudy(yearOfStudy){

    };
string PhDStudent::getType() const{
    return "Doctorat";
} ;
double PhDStudent::computeScholarship() const{
    return 1200;
};   
void PhDStudent::display() const{
    cout << getType() << "|";
    cout << "ID:" << id << "|";
    cout << "Nom:" << name << "|";
    cout << "GPA:" << gpa << "|";
    cout << "Superviseur:" << supervisor << "|";
    cout << "Année d'étude:" << yearOfStudy << "|";
    cout << "Bourse:" << computeScholarship() << " EUR" ;
};  
#include "GraduateStudent.h"
#include <iostream>
GraduateStudent::GraduateStudent(const string& name, int id , float gpa , const string& researchTopic):
    Student(name, id, gpa), researchTopic(researchTopic){

    };
double GraduateStudent::computeScholarship() const{
    return gpa*300;
};
string GraduateStudent::getType() const{
    return "Master";
};
void GraduateStudent::display() const{
    cout << getType() << "|";
    cout << "ID:" << id << "|";
    cout << "Nom:" << name << "|";
    cout << "GPA:" << gpa << "|";
    cout << "Sujet:" << researchTopic << "|";
    cout << "Bourse:" << computeScholarship() << " EUR" ;
};    
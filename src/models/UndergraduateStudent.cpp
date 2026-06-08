#include "UndergraduateStudent.h"
#include <iostream>
UndergraduateStudent::UndergraduateStudent(const string& name, int id, float gpa,const string& major):
    Student(name,id,gpa),major(major){
        
    };
string UndergraduateStudent::getType()const {
    return "Licence";
};
double UndergraduateStudent::computeScholarship() const{
    if (gpa>=3.5)
        return 500;
    return 0;
};
void UndergraduateStudent::display() const{
    cout << "[Licence]";
    cout << "ID:" << id << "|";
    cout << "Nom:" << name << "|";
    cout << "GPA:" << gpa << "|";
    cout << "Filiére:" << major << "|";
    cout << "Bourse:" << computeScholarship() << " EUR" ;

};

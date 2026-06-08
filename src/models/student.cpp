#include "student.h"
Student::Student(const string& name , int id , float gpa):
    name(name), id(id), gpa(gpa){

    };
void Student::setName(const string& nom){
    name=nom;
};
void Student::setGpa(float moyenne){
    gpa=moyenne;
};



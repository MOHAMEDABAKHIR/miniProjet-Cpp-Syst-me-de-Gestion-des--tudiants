#ifndef UndergraduateStudent_H
#define UndergraduateStudent_H
#include "student.h"
using namespace std;
class UndergraduateStudent: public Student {
    private:
        string major;
    public:
        UndergraduateStudent(const string& name, int id , float gpa ,const string& major);
        void display() const override;
        string getType() const override;
        double computeScholarship() const override;
};
#endif
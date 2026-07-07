#ifndef PhDStudent_H
#define PhDStudent_H
#include "student.h"
class PhDStudent: public Student{
    private:
        string supervisor;
        int yearOfStudy;
    public:
    PhDStudent(const string& name, int id ,float gpa,const string& supervisor,int yearOfStudy);
    void display() const override;
    string getType() const override;
    double computeScholarship() const override;
    string getSupervisor() const;
    int getYearOfStudy() const;
};
#endif

#ifndef GraduateStudent_H
#define GraduateStudent_H
#include "student.h"
class GraduateStudent: public Student {
    private: 
        string researchTopic;
    public:
        GraduateStudent(const string& name, int id, float gpa, const string& researchTopic);
        void display() const override;
        string getType() const override;
        double computeScholarship() const override;
        string getResearchTopic() const;
};

#endif

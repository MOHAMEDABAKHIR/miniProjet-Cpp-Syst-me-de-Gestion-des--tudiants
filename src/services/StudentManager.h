#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../models/student.h"

class StudentManager {
private:
    map<int, shared_ptr<Student> > students;

public:
    void add(shared_ptr<Student> s);
    void remove(int id);
    void update(int id, shared_ptr<Student> updated);

    shared_ptr<Student> findById(int id) const;
    vector<shared_ptr<Student> > findByName(const string& name) const;

    vector<shared_ptr<Student> > sortByGpa() const;
    vector<shared_ptr<Student> > sortByName() const;

    double averageGpa() const;
    int countByType(const string& type) const;
    int count() const;
    void clear();

    const map<int, shared_ptr<Student> >& getAll() const;
};

#endif

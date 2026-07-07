#include "StudentManager.h"

#include <algorithm>
#include <cctype>

#include "../exceptions/StudentExceptions.h"

namespace {
string toLowerCopy(const string& value) {
    string result = value;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return static_cast<char>(tolower(c));
    });
    return result;
}

vector<shared_ptr<Student> > asVector(const map<int, shared_ptr<Student> >& students) {
    vector<shared_ptr<Student> > result;
    for (const auto& item : students) {
        result.push_back(item.second);
    }
    return result;
}
}

void StudentManager::add(shared_ptr<Student> s) {
    int id = s->getID();
    if (students.find(id) != students.end()) {
        throw DuplicateIDException(id);
    }
    students[id] = s;
}

void StudentManager::remove(int id) {
    auto it = students.find(id);
    if (it == students.end()) {
        throw StudentNotFoundException(id);
    }
    students.erase(it);
}

void StudentManager::update(int id, shared_ptr<Student> updated) {
    auto it = students.find(id);
    if (it == students.end()) {
        throw StudentNotFoundException(id);
    }

    int newId = updated->getID();
    if (newId != id && students.find(newId) != students.end()) {
        throw DuplicateIDException(newId);
    }

    students.erase(it);
    students[newId] = updated;
}

shared_ptr<Student> StudentManager::findById(int id) const {
    auto it = students.find(id);
    if (it == students.end()) {
        throw StudentNotFoundException(id);
    }
    return it->second;
}

vector<shared_ptr<Student> > StudentManager::findByName(const string& name) const {
    vector<shared_ptr<Student> > result;
    string searched = toLowerCopy(name);

    for (const auto& item : students) {
        string currentName = toLowerCopy(item.second->getName());
        if (currentName.find(searched) != string::npos) {
            result.push_back(item.second);
        }
    }
    return result;
}

vector<shared_ptr<Student> > StudentManager::sortByGpa() const {
    vector<shared_ptr<Student> > result = asVector(students);
    sort(result.begin(), result.end(), [](const shared_ptr<Student>& a, const shared_ptr<Student>& b) {
        return a->getGpa() > b->getGpa();
    });
    return result;
}

vector<shared_ptr<Student> > StudentManager::sortByName() const {
    vector<shared_ptr<Student> > result = asVector(students);
    sort(result.begin(), result.end(), [](const shared_ptr<Student>& a, const shared_ptr<Student>& b) {
        return toLowerCopy(a->getName()) < toLowerCopy(b->getName());
    });
    return result;
}

double StudentManager::averageGpa() const {
    if (students.empty()) {
        return 0.0;
    }

    double total = 0.0;
    for (const auto& item : students) {
        total += item.second->getGpa();
    }
    return total / students.size();
}

int StudentManager::countByType(const string& type) const {
    return static_cast<int>(count_if(students.begin(), students.end(), [&type](const pair<const int, shared_ptr<Student> >& item) {
        return item.second->getType() == type;
    }));
}

int StudentManager::count() const {
    return static_cast<int>(students.size());
}

void StudentManager::clear() {
    students.clear();
}

const map<int, shared_ptr<Student> >& StudentManager::getAll() const {
    return students;
}

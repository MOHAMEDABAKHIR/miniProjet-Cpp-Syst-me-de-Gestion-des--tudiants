#include "PersistenceManager.h"

#include <fstream>
#include <memory>
#include <sstream>
#include <vector>

#include "../models/GraduateStudent.h"
#include "../models/PhDStudent.h"
#include "../models/UndergraduateStudent.h"

namespace {
string trim(const string& value) {
    size_t start = value.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        return "";
    }

    size_t end = value.find_last_not_of(" \t\r\n");
    return value.substr(start, end - start + 1);
}

vector<string> splitLine(const string& line) {
    vector<string> parts;
    string token;
    stringstream ss(line);

    while (getline(ss, token, '|')) {
        parts.push_back(trim(token));
    }

    return parts;
}
}

void PersistenceManager::save(const StudentManager& manager, const string& path) {
    ofstream file(path.c_str());
    if (!file) {
        return;
    }

    for (const auto& item : manager.getAll()) {
        shared_ptr<Student> student = item.second;
        file << student->getType() << "|"
             << student->getID() << "|"
             << student->getName() << "|"
             << student->getGpa();

        if (student->getType() == "Licence") {
            shared_ptr<UndergraduateStudent> licence = dynamic_pointer_cast<UndergraduateStudent>(student);
            if (licence) {
                file << "|" << licence->getMajor();
            }
        } else if (student->getType() == "Master") {
            shared_ptr<GraduateStudent> master = dynamic_pointer_cast<GraduateStudent>(student);
            if (master) {
                file << "|" << master->getResearchTopic();
            }
        } else if (student->getType() == "Doctorat") {
            shared_ptr<PhDStudent> phd = dynamic_pointer_cast<PhDStudent>(student);
            if (phd) {
                file << "|" << phd->getSupervisor()
                     << "|" << phd->getYearOfStudy();
            }
        }

        file << '\n';
    }
}

void PersistenceManager::load(StudentManager& manager, const string& path) {
    ifstream file(path.c_str());
    if (!file) {
        manager.clear();
        return;
    }

    StudentManager loaded;
    string line;

    while (getline(file, line)) {
        try {
            vector<string> parts = splitLine(line);
            if (parts.size() < 5) {
                continue;
            }

            string type = parts[0];
            int id = stoi(parts[1]);
            string name = parts[2];
            float gpa = stof(parts[3]);

            if (type == "Licence" && parts.size() >= 5) {
                loaded.add(make_shared<UndergraduateStudent>(name, id, gpa, parts[4]));
            } else if (type == "Master" && parts.size() >= 5) {
                loaded.add(make_shared<GraduateStudent>(name, id, gpa, parts[4]));
            } else if (type == "Doctorat" && parts.size() >= 6) {
                loaded.add(make_shared<PhDStudent>(name, id, gpa, parts[4], stoi(parts[5])));
            }
        } catch (...) {
            // Une ligne abimee ne doit pas empecher le chargement du reste.
        }
    }

    manager = loaded;
}

#ifndef STUDENT_EXCEPTIONS_H
#define STUDENT_EXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

class InvalidIDException : public exception {
private:
    string msg;

public:
    explicit InvalidIDException(int id)
        : msg("ID invalide (doit etre >= 1000) : " + to_string(id)) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class InvalidGradeException : public exception {
private:
    string msg;

public:
    explicit InvalidGradeException(float gpa)
        : msg("GPA hors plage [0.0 - 4.0] : " + to_string(gpa)) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class StudentNotFoundException : public exception {
private:
    string msg;

public:
    explicit StudentNotFoundException(int id)
        : msg("Etudiant introuvable avec ID : " + to_string(id)) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class DuplicateIDException : public exception {
private:
    string msg;

public:
    explicit DuplicateIDException(int id)
        : msg("ID deja utilise : " + to_string(id)) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

#endif

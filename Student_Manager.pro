QT += widgets

CONFIG += c++11

TEMPLATE = app
TARGET = Student_Manager

SOURCES += \
    src/gui/StudentDialog.cpp \
    src/models/student.cpp \
    src/models/UndergraduateStudent.cpp \
    src/models/GraduateStudent.cpp \
    src/models/PhDStudent.cpp \
    src/services/StudentManager.cpp \
    src/persistence/PersistenceManager.cpp

HEADERS += \
    src/gui/StudentDialog.h \
    src/exceptions/StudentExceptions.h \
    src/models/student.h \
    src/models/UndergraduateStudent.h \
    src/models/GraduateStudent.h \
    src/models/PhDStudent.h \
    src/services/StudentManager.h \
    src/persistence/PersistenceManager.h

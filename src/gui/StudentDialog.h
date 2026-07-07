#ifndef STUDENT_DIALOG_H
#define STUDENT_DIALOG_H

#include <memory>

#include <QComboBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>

#include "../models/GraduateStudent.h"
#include "../models/PhDStudent.h"
#include "../models/UndergraduateStudent.h"

class StudentDialog : public QDialog {
    Q_OBJECT

public:
    explicit StudentDialog(QWidget* parent = nullptr);
    explicit StudentDialog(std::shared_ptr<Student> student, QWidget* parent = nullptr);

    std::shared_ptr<Student> buildStudent() const;

private slots:
    void updateExtraFields();

private:
    void setupUi();
    void fillFromStudent(std::shared_ptr<Student> student);

    QComboBox* typeCombo;
    QLineEdit* nameEdit;
    QSpinBox* idSpin;
    QDoubleSpinBox* gpaSpin;
    QLineEdit* extraEdit;
    QSpinBox* yearSpin;
    QFormLayout* formLayout;
};

#endif

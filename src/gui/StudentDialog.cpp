#include "StudentDialog.h"

#include <QDialogButtonBox>
#include <QVBoxLayout>

StudentDialog::StudentDialog(QWidget* parent)
    : QDialog(parent),
      typeCombo(nullptr),
      nameEdit(nullptr),
      idSpin(nullptr),
      gpaSpin(nullptr),
      extraEdit(nullptr),
      yearSpin(nullptr),
      formLayout(nullptr) {
    setupUi();
}

StudentDialog::StudentDialog(std::shared_ptr<Student> student, QWidget* parent)
    : StudentDialog(parent) {
    fillFromStudent(student);
}

void StudentDialog::setupUi() {
    setWindowTitle("Etudiant");
    setMinimumWidth(360);

    typeCombo = new QComboBox(this);
    typeCombo->addItem("Licence");
    typeCombo->addItem("Master");
    typeCombo->addItem("Doctorat");

    nameEdit = new QLineEdit(this);
    idSpin = new QSpinBox(this);
    idSpin->setRange(1000, 999999);

    gpaSpin = new QDoubleSpinBox(this);
    gpaSpin->setRange(0.0, 4.0);
    gpaSpin->setSingleStep(0.1);
    gpaSpin->setDecimals(2);

    extraEdit = new QLineEdit(this);
    yearSpin = new QSpinBox(this);
    yearSpin->setRange(1, 10);

    formLayout = new QFormLayout;
    formLayout->addRow("Type", typeCombo);
    formLayout->addRow("Nom", nameEdit);
    formLayout->addRow("ID", idSpin);
    formLayout->addRow("GPA", gpaSpin);
    formLayout->addRow("Filiere", extraEdit);
    formLayout->addRow("Annee", yearSpin);

    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &StudentDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &StudentDialog::reject);
    connect(typeCombo, &QComboBox::currentTextChanged, this, &StudentDialog::updateExtraFields);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(formLayout);
    layout->addWidget(buttons);

    updateExtraFields();
}

void StudentDialog::fillFromStudent(std::shared_ptr<Student> student) {
    if (!student) {
        return;
    }

    typeCombo->setCurrentText(QString::fromStdString(student->getType()));
    nameEdit->setText(QString::fromStdString(student->getName()));
    idSpin->setValue(student->getID());
    gpaSpin->setValue(student->getGpa());

    if (student->getType() == "Licence") {
        std::shared_ptr<UndergraduateStudent> licence = std::dynamic_pointer_cast<UndergraduateStudent>(student);
        if (licence) {
            extraEdit->setText(QString::fromStdString(licence->getMajor()));
        }
    } else if (student->getType() == "Master") {
        std::shared_ptr<GraduateStudent> master = std::dynamic_pointer_cast<GraduateStudent>(student);
        if (master) {
            extraEdit->setText(QString::fromStdString(master->getResearchTopic()));
        }
    } else {
        std::shared_ptr<PhDStudent> phd = std::dynamic_pointer_cast<PhDStudent>(student);
        if (phd) {
            extraEdit->setText(QString::fromStdString(phd->getSupervisor()));
            yearSpin->setValue(phd->getYearOfStudy());
        }
    }
}

std::shared_ptr<Student> StudentDialog::buildStudent() const {
    std::string type = typeCombo->currentText().toStdString();
    std::string name = nameEdit->text().trimmed().toStdString();
    int id = idSpin->value();
    float gpa = static_cast<float>(gpaSpin->value());
    std::string extra = extraEdit->text().trimmed().toStdString();

    if (type == "Licence") {
        return std::make_shared<UndergraduateStudent>(name, id, gpa, extra);
    }
    if (type == "Master") {
        return std::make_shared<GraduateStudent>(name, id, gpa, extra);
    }
    return std::make_shared<PhDStudent>(name, id, gpa, extra, yearSpin->value());
}

void StudentDialog::updateExtraFields() {
    QString type = typeCombo->currentText();
    formLayout->labelForField(extraEdit)->setText(type == "Doctorat" ? "Superviseur" : (type == "Master" ? "Sujet" : "Filiere"));
    yearSpin->setVisible(type == "Doctorat");
    formLayout->labelForField(yearSpin)->setVisible(type == "Doctorat");
}

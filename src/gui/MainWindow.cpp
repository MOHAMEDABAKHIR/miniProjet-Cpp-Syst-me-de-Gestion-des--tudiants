#include "MainWindow.h"

#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>

#include "../exceptions/StudentExceptions.h"
#include "../persistence/PersistenceManager.h"
#include "StudentDialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      dataPath("data/students.txt"),
      searchEdit(nullptr),
      table(nullptr),
      addButton(nullptr),
      editButton(nullptr),
      removeButton(nullptr),
      refreshButton(nullptr) {
    setupUi();
    loadStudents();
    refreshTable();
}

void MainWindow::setupUi() {
    setWindowTitle("Gestion des etudiants");
    resize(860, 520);

    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);

    QToolBar* toolbar = new QToolBar(this);
    toolbar->setMovable(false);

    addButton = new QPushButton("+ Ajouter", this);
    editButton = new QPushButton("Modifier", this);
    removeButton = new QPushButton("Supprimer", this);
    refreshButton = new QPushButton("Rafraichir", this);

    toolbar->addWidget(addButton);
    toolbar->addWidget(editButton);
    toolbar->addWidget(removeButton);
    toolbar->addSeparator();
    toolbar->addWidget(refreshButton);

    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Rechercher un etudiant...");

    table = new QTableWidget(this);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(QStringList() << "ID" << "Nom" << "Type" << "GPA" << "Bourse");
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);

    layout->addWidget(toolbar);
    layout->addWidget(new QLabel("Recherche", this));
    layout->addWidget(searchEdit);
    layout->addWidget(table);
    setCentralWidget(central);

    statusBar();

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addStudent);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editStudent);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeStudent);
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshTable);
    connect(searchEdit, &QLineEdit::textChanged, this, &MainWindow::filterTable);
    connect(table, &QTableWidget::cellDoubleClicked, this, &MainWindow::editStudent);
}

void MainWindow::loadStudents() {
    PersistenceManager::load(manager, dataPath.toStdString());
}

void MainWindow::saveStudents() {
    PersistenceManager::save(manager, dataPath.toStdString());
}

QTableWidgetItem* MainWindow::makeCell(const QString& text) const {
    QTableWidgetItem* item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

void MainWindow::refreshTable() {
    table->setRowCount(0);

    std::vector<std::shared_ptr<Student> > students = manager.sortByName();
    for (const std::shared_ptr<Student>& student : students) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, makeCell(QString::number(student->getID())));
        table->setItem(row, 1, makeCell(QString::fromStdString(student->getName())));
        table->setItem(row, 2, makeCell(QString::fromStdString(student->getType())));
        table->setItem(row, 3, makeCell(QString::number(student->getGpa(), 'f', 2)));
        table->setItem(row, 4, makeCell(QString::number(student->computeScholarship(), 'f', 2) + " EUR"));
    }

    filterTable(searchEdit->text());
    updateStatus();
}

void MainWindow::filterTable(const QString& text) {
    QString searched = text.trimmed().toLower();

    for (int row = 0; row < table->rowCount(); ++row) {
        bool visible = searched.isEmpty();
        for (int col = 0; col < table->columnCount() && !visible; ++col) {
            QTableWidgetItem* item = table->item(row, col);
            visible = item && item->text().toLower().contains(searched);
        }
        table->setRowHidden(row, !visible);
    }
}

void MainWindow::addStudent() {
    StudentDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    try {
        manager.add(dialog.buildStudent());
        saveStudents();
        refreshTable();
        statusBar()->showMessage("Etudiant ajoute avec succes.", 3000);
    } catch (const std::exception& e) {
        showStudentError(e);
    }
}

void MainWindow::editStudent() {
    int id = selectedStudentId();
    if (id < 0) {
        QMessageBox::information(this, "Modification", "Selectionnez d'abord un etudiant.");
        return;
    }

    try {
        std::shared_ptr<Student> student = manager.findById(id);
        StudentDialog dialog(student, this);
        if (dialog.exec() != QDialog::Accepted) {
            return;
        }

        manager.update(id, dialog.buildStudent());
        saveStudents();
        refreshTable();
        statusBar()->showMessage("Etudiant modifie avec succes.", 3000);
    } catch (const std::exception& e) {
        showStudentError(e);
    }
}

void MainWindow::removeStudent() {
    int id = selectedStudentId();
    if (id < 0) {
        QMessageBox::information(this, "Suppression", "Selectionnez d'abord un etudiant.");
        return;
    }

    int answer = QMessageBox::question(this, "Suppression", "Supprimer cet etudiant ?");
    if (answer != QMessageBox::Yes) {
        return;
    }

    try {
        manager.remove(id);
        saveStudents();
        refreshTable();
        statusBar()->showMessage("Etudiant supprime avec succes.", 3000);
    } catch (const std::exception& e) {
        showStudentError(e);
    }
}

int MainWindow::selectedStudentId() const {
    QList<QTableWidgetItem*> selected = table->selectedItems();
    if (selected.isEmpty()) {
        return -1;
    }

    int row = selected.first()->row();
    QTableWidgetItem* idItem = table->item(row, 0);
    if (!idItem) {
        return -1;
    }
    return idItem->text().toInt();
}

void MainWindow::updateStatus() {
    statusBar()->showMessage(QString("%1 etudiant(s) | Moyenne GPA : %2")
                                 .arg(manager.count())
                                 .arg(manager.averageGpa(), 0, 'f', 2));
}

void MainWindow::showStudentError(const std::exception& e) {
    QMessageBox::warning(this, "Erreur", QString::fromStdString(e.what()));
}

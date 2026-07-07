#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <memory>

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>

#include "../services/StudentManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void addStudent();
    void editStudent();
    void removeStudent();
    void refreshTable();
    void filterTable(const QString& text);

private:
    void setupUi();
    void loadStudents();
    void saveStudents();
    void updateStatus();
    int selectedStudentId() const;
    void showStudentError(const std::exception& e);
    QTableWidgetItem* makeCell(const QString& text) const;

    StudentManager manager;
    QString dataPath;

    QLineEdit* searchEdit;
    QTableWidget* table;
    QPushButton* addButton;
    QPushButton* editButton;
    QPushButton* removeButton;
    QPushButton* refreshButton;
};

#endif

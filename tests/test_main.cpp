#include <iostream>
#include "src/models/student.h"
#include "src/models/GraduateStudent.h"
#include "src/models/UndergraduateStudent.h"
#include "src/models/PhDStudent.h"
int main() {
    cout<< "les testes de la 1ere partie :" << endl;
    GraduateStudent MohamedABAKHIR("Mohamed Abakhir",1002,3.6,"IA");
    UndergraduateStudent MohamedAli("Mohamed Ali",1009,2.6,"Informatique");
    PhDStudent SaidKhalid("Said Khalid",1019,3.9,"Samir Kholdi",3);
    MohamedABAKHIR.display();
    cout << endl << "La bourse de :" << MohamedABAKHIR.getName() << " est: " << MohamedABAKHIR.computeScholarship() << endl;
    MohamedAli.display();
    cout <<  endl << "La bourse de :" << MohamedAli.getName() << " est: " << MohamedAli.computeScholarship() << endl;
    SaidKhalid.display();
    cout <<  endl << "La bourse de :" << SaidKhalid.getName() << "est: " << MohamedABAKHIR.computeScholarship() << endl;
};
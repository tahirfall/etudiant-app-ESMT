#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <QString>
class Etudiant
{
private:
    int id;
    QString firstName;
    QString lastName;
    QString sexe;
    QString classe;
    QString filiere;
    QString option;
    QString yearAcademic;

public:
    //Declaration des constructeurs
    Etudiant();
    Etudiant(int id, QString firstName, QString lastName, QString sexe, QString classe,
             QString filiere, QString option, QString yearAcademic);
    Etudiant(QString firstName, QString lastName, QString sexe, QString classe,
             QString filiere, QString option, QString yearAcademic);

    //Declarations et definitions des Getters
    int getId(){ return id; }
    QString getFirstName(){ return firstName; }
    QString getLastname(){ return  lastName; }
    QString getSexe(){ return sexe; }
    QString getClass(){ return classe; }
    QString getOption(){ return option; }
    QString getFiliere(){ return filiere; }
    QString getYearAcademic(){ return yearAcademic; }

    //Declarations et definitions des Setters
    void setId(int val_id){ id = val_id; }
    void setFirstName(QString fName_val){ firstName = fName_val; }
    void setLastName(QString lName_val){ lastName = lName_val; }
    void setSexe(QString sexe_val){ sexe = sexe_val; }
    void setClass(QString class_val){ classe = class_val; }
    void setOption(QString option_val){ classe = option_val; }
    void setFiliere(QString filiere_val){ filiere = filiere_val; }
    void setYearAcademic(QString yearAcademic_val){ yearAcademic = yearAcademic_val; }



};

#endif // ETUDIANT_H

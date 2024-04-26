#include "etudiant.h"

Etudiant::Etudiant()
{

}

Etudiant::Etudiant(int id, QString firstName, QString lastName, QString sexe, QString classe,
                    QString filiere, QString option, QString yearAcademic):
    id(id), firstName(firstName), lastName(lastName), sexe(sexe), classe(classe),
    filiere(filiere), option(option), yearAcademic(yearAcademic)
{

}

Etudiant::Etudiant(QString firstName, QString lastName, QString sexe, QString classe,
                   QString filiere, QString option, QString yearAcademic):
    firstName(firstName), lastName(lastName), sexe(sexe), classe(classe),
    filiere(filiere), option(option), yearAcademic(yearAcademic)
{

}

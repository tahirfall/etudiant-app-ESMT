#include "service.h"
#include <QMetaType>
#include <QSqlField>
#include <QtDebug>
#include <QList>

Service::Service()
{
    selectionModel = new QItemSelectionModel(this);
    dbaccess = DBAccess::getInstance();
}



Service::~Service()
{
    delete dbaccess;
}


void Service::Create(Etudiant etudiant)
{
    dbaccess->open();
    QSqlQuery query(dbaccess->database());

    query.prepare("INSERT INTO etudiants (firstName, lastName, sexe, class, filiere, option, yearAcademic)"
                  "VALUES (:firstName, :lastName, :sexe, :classe, :filiere, :option, :yearAcademic)");

    query.bindValue(":firstName", etudiant.getFirstName());
    query.bindValue(":lastName", etudiant.getLastname());
    query.bindValue(":sexe", etudiant.getSexe());
    query.bindValue(":classe", etudiant.getClass());
    query.bindValue(":filiere", etudiant.getFiliere());
    query.bindValue(":option", etudiant.getOption());
    query.bindValue(":yearAcademic", etudiant.getYearAcademic());

    query.exec();
     readAll();

    dbaccess->close();

}

Etudiant Service::read(int id)
{

        Etudiant etudiant;

        dbaccess->open();
        QSqlQuery query(dbaccess->database());

        query.prepare("SELECT * FROM etudiants WHERE id=:id");
        query.bindValue(":id", id);

        query.exec();

        if (query.next())
        {
            etudiant.setId(query.record().field("id").value().toInt());
            etudiant.setFirstName(query.record().field("firstname").value().toString());
            etudiant.setLastName(query.record().field("lastName").value().toString());
            etudiant.setSexe(query.record().field("sexe").value().toString());
            etudiant.setClass(query.record().field("class").value().toString());
            etudiant.setFiliere(query.record().field("filiere").value().toString());
            etudiant.setOption(query.record().field("option").value().toString());
            etudiant.setYearAcademic(query.record().field("yearAcademic").value().toString());
        }
        readAll();

        dbaccess->close();

        return etudiant;
}

void Service::_delete (int id)
{
    dbaccess->open();
    QSqlQuery query(dbaccess->database());

    query.prepare("DELETE FROM etudiants WHERE id=:id");
    query.bindValue(":id", id);

    query.exec();
     readAll();

    dbaccess->close();

}


void Service::update(Etudiant etudiant)
{
    dbaccess->open();
    QSqlQuery query(dbaccess->database());

    query.prepare("UPDATE etudiants SET firstName=:firstName, lastName=:lastName, sexe=:sexe, class=:class, filiere=:filiere, option=:option, yearAcademic=:yearAcademic WHERE id=:id");

    query.bindValue(":firstName", etudiant.getFirstName());
    query.bindValue(":lastName", etudiant.getLastname());
    query.bindValue(":sexe", etudiant.getSexe());
    query.bindValue(":class", etudiant.getClass());
    query.bindValue(":filiere", etudiant.getFiliere());
    query.bindValue(":option", etudiant.getOption());
    query.bindValue(":yearAcademic", etudiant.getYearAcademic());
    query.bindValue(":id", etudiant.getId());

    query.exec();

    dbaccess->close();
    readAll();

}


QList<Etudiant> Service::list()
{
    Etudiant etudiant;
    QList<Etudiant> etudiants;

    dbaccess->open();
    QSqlQuery query(dbaccess->database());

    query.prepare("SELECT * FROM etudiants WHERE 1");
    query.exec();

    while (query.next())
    {

        etudiant.setId(query.record().field("id").value().toInt());
        etudiant.setFirstName(query.record().field("firstname").value().toString());
        etudiant.setLastName(query.record().field("lastName").value().toString());
        etudiant.setSexe(query.record().field("sexe").value().toString());
        etudiant.setClass(query.record().field("class").value().toString());
        etudiant.setFiliere(query.record().field("filiere").value().toString());
        etudiant.setOption(query.record().field("option").value().toString());
        etudiant.setYearAcademic(query.record().field("yearAcademic").value().toString());

        etudiants.push_back(etudiant);
    }
    readAll();

    dbaccess->close();

    return etudiants;
}


void Service::remove()
{
    dbaccess->open();
    QModelIndex currentIndex = selectionModel->currentIndex();

    if(currentIndex.isValid())
    {

        int ligne = currentIndex.row();
        QSqlRecord record = this->record(ligne);

        int id = record.field(0).value().toInt();

        QSqlQuery query(dbaccess->database());

        query.prepare("DELETE from etudiants where id=:id");
        query.bindValue(":id", id);

        query.exec();
    }
    dbaccess->close();
    readAll();
}


void Service::readAll()
{

        dbaccess->open();
        QSqlDatabase database = dbaccess->database();

        this->setQuery("SELECT * FROM etudiants", database);

        this->setHeaderData(0, Qt::Horizontal, tr("Identifiant"));
        this->setHeaderData(1, Qt::Horizontal, tr("First Name"));
        this->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
        this->setHeaderData(3, Qt::Horizontal, tr("Genre"));
        this->setHeaderData(4, Qt::Horizontal, tr("Class"));
        this->setHeaderData(6, Qt::Horizontal, tr("Option"));
        this->setHeaderData(5, Qt::Horizontal, tr("Filiere"));
        this->setHeaderData(7, Qt::Horizontal, tr("Year Academic"));
        dbaccess->close();

}

/*
void Service::readOnly(int id)
{


        dbaccess->open() ;
        QSqlDatabase database = dbaccess->database() ;
        QSqlQuery query(database);
        //
        QString queryStr = "select id, firstName, lastName, sexe, class, filiere, option, yearAcademic from etudiants where id= ?";
        query.prepare(queryStr);
        query.addBindValue(id);
        //query.exec();
        query.exec();

        this->setQuery(query);
        this->setHeaderData(0, Qt::Horizontal, tr("Identifiant"));
        this->setHeaderData(1, Qt::Horizontal, tr("First Name"));
        this->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
        this->setHeaderData(3, Qt::Horizontal, tr("Sexe"));
        this->setHeaderData(4, Qt::Horizontal, tr("Class"));
        this->setHeaderData(6, Qt::Horizontal, tr("Filiere"));
        this->setHeaderData(5, Qt::Horizontal, tr("Option"));
        this->setHeaderData(7, Qt::Horizontal, tr("Year Academic"));


        dbaccess->close();

}
*/



void Service::readOnly(QString className, QString firstName, QString lastName)
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();
    QSqlQuery query(database);

    QString queryStr = "SELECT id, firstName, lastName, sexe, class, filiere, option, yearAcademic FROM etudiants WHERE ";

    QStringList conditions;
    if (!className.isEmpty()) {
        conditions << "class = ?";
    }
    if (!firstName.isEmpty()) {
        conditions << "firstName LIKE ?";
    }
    if (!lastName.isEmpty()) {
        conditions << "lastName LIKE ?";
    }

    queryStr += conditions.join(" AND ");
    query.prepare(queryStr);

    int i = 0;
    if (!className.isEmpty()) {
        query.addBindValue(className);
        i++;
    }
    if (!firstName.isEmpty()) {
        query.addBindValue("%" + firstName + "%");
        i++;
    }
    if (!lastName.isEmpty()) {
        query.addBindValue("%" + lastName + "%");
        i++;
    }

    query.exec();
    this->setQuery(query);

    this->setHeaderData(0, Qt::Horizontal, tr("Identifiant"));
    this->setHeaderData(1, Qt::Horizontal, tr("First Name"));
    this->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
    this->setHeaderData(3, Qt::Horizontal, tr("Sexe"));
    this->setHeaderData(4, Qt::Horizontal, tr("Class"));
    this->setHeaderData(5, Qt::Horizontal, tr("Filiere"));
    this->setHeaderData(6, Qt::Horizontal, tr("Option"));
    this->setHeaderData(7, Qt::Horizontal, tr("Year Academic"));

    dbaccess->close();
}


void Service::readByClass(QString className)
{
    dbaccess->open();
    QSqlDatabase database = dbaccess->database();

    QString queryStr = "SELECT * FROM etudiants WHERE class = ?";
    QSqlQuery query(database);
    query.prepare(queryStr);
    query.addBindValue(className);

    query.exec();
    this->setQuery(query);

    this->setHeaderData(0, Qt::Horizontal, tr("Identifiant"));
    this->setHeaderData(1, Qt::Horizontal, tr("First Name"));
    this->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
    this->setHeaderData(3, Qt::Horizontal, tr("Genre"));
    this->setHeaderData(4, Qt::Horizontal, tr("Class"));
    this->setHeaderData(5, Qt::Horizontal, tr("Filiere"));
    this->setHeaderData(6, Qt::Horizontal, tr("Option"));
    this->setHeaderData(7, Qt::Horizontal, tr("Year Academic"));

    dbaccess->close();
}








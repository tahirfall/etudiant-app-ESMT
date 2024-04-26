#include "dbaccess.h"

//initialisation de nullptr
DBAccess* DBAccess::instance = nullptr;

DBAccess::DBAccess()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\fallt\\Desktop\\M1-ISI-22-23\\Sem 1\\C++\\Projet Qt\\database\\etudiant.db");
    qDebug("Acces  a la base de donnes 'etudiant.db' effectif !");
    qDebug("Singleton DBAcess initialise");
}

bool DBAccess::open()
{
    if(db.isOpen() == true )
        return  true;

    if(db.open() == true )
    {
        qDebug("Connexion avec la base de données ouverte !");
        return  true;
    }
    else
    {
        qDebug("Echec d'ouverture de la connexion avec la base de données!");
        return false;
    }
}

void DBAccess::close()
{
    if(db.isOpen() == false)
        return ;

    db.close();
    qDebug("Fermeture de la connexion efffectuée avec succes");
}


DBAccess* DBAccess::getInstance()
{
    if(instance == nullptr)
    {
        instance = new DBAccess;
    }
    return instance;
}

void DBAccess::release()
{
    if(instance != nullptr)
    {
        delete instance;
    }
}

DBAccess::~DBAccess()
{
    qDebug("Suppresion du singleton DBAccess");
}

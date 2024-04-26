#ifndef SERVICE_H
#define SERVICE_H

#include "dbaccess.h"
#include "etudiant.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QList>
#include <QItemSelectionModel>
#include <QModelIndex>
#include "themewidget.h"

class Service: public QSqlQueryModel
{
    private:
    DBAccess* dbaccess;
    //Permet de savoir a tout moment les informations sur l'element selectionne sur la vue
    QItemSelectionModel* selectionModel;
    public:
    Service();
    ~Service();

    QItemSelectionModel* getSelectionModel(){ return  selectionModel; }

    void Create(Etudiant etudiant);
    void update(Etudiant etudiant);
    Etudiant read(int id);
    void _delete (int id);

    //Supprime l'element selectionne dans le model. L'element est obtenu a partir de l'objet QItemSelectionModel -> QModelIndex
    void remove();

    void updatePM();

    QList<Etudiant> list();

    //Raffraichit la collection de la liste
    void readAll();

    //void readOnly(int id);
    void readOnly(QString firstName, QString lastName, QString className);

    void readByClass(QString className);
};

#endif // SERVICE_H

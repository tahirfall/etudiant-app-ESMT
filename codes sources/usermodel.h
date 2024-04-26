#ifndef USERMODEL_H
#define USERMODEL_H
#include "dbaccess.h"
#include "user.h"
#include <QSqlQuery>
#include <QSqlRecord>


class UserModel
{
private:
    DBAccess* dbaccess;
public:
    UserModel();
    ~UserModel();

    bool readBy(QString login, QString password);
    void create(User user);
    void update(User user);
    User read(int id);
    void _delete (int id);
    QList<User> list();

};

#endif // USERMODEL_H

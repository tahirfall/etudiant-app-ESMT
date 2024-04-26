#ifndef DBACCESS_H
#define DBACCESS_H

#include <QSqlDatabase>

class DBAccess
{
private:
    QSqlDatabase db;
     DBAccess();

     static DBAccess* instance;

public:
    QSqlDatabase database() {return db; }

    ~DBAccess();

    bool open();
    void close();
    static DBAccess* getInstance();

    static void release();


};

#endif // DBACCESS_H

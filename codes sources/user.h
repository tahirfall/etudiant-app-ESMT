#ifndef USER_H
#define USER_H
#include <QString>

class User
{
private:
    int id;
    QString login;
    QString password;

public:
    User();
    User(QString login, QString password);
    User(int id, QString login, QString password);

    int getId(){ return  id; }
    QString getLogin() { return login; }
    QString getPassword() { return password; }

    void setId(int val_id){   id = val_id; }
    void setLogin(QString val_log) { login = val_log; }
    void setPassword(QString val_passwd) { password = val_passwd; }

   // ~User();


};

#endif // USER_H

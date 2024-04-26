#include "user.h"

User::User(): id(-1), login(" "), password(" ")
{

}

User::User(int val_id, QString val_log, QString val_passwd):
    id(val_id), login(val_log), password(val_passwd)
{

}

User::User(QString val_log, QString val_passwd):
    login(val_log), password(val_passwd)
{

}

/*
User::~User()
{

}
*/

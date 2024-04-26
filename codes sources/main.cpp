#include "controller.h"
#include <QApplication>

#include "usermodel.h"
#include "dbaccess.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller c;
    c.execute();
    return a.exec();

    /*
    UserModel um;
    User user("tahir", "fall");
    um.create(user);

    return  0;
    */

}

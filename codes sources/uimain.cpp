#include "uimain.h"
#include <QMessageBox>


UIMain::UIMain()
{

}
int UIMain::information(QWidget *parent, QString title, QString text) {
    return QMessageBox::information(parent, title,text);
}

int UIMain::warning(QWidget *parent, QString title, QString text) {
    return QMessageBox::warning(parent, title, text);
}

int UIMain::question(QWidget *parent, QString title, QString text){
    return QMessageBox::question(parent,title,text);
}


#include "authentification.h"
#include "ui_authentification.h"


#include <QMessageBox>
Authentification::Authentification(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Authentification)
{
    ui->setupUi(this);
}

Authentification::Authentification(QObject *controller) :

    ui(new Ui::Authentification)
{
    ui->setupUi(this);
    connect(ui->pushButtonSubmit, SIGNAL(clicked()), controller, SLOT(onSubmitAuthentification()));
    connect(ui->pushButtonCancel, SIGNAL(clicked()), controller, SLOT(onCancelAuthentification()));
}


QString Authentification::getLogin()
{
    return ui->lineEditLogin->text();
}
QString Authentification::getPassword()
{
    return ui->lineEditPassword->text();
}

void Authentification::reinit()
{

    ui->lineEditLogin->setText("");
    ui->lineEditPassword->setText("");
}

Authentification::~Authentification()
{
    delete ui;
}

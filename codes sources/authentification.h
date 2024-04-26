#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QMainWindow>
#include <QMessageBox>

#include <QString>
#include "uimain.h"
#include <iostream>

namespace Ui {
class Authentification;
}

class Authentification : public QMainWindow, public UIMain
{
    Q_OBJECT

public:
    explicit Authentification(QWidget *parent = nullptr);
    Authentification(QObject *controller);

    ~Authentification();

    QString getLogin();
    QString getPassword();

    void reinit();

private slots:



private:
    Ui::Authentification *ui;
};

#endif // AUTHENTIFICATION_H

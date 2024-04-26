#ifndef ACCUEIL_H
#define ACCUEIL_H

#include <QMainWindow>
#include "uimain.h"
#include "service.h"

namespace Ui {
class Accueil;
}

class Accueil : public QMainWindow, public UIMain
{
    Q_OBJECT

public:
    explicit Accueil(QWidget *parent = nullptr);
    //second constructor
    Accueil(QObject *controller);

    QString getLineEditFirstName();
    QString getLineditLastName();
    QString getComboBoxSexe();
    QString getComboBoxClass();
    QString getComboBoxOption();
    QString getComboBoxYearAcademic();
    QString getComboBoxFiliere();


    void reinit();

    void hideButtonRegister();
    void hideButtonUpdate();

    void populate(QString firstname, QString lastname, QString sexe, QString classe, QString filiere, QString option, QString yearAcademic );


    ~Accueil();

private slots:

private:
    Ui::Accueil *ui;
};

#endif // ACCUEIL_H

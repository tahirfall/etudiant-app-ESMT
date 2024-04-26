#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>


#include "authentification.h"
#include "usermodel.h"
#include "dbaccess.h"
#include "accueil.h"
#include "service.h"
#include "uilist.h"
#include "themewidget.h"


class Controller : public QObject
{
    Q_OBJECT

private:
    Authentification* authentification;
    Accueil* accueil;
    UserModel* um;
    Service* ser;
    UIList* uil;
    ThemeWidget *tw;



public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    void execute();


private slots:


    void onCancelAuthentification();
    void onSubmitAuthentification();

    void onRegisterAccueil();
    void onUpdateAccueil();
    void onShowListAccueil();
    void onSearchAccueil();
    void onVisualizeChartsAccueil();
    void onCloseAccueil();
    void onShowClassAccueil();

    void onUpdateUiL();
    void onDeleteUiL();
    void onRetourUiL();

    void onCloseThemewidget();



signals:


};




#endif // CONTROLLER_H

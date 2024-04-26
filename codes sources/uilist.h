#ifndef UILIST_H
#define UILIST_H

#include <QMainWindow>
#include <QMessageBox>

#include "uimain.h"
#include "accueil.h"
#include "service.h"
#include <QAbstractTableModel>

namespace Ui {
class UIList;
}

class UIList : public QMainWindow, public UIMain
{
    Q_OBJECT

public:
    explicit UIList(QWidget *parent = nullptr);
    UIList(QObject *controller);


    ~UIList();

    void setTableViewModel(Service* model);

private:
    Ui::UIList *ui;
    QList<Etudiant> etudiants;
};

#endif // UILIST_H

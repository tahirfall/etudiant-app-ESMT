#include "controller.h"
#include "usermodel.h"
#include "dbaccess.h"

#include <QMessageBox>
#include <QSqlField>
#include <QInputDialog>




Controller::Controller(QObject *parent) :
    QObject(parent), authentification(nullptr), accueil(nullptr), um(new UserModel),
                ser(new Service), uil(nullptr), tw(nullptr)
{

}

void Controller::execute()
{
   authentification = new Authentification(this);
   authentification->show();
}

void Controller::onCancelAuthentification()
{
    bool bCancel(false);
   /* if(!authentification->getLogin().isEmpty()
            || !authentification->getPassword().isEmpty())
    { */
        if(QMessageBox::Yes == authentification->question(authentification,
                                "Save unchanged data",
                                "The data have changed. Cancel anyway?"))
        {
            bCancel = true;
        }
    //}

    if(bCancel)
    {
        authentification->close();
        authentification = nullptr;

    }
}


void Controller::onSubmitAuthentification()
{
    QString login = authentification->getLogin();
    QString password = authentification->getPassword();
    bool status = um->readBy(login, password);

    if(status == false)
    {
         authentification->warning(authentification, "Erreur", "Incorrect Login/Password, please try again !");
    }
    else
    {
        accueil = new Accueil(this);
        accueil->hideButtonUpdate();
        accueil->show();

        authentification->hide();
    }
}


void Controller::onRegisterAccueil()
{
    QString firstNam = accueil->getLineEditFirstName();
    QString lastNam = accueil->getLineditLastName();

    if(firstNam.isEmpty() || lastNam.isEmpty())
    {
        accueil->warning(accueil, "Failure", "Please fill in all fields!!!");
    }
    else
    {
        QString sexe = accueil->getComboBoxSexe();
        QString classe = accueil->getComboBoxClass();
        QString option = accueil->getComboBoxOption();
        QString department = accueil->getComboBoxFiliere();
        QString yearAcademic = accueil->getComboBoxYearAcademic();

        Etudiant etudiant(firstNam, lastNam, sexe, classe, option, department, yearAcademic);
        ser->Create(etudiant);

        accueil->information(accueil, "Etudiant creation", "Successful creation of etudiant: "
                    + etudiant.getFirstName() + "  " + etudiant.getLastname() + "  " + etudiant.getSexe() +
                    "  " + etudiant.getClass() + "  " + etudiant.getFiliere() + "  " + etudiant.getOption() +
                     "  " + etudiant.getYearAcademic() + " !");
    }
}


void Controller::onUpdateAccueil()
{
    QString firstNam = accueil->getLineEditFirstName();
    QString lastNam = accueil->getLineditLastName();

    if(firstNam.isEmpty() || lastNam.isEmpty())
    {
        accueil->warning(accueil, "Failure", "Please fill in all fields!!!");
    }
    else
    {
        QString sexe = accueil->getComboBoxSexe();
        QString classe = accueil->getComboBoxClass();
        QString option = accueil->getComboBoxOption();
        QString filiere = accueil->getComboBoxFiliere();
        QString yearAcademic = accueil->getComboBoxYearAcademic();

        QModelIndex index = ser->getSelectionModel()->currentIndex();

        int id = ser->record(index.row()).field(0).value().toInt();

        Etudiant etudiant(id, firstNam, lastNam, sexe, classe, filiere, option, yearAcademic);
        ser->update(etudiant);
        accueil->information(accueil, "Etudiant Update", "Successful Update of etudiant: "
                             + etudiant.getFirstName() + " " + etudiant.getLastname() +" " + etudiant.getSexe() +
                             " " + etudiant.getClass() + "  " + etudiant.getFiliere() + " " + etudiant.getOption() +
                              " " + etudiant.getYearAcademic() + " !");
    }
}


/*
void Controller::onSearchAccueil()
{
    qDebug("");
    bool ok ;
    int id = QInputDialog::getInt(nullptr, tr("QInputDialog::getInteger()"),
                                     tr("ID :"), 0, 0, 100, 1, &ok);
    if (ok){
        uil = new UIList(this);

        uil->setTableViewModel(ser);
        ser->readOnly(id);
        uil->show();
        accueil->close();
    }

}
*/


void Controller::onSearchAccueil()
{
    //qDebug("");
    bool ok ;
    QString firstName = QInputDialog::getText(nullptr, tr("Recherche"),
                                     tr("Prénom :"), QLineEdit::Normal, QString(), &ok);
    if (ok){
        QString lastName = QInputDialog::getText(nullptr, tr("Recherche"),
                                     tr("Nom :"), QLineEdit::Normal, QString(), &ok);
        if (ok) {
            QString classe = QInputDialog::getText(nullptr, tr("Recherche"),
                                         tr("Classe :"), QLineEdit::Normal, QString(), &ok);
            if (ok) {
                uil = new UIList(this);

                uil->setTableViewModel(ser);
                ser->readOnly(classe, firstName, lastName);
                uil->show();
                accueil->close();
            }
        }
    }
}

void Controller::onCloseAccueil()
{
    bool bCloseAccueil(false);


        if(QMessageBox::Yes == QMessageBox::question(accueil,
                                "Save unchanged data",
                                "The data have changed. Exit anyway?"))
        {
            bCloseAccueil = true;
        }

    if(bCloseAccueil)
    {
        accueil->close();
        accueil = nullptr;

        authentification->reinit();
        authentification->show();

    }

}


void Controller::onShowListAccueil()
{
    accueil->hide();

    uil = new UIList(this);
    uil->setTableViewModel(ser);
    ser->readAll();
    uil->show();


}


void Controller::onShowClassAccueil()
{
    qDebug("Affichage des étudiants par classe...");

        // Demander à l'utilisateur de saisir la classe
        bool ok;
        QString classe = QInputDialog::getText(nullptr, tr("Recherche par classe"),
                                                tr("Classe :"), QLineEdit::Normal,
                                                "", &ok);
        if (ok && !classe.isEmpty()) {

             accueil->hide();

            // Afficher la liste des étudiants
            uil = new UIList(this);
            uil->setTableViewModel(ser);
            ser->readByClass(classe);
            uil->show();
        }
}

void Controller::onVisualizeChartsAccueil()
{
    accueil->hide();

    tw = new ThemeWidget(this);
    //tw->initialise();
    tw->show();

}



void Controller::onRetourUiL()
{
    accueil = new Accueil(this);
    accueil->hideButtonUpdate();
    accueil->show();
    accueil->reinit();

    uil->hide();
}

void Controller::onDeleteUiL()
{
    if(QMessageBox::Yes == QMessageBox::question(uil, "Suppression", "Etes-vous sur de vouloir supprimer?"))
    {
       ser->remove();
    }
}


void Controller::onUpdateUiL()
{

    uil->close();

    accueil->hideButtonRegister();
    accueil->show();

    // 1- Recuperer les informations de la personne eslectionnée
    QModelIndex index = ser->getSelectionModel()->currentIndex();

    if(index.isValid())
    {
        int ligne = index.row();

        QString firstname = ser->record(ligne).field(1).value().toString();
        QString lastname = ser->record(ligne).field(2).value().toString();
        QString sexe = ser->record(ligne).field(3).value().toString();
        QString classe = ser->record(ligne).field(4).value().toString();
        QString filiere = ser->record(ligne).field(5).value().toString();
        QString option = ser->record(ligne).field(6).value().toString();
        QString yearAcademic = ser->record(ligne).field(7).value().toString();


        // 2- Remplir les champs du formulaire mainwindow avec les infos récupéerées
        accueil->populate(firstname, lastname, sexe, classe, filiere, option, yearAcademic);
    }
}



void Controller::onCloseThemewidget()
{
    accueil = new Accueil(this);
    tw->close();
    tw = nullptr;

    accueil->show();
}



Controller::~Controller()
{
    if(authentification != nullptr)
        delete authentification;
    if(accueil != nullptr)
        delete accueil;
    if(tw != nullptr)
        delete tw;
    if(uil != nullptr)
        delete uil;


    DBAccess::release();
}

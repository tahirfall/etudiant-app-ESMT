#include "accueil.h"
#include "ui_accueil.h"

Accueil::Accueil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Accueil)
{
    ui->setupUi(this);
}

Accueil::Accueil(QObject *controller) :
    ui(new Ui::Accueil)
{
    ui->setupUi(this);
    connect(ui->pushButtonClose, SIGNAL(clicked()), controller, SLOT(onCloseAccueil()));
    connect(ui->pushButtonRegister, SIGNAL(clicked()), controller, SLOT(onRegisterAccueil()));
    connect(ui->pushButtonShowList, SIGNAL(clicked()), controller, SLOT(onShowListAccueil()));
    connect(ui->pushButtonUpdate, SIGNAL(clicked()), controller, SLOT(onUpdateAccueil()));
    connect(ui->pushButtonSearch, SIGNAL(clicked()), controller, SLOT(onSearchAccueil()));
    connect(ui->pushButtonVisualizeCharts, SIGNAL(clicked()), controller, SLOT(onVisualizeChartsAccueil()));
    connect(ui->pushButtonShowClass, SIGNAL(clicked()), controller, SLOT(onShowClassAccueil()));
}


QString Accueil::getLineEditFirstName()
{
    return ui->lineEditFirstName->text();
}

QString Accueil::getLineditLastName()
{
    return ui->lineEditLastName->text();
}

QString Accueil::getComboBoxSexe()
{
    return ui->comboBoxSexe->currentText();
}

QString Accueil::getComboBoxClass()
{
    return ui->comboBoxClass->currentText();
}

QString Accueil::getComboBoxOption()
{
    return ui->comboBoxOption->currentText();
}

QString Accueil::getComboBoxYearAcademic()
{
    return ui->comboBoxYearAcademic->currentText();
}

QString Accueil::getComboBoxFiliere()
{
    return ui->comboBoxFiliere->currentText();
}


void Accueil::reinit()
{
    ui->lineEditFirstName->setText("");
    ui->lineEditLastName->setText("");
    ui->comboBoxSexe->setCurrentIndex(0);
    ui->comboBoxClass->setCurrentIndex(0);
    ui->comboBoxOption->setCurrentIndex(0);
    ui->comboBoxYearAcademic->setCurrentIndex(0);
    ui->comboBoxFiliere->setCurrentIndex(0);
}


void Accueil::hideButtonRegister()
{
    ui->pushButtonRegister->setVisible(false);
    ui->pushButtonUpdate->setVisible(true);
}
void Accueil::hideButtonUpdate()
{
    ui->pushButtonUpdate->setVisible(false);
    ui->pushButtonRegister->setVisible(true);
}


void Accueil::populate(QString firstname, QString lastname, QString sexe, QString classe,
                             QString filiere, QString option, QString yearAcademic)
{
    ui->lineEditFirstName->setText(firstname);
    ui->lineEditLastName->setText(lastname);
    ui->comboBoxSexe->setCurrentText(sexe);
    ui->comboBoxClass->setCurrentText(classe);
    ui->comboBoxOption->setCurrentText(option);
    ui->comboBoxYearAcademic->setCurrentText(yearAcademic);
    ui->comboBoxFiliere->setCurrentText(filiere);

}


Accueil::~Accueil()
{
    delete ui;
}

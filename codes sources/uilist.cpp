#include "uilist.h"
#include "ui_uilist.h"

UIList::UIList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIList)
{
    ui->setupUi(this);
}

UIList::UIList(QObject *controller) :
    ui(new Ui::UIList)
{
    ui->setupUi(this);
    connect(ui->pushButtonRetour, SIGNAL(clicked()), controller, SLOT(onRetourUiL()));
    connect(ui->pushButtonDelete, SIGNAL(clicked()), controller, SLOT(onDeleteUiL()));
    connect(ui->pushButtonUpdate, SIGNAL(clicked()), controller, SLOT(onUpdateUiL()));
}

void UIList::setTableViewModel(Service* model)
{
    ui->tableView->setModel(model);
    ui->tableView->setSelectionModel(model->getSelectionModel());
    ui->tableView->show();
}


UIList::~UIList()
{
    delete ui;
}

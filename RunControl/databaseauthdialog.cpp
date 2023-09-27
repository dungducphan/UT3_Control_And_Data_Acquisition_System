#include "databaseauthdialog.h"
#include "ui_databaseauthdialog.h"

DatabaseAuthDialog::DatabaseAuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseAuthDialog)
{
    ui->setupUi(this);
}

DatabaseAuthDialog::~DatabaseAuthDialog()
{
    delete ui;
}

#include "databaseauthdialog.h"
#include "ui_databaseauthdialog.h"

DatabaseAuthDialog::DatabaseAuthDialog(QWidget *parent)
: QDialog(parent),
  ui(new Ui::DatabaseAuthDialog) {
    ui->setupUi(this);
    ui->LE_Password->setEchoMode(QLineEdit::Password);
}

DatabaseAuthDialog::~DatabaseAuthDialog() {
    delete ui;
}

void DatabaseAuthDialog::on_Button_OK_clicked() {
    DB_USER = ui->LE_Username->text().toStdString();
    DB_PASSWORD = ui->LE_Password->text().toStdString();
    this->close();
}


void DatabaseAuthDialog::on_Button_Cancel_clicked() {
    this->close();
}


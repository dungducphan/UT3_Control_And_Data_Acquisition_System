#pragma once

#include <QDialog>

namespace Ui {
class DatabaseAuthDialog;
}

class DatabaseAuthDialog : public QDialog {
    Q_OBJECT

public:
    explicit DatabaseAuthDialog(QWidget *parent = nullptr);
    ~DatabaseAuthDialog();

private:
    Ui::DatabaseAuthDialog *ui;
};

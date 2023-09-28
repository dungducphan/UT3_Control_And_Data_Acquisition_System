#pragma once

#include <QDialog>
#include <QSettings>

namespace Ui {
class DatabaseAuthDialog;
}

class DatabaseAuthDialog : public QDialog {
    Q_OBJECT

public:
    explicit DatabaseAuthDialog(QWidget *parent = nullptr);
    ~DatabaseAuthDialog() override;

    std::string DB_USER;
    std::string DB_PASSWORD;

    void setSettings(QSettings& parentSettings);

private slots:
    void on_Button_OK_clicked();
    void on_Button_Cancel_clicked();

private:
    Ui::DatabaseAuthDialog *ui;
    QSettings* settings;
};

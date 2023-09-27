#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <databaseauthdialog.h>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent),
  ui(new Ui::MainWindow),
  beamlineImgViewer{nullptr} {
    DB_Controller = std::make_unique<MariaDBController>();
    ui->setupUi(this);
    update_DB_CONNECTION_PARAMETERS();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionBeamline_Image_Diagnostic_triggered() {
    if (beamlineImgViewer == nullptr) beamlineImgViewer = std::make_unique<BeamlineDiagnosticsImageViewer>(this);
    beamlineImgViewer->show();
}

[[maybe_unused]] void MainWindow::on_actionExit_triggered() {
    QApplication::exit();
}

void MainWindow::on_Button_ImageBasePathFileDialog_clicked() {
    // FIXME: open a file dialog here to set the base path for image saving. View this video: https://www.youtube.com/watch?v=NANhXeoOwNY
}

void MainWindow::on_LE_DatabaseHost_returnPressed() {
    update_DB_CONNECTION_PARAMETERS();
}

void MainWindow::on_LE_DatabasePort_returnPressed() {
    update_DB_CONNECTION_PARAMETERS();
}

void MainWindow::on_LE_DatabaseSchema_returnPressed() {
    update_DB_CONNECTION_PARAMETERS();
}

void MainWindow::update_DB_HOST() {
    if (ui->LE_DatabaseHost->text().isEmpty()) {
        DB_Controller->DB_HOST = "localhost";
        ui->LE_DatabaseHost->setPlaceholderText("localhost");
    } else {
        DB_Controller->DB_HOST = ui->LE_DatabaseHost->text().toStdString();
    }
}

void MainWindow::update_DB_PORT() {
    if (ui->LE_DatabasePort->text().isEmpty()) {
        DB_Controller->DB_PORT = "3306";
        ui->LE_DatabasePort->setPlaceholderText("3306");
    } else {
        DB_Controller->DB_PORT = ui->LE_DatabasePort->text().toStdString();
    }
}

void MainWindow::update_DB_SCHEMA() {
    if (ui->LE_DatabaseSchema->text().isEmpty()) {
        DB_Controller->DB_SCHEMA = "LaserParameter";
        ui->LE_DatabaseSchema->setPlaceholderText("LaserParameter");
    } else {
        DB_Controller->DB_SCHEMA = ui->LE_DatabaseSchema->text().toStdString();
    }
}

void MainWindow::update_DB_CONNECTION_PARAMETERS() {
    update_DB_HOST();
    update_DB_PORT();
    update_DB_SCHEMA();
    DB_Controller->DB_URL = "jdbc:mariadb://" + DB_Controller->DB_HOST + ":" + DB_Controller->DB_PORT + "/" + DB_Controller->DB_SCHEMA;
    ui->URLLabel->setText(QString::fromStdString(DB_Controller->DB_URL.c_str()));
}

void MainWindow::on_ConnectButton_clicked() {
    auto authDialog = std::make_unique<DatabaseAuthDialog>(this);
    authDialog->exec();
    DB_Controller->DB_USER = authDialog->DB_USER;
    DB_Controller->DB_PASSWORD = authDialog->DB_PASSWORD;

    try {
        DB_Controller->Connect();
        ui->ConnectionStatusLabel->setText("Database connected.");
    } catch (sql::SQLException &e) {
        ui->ConnectionStatusLabel->setText(e.what());
    }
}


#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    beamlineImgViewer{nullptr} {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_actionBeamline_Image_Diagnostic_triggered() {
    if (beamlineImgViewer == nullptr) beamlineImgViewer = std::make_shared<BeamlineDiagnosticsImageViewer>(this);
    beamlineImgViewer->show();
}


void MainWindow::on_actionExit_triggered() {
    QApplication::exit();
}

void MainWindow::on_Button_ImageBasePathFileDialog_clicked() {
    // FIXME: open a file dialog here to set the base path for image saving. View this video: https://www.youtube.com/watch?v=NANhXeoOwNY
}


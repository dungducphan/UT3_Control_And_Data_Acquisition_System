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


#include "beamlinediagnosticsimageviewer.h"
#include "ui_beamlinediagnosticsimageviewer.h"

BeamlineDiagnosticsImageViewer::BeamlineDiagnosticsImageViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BeamlineDiagnosticsImageViewer)
{
    ui->setupUi(this);
}

BeamlineDiagnosticsImageViewer::~BeamlineDiagnosticsImageViewer()
{
    delete ui;
}

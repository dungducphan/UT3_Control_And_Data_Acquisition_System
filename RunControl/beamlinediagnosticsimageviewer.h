#ifndef BEAMLINEDIAGNOSTICSIMAGEVIEWER_H
#define BEAMLINEDIAGNOSTICSIMAGEVIEWER_H

#include <QDialog>

namespace Ui {
class BeamlineDiagnosticsImageViewer;
}

class BeamlineDiagnosticsImageViewer : public QDialog
{
    Q_OBJECT

public:
    explicit BeamlineDiagnosticsImageViewer(QWidget *parent = nullptr);
    ~BeamlineDiagnosticsImageViewer();

private:
    Ui::BeamlineDiagnosticsImageViewer *ui;
};

#endif // BEAMLINEDIAGNOSTICSIMAGEVIEWER_H

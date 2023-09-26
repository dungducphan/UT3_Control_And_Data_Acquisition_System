#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "beamlinediagnosticsimageviewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionBeamline_Image_Diagnostic_triggered();
    void on_actionExit_triggered();
    void on_Button_ImageBasePathFileDialog_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<BeamlineDiagnosticsImageViewer> beamlineImgViewer;
};
#endif // MAINWINDOW_H

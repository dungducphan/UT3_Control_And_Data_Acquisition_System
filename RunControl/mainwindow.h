#pragma once

#include <QMainWindow>
#include <beamlinediagnosticsimageviewer.h>

#include <MariaDBController.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    static void on_actionExit_triggered();

    void on_actionBeamline_Image_Diagnostic_triggered();
    void on_Button_ImageBasePathFileDialog_clicked();
    void on_LE_DatabaseHost_returnPressed();
    void on_LE_DatabasePort_returnPressed();
    void on_LE_DatabaseSchema_returnPressed();

    void update_DB_HOST();
    void update_DB_PORT();
    void update_DB_SCHEMA();
    void update_DB_CONNECTION_PARAMETERS();

    void on_ConnectButton_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<BeamlineDiagnosticsImageViewer> beamlineImgViewer;
    std::unique_ptr<MariaDBController> DB_Controller;
};

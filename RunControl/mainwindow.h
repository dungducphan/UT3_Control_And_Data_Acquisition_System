#pragma once

#include <QMainWindow>
#include <QLineEdit>
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
    void on_actionExit_triggered();
    void on_actionBeamline_Image_Diagnostic_triggered();
    void on_Button_ImageBasePathFileDialog_clicked();
    void on_LE_DatabaseHost_returnPressed();
    void on_LE_DatabasePort_returnPressed();
    void on_LE_DatabaseSchema_returnPressed();
    void on_ConnectButton_clicked();
    void on_DisconnectButton_clicked();
    void on_LE_Notes_textChanged();
    void on_ApplyConfigButton_clicked();
    void on_ClearConfigButton_clicked();
    void on_LE_ImageBasePath_textChanged(const QString& newText);
    void on_LE_EnergyOnTarget_textChanged(const QString& newText);
    void on_LE_FarfieldEnergy_textChanged(const QString& newText);
    void on_LE_PulseDuration_textChanged(const QString& newText);
    void on_LE_GasjetBackpressure_textChanged(const QString& newText);
    void on_LE_GasjetX_textChanged(const QString& newText);
    void on_LE_GasjetY_textChanged(const QString& newText);
    void on_LE_GasjetZ_textChanged(const QString& newText);
    void on_LE_GasjetTiming_textChanged(const QString& newText);
    void on_LE_GasjetDuration_textChanged(const QString& newText);
    void on_LE_ProbeTiming_textChanged(const QString& newText);
    void on_LE_ProbeND_textChanged(const QString& newText);
    void on_LE_WFSND_textChanged(const QString& newText);
    void on_LE_TopviewND_textChanged(const QString& newText);

    void update_DB_HOST();
    void update_DB_PORT();
    void update_DB_SCHEMA();
    void update_DB_CONNECTION_PARAMETERS();

    void setRangeForRunControlParameter();
    void validateRunControlParameter(const QLineEdit* lineEdit, const std::string& lineEditName, float& DBReference);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<BeamlineDiagnosticsImageViewer> beamlineImgViewer;
    std::unique_ptr<MariaDBController> DB_Controller;
};

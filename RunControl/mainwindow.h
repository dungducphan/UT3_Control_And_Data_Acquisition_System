#pragma once

#include <thread>

#include <tango.h>

#include <QMainWindow>
#include <QLineEdit>
#include <QSettings>

#include <beamlinediagnosticsimageviewer.h>
#include <callback.h>

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
    void on_ApplyConfigButton_clicked();
    void on_ClearConfigButton_clicked();

    // Run Control Parameters
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
    void on_LE_Notes_textChanged();

private:
    // UI elements
    Ui::MainWindow *ui;
    QSettings UI_settings;
    std::unique_ptr<BeamlineDiagnosticsImageViewer> beamlineImgViewer;

    // MariaDB
    std::unique_ptr<MariaDBController> DB_Controller;
    bool DB_IsDBReady;
    std::thread DB_Thread;
    unsigned long DB_LatestShotID;

    // Tango DeviceProxies
    std::unique_ptr<Tango::DeviceProxy> TANGO_TimingUnit;
    std::unique_ptr<Tango::DeviceProxy> TANGO_WFS;
    TriggerCallback* TANGO_TriggerCallback;
    WFSCallback* TANGO_WFSCallback;

private:
    void DB_update_DB_HOST();
    void DB_update_DB_PORT();
    void DB_update_DB_SCHEMA();
    void DB_update_DB_CONNECTION_PARAMETERS();

    void UI_setRangeForRunControlParameter();
    void UI_validateRunControlParameter(const QLineEdit* lineEdit, const std::string& lineEditName, float& DBReference);
    void UI_on_TriggerReceived();
    void UI_on_WFSReceived();
    void UI_recallSettings();
};

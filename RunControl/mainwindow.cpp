#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <databaseauthdialog.h>
#include <warningonmissingbasepath.h>

#include <iostream>

#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent),
  ui(new Ui::MainWindow),
  beamlineImgViewer{nullptr} {
    DB_Controller = std::make_unique<MariaDBController>();
    ui->setupUi(this);
    setRangeForRunControlParameter();
    update_DB_CONNECTION_PARAMETERS();

    TimingUnit = std::make_unique<Tango::DeviceProxy>("tau/beamline/ttdu");
    TriggerCallbackInstance = new TriggerCallback();
    TimingUnit->subscribe_event("Timestamp", Tango::CHANGE_EVENT, TriggerCallbackInstance);
    connect(TriggerCallbackInstance, &TriggerCallback::TriggerReceived, this, &MainWindow::on_TriggerCallback_TriggerReceived);
}

void MainWindow::setRangeForRunControlParameter() {
    ui->LE_EnergyOnTarget->setValidator(new QDoubleValidator(0., 2000., 1));
    ui->LE_FarfieldEnergy->setValidator(new QDoubleValidator(0., 2000., 1));
    ui->LE_PulseDuration->setValidator(new QDoubleValidator(0., 100., 1));
    ui->LE_GasjetBackpressure->setValidator(new QDoubleValidator(0., 50., 1));
    ui->LE_GasjetX->setValidator(new QDoubleValidator(-100., 100., 2));
    ui->LE_GasjetY->setValidator(new QDoubleValidator(-100., 100., 2));
    ui->LE_GasjetZ->setValidator(new QDoubleValidator(-100., 100., 2));
    ui->LE_GasjetTiming->setValidator(new QDoubleValidator(0., 100., 1));
    ui->LE_GasjetDuration->setValidator(new QDoubleValidator(0., 100., 1));
    ui->LE_ProbeTiming->setValidator(new QDoubleValidator(0., 20000., 1));
    ui->LE_ProbeND->setValidator(new QDoubleValidator(0., 10., 0));
    ui->LE_WFSND->setValidator(new QDoubleValidator(0., 10., 0));
    ui->LE_TopviewND->setValidator(new QDoubleValidator(0., 10., 0));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionBeamline_Image_Diagnostic_triggered() {
    if (beamlineImgViewer == nullptr) beamlineImgViewer = std::make_unique<BeamlineDiagnosticsImageViewer>(this);
    beamlineImgViewer->show();
}

void MainWindow::on_actionExit_triggered() {
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
        DB_Controller->DB_SCHEMA = "UT3Data";
        ui->LE_DatabaseSchema->setPlaceholderText("UT3Data");
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

void MainWindow::on_DisconnectButton_clicked()  {
    DB_Controller->Disconnect();
    ui->ConnectionStatusLabel->setText("Database disconnected.");
}

void MainWindow::on_LE_ImageBasePath_textChanged(const QString& newText) {
    if (ui->LE_ImageBasePath->text().isEmpty()) {
        WarningOnMissingBasePath warningOnMissingBasePath(this);
        warningOnMissingBasePath.exec();
    }
    DB_Controller->DBEntry.ImageBasePath = ui->LE_ImageBasePath->text().toStdString();
}

void MainWindow::on_LE_EnergyOnTarget_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_EnergyOnTarget, "Energy-on-Target", DB_Controller->DBEntry.EnergyOnTargetInMilliJoules);
}

void MainWindow::on_LE_FarfieldEnergy_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_FarfieldEnergy, "Far-field energy", DB_Controller->DBEntry.FarfieldEnergyInMilliJoules);
}

void MainWindow::on_LE_PulseDuration_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_PulseDuration, "Pulse duration", DB_Controller->DBEntry.PulseDurationInFemtoSeconds);
}

void MainWindow::on_LE_GasjetBackpressure_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_GasjetBackpressure, "Gasjet backpressure", DB_Controller->DBEntry.GasjetBackpressureInBars);
}

void MainWindow::on_LE_GasjetX_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_GasjetX, "Gasjet X", DB_Controller->DBEntry.GasjetXInMicrons);
}

void MainWindow::on_LE_GasjetY_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_GasjetY, "Gasjet Y", DB_Controller->DBEntry.GasjetYInMicrons);
}

void MainWindow::on_LE_GasjetZ_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_GasjetZ, "Gasjet Z", DB_Controller->DBEntry.GasjetZInMicrons);
}

void MainWindow::on_LE_GasjetTiming_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_GasjetTiming, "Gasjet timing", DB_Controller->DBEntry.GasjetTimingInMilliSeconds);
}

void MainWindow::on_LE_GasjetDuration_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_GasjetDuration, "Gasjet duration", DB_Controller->DBEntry.GasjetDurationInMilliSeconds);
}

void MainWindow::on_LE_ProbeTiming_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_ProbeTiming, "Probe timing", DB_Controller->DBEntry.ProbeTimingInFemtoSeconds);
}

void MainWindow::on_LE_ProbeND_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_ProbeND, "Probe ND", DB_Controller->DBEntry.ProbeND);
}

void MainWindow::on_LE_WFSND_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_WFSND, "WFS ND", DB_Controller->DBEntry.WFSND);
}

void MainWindow::on_LE_TopviewND_textChanged(const QString& newText) {
    validateRunControlParameter(ui->LE_TopviewND, "Topview ND", DB_Controller->DBEntry.TopviewND);
}

void MainWindow::on_LE_Notes_textChanged() {
    DB_Controller->DBEntry.Notes = ui->LE_Notes->toPlainText().toStdString();
}

void MainWindow::on_ApplyConfigButton_clicked() {
    if (ui->LE_ImageBasePath->text().isEmpty()) {
        WarningOnMissingBasePath warningOnMissingBasePath(this);
        warningOnMissingBasePath.exec();
    }
    DB_Controller->DBEntry.ImageBasePath = ui->LE_ImageBasePath->text().toStdString();
    DB_Controller->DBEntry.EnergyOnTargetInMilliJoules = ui->LE_EnergyOnTarget->text().toFloat();
    DB_Controller->DBEntry.FarfieldEnergyInMilliJoules = ui->LE_FarfieldEnergy->text().toFloat();
    DB_Controller->DBEntry.PulseDurationInFemtoSeconds = ui->LE_PulseDuration->text().toFloat();
    DB_Controller->DBEntry.GasjetBackpressureInBars = ui->LE_GasjetBackpressure->text().toFloat();
    DB_Controller->DBEntry.GasjetXInMicrons = ui->LE_GasjetX->text().toFloat();
    DB_Controller->DBEntry.GasjetYInMicrons = ui->LE_GasjetY->text().toFloat();
    DB_Controller->DBEntry.GasjetZInMicrons = ui->LE_GasjetZ->text().toFloat();
    DB_Controller->DBEntry.GasjetTimingInMilliSeconds = ui->LE_GasjetTiming->text().toFloat();
    DB_Controller->DBEntry.GasjetDurationInMilliSeconds = ui->LE_GasjetDuration->text().toFloat();
    DB_Controller->DBEntry.ProbeTimingInFemtoSeconds = ui->LE_ProbeTiming->text().toFloat();
    DB_Controller->DBEntry.ProbeND = ui->LE_ProbeND->text().toFloat();
    DB_Controller->DBEntry.WFSND = ui->LE_WFSND->text().toFloat();
    DB_Controller->DBEntry.TopviewND = ui->LE_TopviewND->text().toFloat();
    DB_Controller->DBEntry.Notes = ui->LE_Notes->toPlainText().toStdString();
}

void MainWindow::on_ClearConfigButton_clicked() {
    ui->LE_ImageBasePath->clear();
    ui->LE_EnergyOnTarget->clear();
    ui->LE_FarfieldEnergy->clear();
    ui->LE_PulseDuration->clear();
    ui->LE_GasjetBackpressure->clear();
    ui->LE_GasjetX->clear();
    ui->LE_GasjetY->clear();
    ui->LE_GasjetZ->clear();
    ui->LE_GasjetTiming->clear();
    ui->LE_GasjetDuration->clear();
    ui->LE_ProbeTiming->clear();
    ui->LE_ProbeND->clear();
    ui->LE_WFSND->clear();
    ui->LE_TopviewND->clear();
    ui->LE_Notes->clear();
}

void MainWindow::validateRunControlParameter(const QLineEdit* lineEdit, const std::string& lineEditName, float& DBReference) {
    auto validator = (QDoubleValidator*) lineEdit->validator();
    float inputValue = lineEdit->displayText().toFloat();
    if (inputValue < validator->bottom() || inputValue > validator->top()) {
        auto status = boost::format("WARNING: %1% set value is out of range [%2%, %3%]") % lineEditName % validator->bottom() % validator->top();
        ui->Label_RunControlStatus->setText(status.str().c_str());
    } else {
        auto status = boost::format("%1% set value is %2%.") % lineEditName % inputValue;
        ui->Label_RunControlStatus->setText(status.str().c_str());
        DBReference = inputValue;
    }
}

void MainWindow::on_TriggerCallback_TriggerReceived() {
    auto timestamp = boost::format("%1%") % TriggerCallbackInstance->Timestamp;
    ui->Label_CurrentShotTimestamp->setText(timestamp.str().c_str());
}


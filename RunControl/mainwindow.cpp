#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <databaseauthdialog.h>
#include <warningonmissingbasepath.h>

#include <iostream>

#include <QDoubleValidator>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent),
  ui(new Ui::MainWindow),
  DB_IsDBReady(false),
  DB_LatestShotID{0},
  beamlineImgViewer{nullptr} {
    // Setup MariaDB
    DB_Controller = std::make_unique<MariaDBController>();
    DB_Controller->DBEntry.Notes = "NULL";

    // Setup UI
    ui->setupUi(this);
    UI_setRangeForRunControlParameter();
    UI_recallSettings();

    // Setup TANGO device clients
    TANGO_TimingUnit = std::make_unique<Tango::DeviceProxy>("UT3/Timing/TDU");
    TANGO_TriggerCallback = new TriggerCallback();
    TANGO_TimingUnit->subscribe_event("Timestamp", Tango::CHANGE_EVENT, TANGO_TriggerCallback);
    connect(TANGO_TriggerCallback, &TriggerCallback::TriggerReceived, this, &MainWindow::UI_on_TriggerReceived);

//    TANGO_WFS = std::make_unique<Tango::DeviceProxy>("UT3/Beamline/WFS");
//    TANGO_WFSCallback = new WFSCallback();
//    TANGO_WFS->subscribe_event("DynamicImage", Tango::CHANGE_EVENT, TANGO_WFSCallback);
//    connect(TANGO_WFSCallback, &WFSCallback::WFSReceived, this, &MainWindow::UI_on_WFSReceived);
}

void MainWindow::UI_setRangeForRunControlParameter() {
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
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);
    fileDialog.exec();
    ui->LE_ImageBasePath->setText(fileDialog.selectedFiles().first());
}

void MainWindow::on_LE_DatabaseHost_returnPressed() {
    DB_update_DB_CONNECTION_PARAMETERS();
}

void MainWindow::on_LE_DatabasePort_returnPressed() {
    DB_update_DB_CONNECTION_PARAMETERS();
}

void MainWindow::on_LE_DatabaseSchema_returnPressed() {
    DB_update_DB_CONNECTION_PARAMETERS();
}

void MainWindow::DB_update_DB_HOST() {
    if (ui->LE_DatabaseHost->text().isEmpty()) {
        DB_Controller->DB_HOST = "localhost";
        ui->LE_DatabaseHost->setPlaceholderText("localhost");
        UI_settings.setValue("DB_HOST", "localhost");
    } else {
        DB_Controller->DB_HOST = ui->LE_DatabaseHost->text().toStdString();
        UI_settings.setValue("DB_HOST", ui->LE_DatabaseHost->text());
    }
}

void MainWindow::DB_update_DB_PORT() {
    if (ui->LE_DatabasePort->text().isEmpty()) {
        DB_Controller->DB_PORT = "3306";
        ui->LE_DatabasePort->setPlaceholderText("3306");
        UI_settings.setValue("DB_PORT", "3306");
    } else {
        DB_Controller->DB_PORT = ui->LE_DatabasePort->text().toStdString();
        UI_settings.setValue("DB_PORT", ui->LE_DatabasePort->text());
    }
}

void MainWindow::DB_update_DB_SCHEMA() {
    if (ui->LE_DatabaseSchema->text().isEmpty()) {
        DB_Controller->DB_SCHEMA = "UT3Data";
        ui->LE_DatabaseSchema->setPlaceholderText("UT3Data");
        UI_settings.setValue("DB_SCHEMA", "UT3Data");
    } else {
        DB_Controller->DB_SCHEMA = ui->LE_DatabaseSchema->text().toStdString();
        UI_settings.setValue("DB_SCHEMA", ui->LE_DatabaseSchema->text());
    }
}

void MainWindow::DB_update_DB_CONNECTION_PARAMETERS() {
    DB_update_DB_HOST();
    DB_update_DB_PORT();
    DB_update_DB_SCHEMA();
    DB_Controller->DB_URL = "jdbc:mariadb://" + DB_Controller->DB_HOST + ":" + DB_Controller->DB_PORT + "/" + DB_Controller->DB_SCHEMA;
    ui->URLLabel->setText(QString::fromStdString(DB_Controller->DB_URL.c_str()));
}

void MainWindow::on_ConnectButton_clicked() {
    auto authDialog = std::make_unique<DatabaseAuthDialog>(this);
    authDialog->setSettings(UI_settings);
    authDialog->exec();
    DB_Controller->DB_USER = authDialog->DB_USER;
    DB_Controller->DB_PASSWORD = authDialog->DB_PASSWORD;

    try {
        DB_Controller->Connect();
        ui->ConnectionStatusLabel->setText("Database connected.");
        DB_IsDBReady = true;
        DB_LatestShotID = DB_Controller->GetLatestShotID();
        ui->Label_CurrentShotID->setText(QString::fromStdString(std::to_string(DB_LatestShotID)));
    } catch (sql::SQLException &e) {
        ui->ConnectionStatusLabel->setText(e.what());
    }
}

void MainWindow::on_DisconnectButton_clicked()  {
    DB_Controller->Disconnect();
    ui->ConnectionStatusLabel->setText("Database disconnected.");
    DB_IsDBReady = false;
}

void MainWindow::on_LE_ImageBasePath_textChanged(const QString& newText) {
    if (ui->LE_ImageBasePath->text().isEmpty()) {
        WarningOnMissingBasePath warningOnMissingBasePath(this);
        warningOnMissingBasePath.exec();
    }
    DB_Controller->DBEntry.ImageBasePath = ui->LE_ImageBasePath->text().toStdString();
    UI_settings.setValue("ImageBasePath", ui->LE_ImageBasePath->text());
}

void MainWindow::on_LE_EnergyOnTarget_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_EnergyOnTarget, "EnergyOnTarget",
                                   DB_Controller->DBEntry.EnergyOnTargetInMilliJoules);
}

void MainWindow::on_LE_FarfieldEnergy_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_FarfieldEnergy, "FarfieldEnergy",
                                   DB_Controller->DBEntry.FarfieldEnergyInMilliJoules);
}

void MainWindow::on_LE_PulseDuration_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_PulseDuration, "PulseDuration",
                                   DB_Controller->DBEntry.PulseDurationInFemtoSeconds);
}

void MainWindow::on_LE_GasjetBackpressure_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_GasjetBackpressure, "GasjetBackpressure",
                                   DB_Controller->DBEntry.GasjetBackpressureInBars);
}

void MainWindow::on_LE_GasjetX_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_GasjetX, "GasjetX", DB_Controller->DBEntry.GasjetXInMicrons);
}

void MainWindow::on_LE_GasjetY_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_GasjetY, "GasjetY", DB_Controller->DBEntry.GasjetYInMicrons);
}

void MainWindow::on_LE_GasjetZ_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_GasjetZ, "GasjetZ", DB_Controller->DBEntry.GasjetZInMicrons);
}

void MainWindow::on_LE_GasjetTiming_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_GasjetTiming, "GasjetTiming",
                                   DB_Controller->DBEntry.GasjetTimingInMilliSeconds);
}

void MainWindow::on_LE_GasjetDuration_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_GasjetDuration, "GasjetDuration",
                                   DB_Controller->DBEntry.GasjetDurationInMilliSeconds);
}

void MainWindow::on_LE_ProbeTiming_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_ProbeTiming, "ProbeTiming", DB_Controller->DBEntry.ProbeTimingInFemtoSeconds);
}

void MainWindow::on_LE_ProbeND_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_ProbeND, "ProbeND", DB_Controller->DBEntry.ProbeND);
}

void MainWindow::on_LE_WFSND_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_WFSND, "WFSND", DB_Controller->DBEntry.WFSND);
}

void MainWindow::on_LE_TopviewND_textChanged(const QString& newText) {
    UI_validateRunControlParameter(ui->LE_TopviewND, "TopviewND", DB_Controller->DBEntry.TopviewND);
}

void MainWindow::on_LE_Notes_textChanged() {
    if (ui->LE_Notes->toPlainText().isEmpty()) {
        std::cout << "No notes." << std::endl;
        DB_Controller->DBEntry.Notes = "NULL";
    } else {
        std::cout << "Some notes." << std::endl;
        DB_Controller->DBEntry.Notes = ui->LE_Notes->toPlainText().toStdString();
    }
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
    if (ui->LE_Notes->toPlainText().isEmpty()) {
        std::cout << "No notes." << std::endl;
        DB_Controller->DBEntry.Notes = "NULL";
    } else {
        std::cout << "Some notes." << std::endl;
        DB_Controller->DBEntry.Notes = ui->LE_Notes->toPlainText().toStdString();
    }

    UI_settings.setValue("ImageBasePath", ui->LE_ImageBasePath->text());
    UI_settings.setValue("EnergyOnTarget", ui->LE_EnergyOnTarget->text());
    UI_settings.setValue("FarfieldEnergy", ui->LE_FarfieldEnergy->text());
    UI_settings.setValue("PulseDuration", ui->LE_PulseDuration->text());
    UI_settings.setValue("GasjetBackpressure", ui->LE_GasjetBackpressure->text());
    UI_settings.setValue("GasjetX", ui->LE_GasjetX->text());
    UI_settings.setValue("GasjetY", ui->LE_GasjetY->text());
    UI_settings.setValue("GasjetZ", ui->LE_GasjetZ->text());
    UI_settings.setValue("GasjetTiming", ui->LE_GasjetTiming->text());
    UI_settings.setValue("GasjetDuration", ui->LE_GasjetDuration->text());
    UI_settings.setValue("ProbeTiming", ui->LE_ProbeTiming->text());
    UI_settings.setValue("ProbeND", ui->LE_ProbeND->text());
    UI_settings.setValue("WFSND", ui->LE_WFSND->text());
    UI_settings.setValue("TopviewND", ui->LE_TopviewND->text());
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

void MainWindow::UI_validateRunControlParameter(const QLineEdit* lineEdit, const std::string& lineEditName, float& DBReference) {
    auto validator = (QDoubleValidator*) lineEdit->validator();
    float inputValue = lineEdit->displayText().toFloat();
    if (inputValue < validator->bottom() || inputValue > validator->top()) {
        auto status = boost::format("WARNING: %1% set value is out of range [%2%, %3%]") % lineEditName % validator->bottom() % validator->top();
        ui->Label_RunControlStatus->setText(status.str().c_str());
    } else {
        auto status = boost::format("%1% set value is %2%.") % lineEditName % inputValue;
        ui->Label_RunControlStatus->setText(status.str().c_str());
        DBReference = inputValue;
        UI_settings.setValue(QString::fromStdString(lineEditName), lineEdit->text());
    }
}

void MainWindow::UI_on_TriggerReceived() {
    auto timestamp = boost::format("%1%") % TANGO_TriggerCallback->Timestamp;
    ui->Label_CurrentShotTimestamp->setText(timestamp.str().c_str());

    if (DB_IsDBReady) {
        DB_LatestShotID++;
        ui->Label_CurrentShotID->setText(QString::fromStdString(std::to_string(DB_LatestShotID)));
        DB_Controller->DBEntry.Timestamp = (int64_t) TANGO_TriggerCallback->Timestamp;
        DB_Controller->AddEntryShotRecord();
    }
}

void MainWindow::UI_on_WFSReceived() {
}

void MainWindow::UI_recallSettings() {
    auto db_host = UI_settings.value("DB_HOST").toString().toStdString();
    if (db_host.empty()) {
        ui->LE_DatabaseHost->setPlaceholderText("localhost");
        UI_settings.setValue("DB_HOST", "localhost");
    }
    else ui->LE_DatabaseHost->setText(QString::fromStdString(db_host));

    auto db_port = UI_settings.value("DB_PORT").toString().toStdString();
    if (db_port.empty()) ui->LE_DatabasePort->setPlaceholderText("3306");
    else ui->LE_DatabasePort->setText(QString::fromStdString(db_port));

    auto db_schema = UI_settings.value("DB_SCHEMA").toString().toStdString();
    if (db_schema.empty()) ui->LE_DatabaseSchema->setPlaceholderText("UT3Data");
    else ui->LE_DatabaseSchema->setText(QString::fromStdString(db_schema));

    DB_update_DB_CONNECTION_PARAMETERS();

    auto image_base_path = UI_settings.value("ImageBasePath").toString().toStdString();
    if (image_base_path.empty()) {
        std::string home = getenv("HOME");
        std::string defaultDir = home + "/UT3Data";
        ui->LE_ImageBasePath->setPlaceholderText(defaultDir.c_str());
        UI_settings.setValue("ImageBasePath", defaultDir.c_str());
        DB_Controller->DBEntry.ImageBasePath = defaultDir;
    } else {
        ui->LE_ImageBasePath->setText(QString::fromStdString(image_base_path));
    }

    ui->LE_EnergyOnTarget->setText(QString::fromStdString(UI_settings.value("EnergyOnTarget").toString().toStdString()));
    ui->LE_FarfieldEnergy->setText(QString::fromStdString(UI_settings.value("FarfieldEnergy").toString().toStdString()));
    ui->LE_PulseDuration->setText(QString::fromStdString(UI_settings.value("PulseDuration").toString().toStdString()));
    ui->LE_GasjetBackpressure->setText(QString::fromStdString(UI_settings.value("GasjetBackpressure").toString().toStdString()));
    ui->LE_GasjetX->setText(QString::fromStdString(UI_settings.value("GasjetX").toString().toStdString()));
    ui->LE_GasjetY->setText(QString::fromStdString(UI_settings.value("GasjetY").toString().toStdString()));
    ui->LE_GasjetZ->setText(QString::fromStdString(UI_settings.value("GasjetZ").toString().toStdString()));
    ui->LE_GasjetTiming->setText(QString::fromStdString(UI_settings.value("GasjetTiming").toString().toStdString()));
    ui->LE_GasjetDuration->setText(QString::fromStdString(UI_settings.value("GasjetDuration").toString().toStdString()));
    ui->LE_ProbeTiming->setText(QString::fromStdString(UI_settings.value("ProbeTiming").toString().toStdString()));
    ui->LE_ProbeND->setText(QString::fromStdString(UI_settings.value("ProbeND").toString().toStdString()));
    ui->LE_WFSND->setText(QString::fromStdString(UI_settings.value("WFSND").toString().toStdString()));
    ui->LE_TopviewND->setText(QString::fromStdString(UI_settings.value("TopviewND").toString().toStdString()));
}


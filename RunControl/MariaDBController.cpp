#include <MariaDBController.h>
#include <boost/date_time.hpp>

MariaDBController::MariaDBController()
: SQL_Driver(sql::mariadb::get_driver_instance()),
  DB_Connection{nullptr} {
}

MariaDBController::~MariaDBController() {}

void MariaDBController::Connect() {
    sql::Properties properties({
        {"user", DB_USER},
        {"password", DB_PASSWORD}
    });
    DB_Connection.reset(SQL_Driver->connect(DB_URL, properties));
}

void MariaDBController::Disconnect() const {
    DB_Connection->close();
}

void MariaDBController::AddEntryShotRecord() const {
    try {
        auto date = boost::gregorian::to_iso_string(boost::gregorian::day_clock::local_day());
        auto iso_date = boost::gregorian::to_iso_extended_string(boost::gregorian::day_clock::local_day());
        auto statement = boost::format("INSERT INTO UT3Data.ShotRecord "
                                       "(Timestamp, Date, EnergyOnTarget, FarfieldEnergy, PulseDuration, GasJetBackPressure, GasJetPosX, GasJetPosY, GasJetPosZ, GasJetOpeningDuration, GasJetTiming, ProbeTiming, ProbeND, WFSND, TopViewND, Notes, BasePath, WFS, Topview, PointingScreen, ESpecScreenA, ESpecScreenB, PointingScreenBrem) VALUES "
                                       "(%1%,%2%,%3%,%4%,%5%,%6%,%7%,%8%,%9%,%10%,%11%,%12%,%13%,%14%,%15%,%16%,'%17%','%18%','%19%','%20%','%21%','%22%','%23%')")
                                        % DBEntry.Timestamp
                                        % date
                                        % DBEntry.EnergyOnTargetInMilliJoules
                                        % DBEntry.FarfieldEnergyInMilliJoules
                                        % DBEntry.PulseDurationInFemtoSeconds
                                        % DBEntry.GasjetBackpressureInBars
                                        % DBEntry.GasjetXInMicrons
                                        % DBEntry.GasjetYInMicrons
                                        % DBEntry.GasjetZInMicrons
                                        % DBEntry.GasjetDurationInMilliSeconds
                                        % DBEntry.GasjetTimingInMilliSeconds
                                        % DBEntry.ProbeTimingInFemtoSeconds
                                        % DBEntry.ProbeND
                                        % DBEntry.WFSND
                                        % DBEntry.TopviewND
                                        % DBEntry.Notes
                                        % DBEntry.ImageBasePath
                                        % (boost::format{"%1%/WFS_%2%.tiff"}                   % iso_date % DBEntry.Timestamp)
                                        % (boost::format{"%1%/Topview_%2%.tiff"}               % iso_date % DBEntry.Timestamp)
                                        % (boost::format{"%1%/PointingScreen_%2%.tiff"}        % iso_date % DBEntry.Timestamp)
                                        % (boost::format{"%1%/ESpecScreenA_%2%.tiff"}          % iso_date % DBEntry.Timestamp)
                                        % (boost::format{"%1%/ESpecScreenB_%2%.tiff"}          % iso_date % DBEntry.Timestamp)
                                        % (boost::format{"%1%/PointingScreenBrem_%2%.tiff"}    % iso_date % DBEntry.Timestamp);
        std::cout << statement << std::endl;
        std::unique_ptr<sql::PreparedStatement> query(DB_Connection->prepareStatement(statement.str()));
        query->executeQuery();
    } catch(sql::SQLException& e){
        std::cerr << e.what() << std::endl;
    }
}

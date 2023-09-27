#include <MariaDBController.h>
#include <boost/date_time.hpp>

MariaDBController::MariaDBController()
: SQL_Driver(sql::mariadb::get_driver_instance()),
  DB_Connection{nullptr} {
}

MariaDBController::~MariaDBController() = default;

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

void MariaDBController::AddEntry(const DBEntry_t &entry) const {
    AddEntryBeamlineParameters(entry);
    AddEntryShotRecord(entry);
}

void MariaDBController::AddEntryShotRecord(const DBEntry_t &entry) const {
    try {
        auto date = boost::gregorian::to_iso_extended_string(boost::gregorian::day_clock::local_day());
        auto statement = boost::format("INSERT INTO UT3Data.ShotRecord "
                                       "(Timestamp, Date, BasePath, WFS, TopView, PointingScreen, ESpecScreenA, ESpecScreenB, PointingScreenBrem) VALUES "
                                       "(%1%,       %2%,  %3%,      %4%, %5%,     %6,             %7,           %8,           %9)")
                         % entry.Timestamp
                         % date
                         % entry.ImageBasePath
                         // FIXME: this client is responsible to save the received images from TANGO device servers to disk,
                         //  so it knows the name of the files. The problem is to keep these names consistent within the code.
                         % boost::format{"%1%/WFS_%2%.tiff"}  % date % entry.Timestamp
                         % boost::format{"%1%/TopView_%2%.tiff"}  % date % entry.Timestamp
                         % boost::format{"%1%/PointingScreen_%2%.tiff"}  % date % entry.Timestamp
                         % boost::format{"%1%/ESpecScreenA_%2%.tiff"}  % date % entry.Timestamp
                         % boost::format{"%1%/ESpecScreenB_%2%.tiff"}  % date % entry.Timestamp
                         % boost::format{"%1%/PointingScreenBrem_%2%.tiff"}  % date % entry.Timestamp;
        std::unique_ptr<sql::PreparedStatement> query(DB_Connection->prepareStatement(statement.str()));
        query->executeQuery();
    } catch(sql::SQLException& e){
        std::cerr << "Error inserting new data entry: " << e.what() << std::endl;
    }
}

void MariaDBController::AddEntryBeamlineParameters(const DBEntry_t &entry) const {
    try {
        auto date = boost::gregorian::to_iso_extended_string(boost::gregorian::day_clock::local_day());
        auto statement = boost::format("INSERT INTO UT3Data.BeamlineParameters "
                                       "(Timestamp, Date, EnergyOnTarget, FarfieldEnergy, PulseDuration, GasJetBackPressure, GasJetPosX, GasJetPosY, GasJetPosZ, GasJetOpeningDuration, GasJetTiming, ProbeTiming, ProbeND, WFSND, TopViewND, Notes) VALUES "
                                       "(%1%,       %2%,  %3%,            %4%,            %5%,           %6,                 %7,         %8,         %9,         %10,                   %11,          %12,         %13,     %14,   %15,       %16)")
                                        % entry.Timestamp
                                        % date
                                        % entry.EnergyOnTargetInMilliJoules
                                        % entry.FarfieldEnergyInMilliJoules
                                        % entry.PulseDurationInFemtoSeconds
                                        % entry.GasjetBackpressureInBars
                                        % entry.GasjetYInMicrons
                                        % entry.GasjetXInMicrons
                                        % entry.GasjetZInMicrons
                                        % entry.GasjetDurationInMilliSeconds
                                        % entry.GasjetTimingInMilliSeconds
                                        % entry.ProbeTimingInFemtoSeconds
                                        % entry.ProbeND
                                        % entry.WFSND
                                        % entry.TopviewND
                                        % entry.Notes;
        std::unique_ptr<sql::PreparedStatement> query(DB_Connection->prepareStatement(statement.str()));
        query->executeQuery();
    } catch(sql::SQLException& e){
        std::cerr << "Error inserting new data entry: " << e.what() << std::endl;
    }
}

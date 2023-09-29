#pragma once

#include <conncpp.hpp>
#include <boost/format.hpp>

struct DBEntry_t {
    long Timestamp;
    std::string ImageBasePath;
    float EnergyOnTargetInMilliJoules;
    float FarfieldEnergyInMilliJoules;
    float PulseDurationInFemtoSeconds;
    float GasjetBackpressureInBars;
    float GasjetXInMicrons;
    float GasjetYInMicrons;
    float GasjetZInMicrons;
    float GasjetTimingInMilliSeconds;
    float GasjetDurationInMilliSeconds;
    float ProbeTimingInFemtoSeconds;
    float ProbeND;
    float WFSND;
    float TopviewND;
    std::string Notes;
};

class MariaDBController {
public:
    MariaDBController();
    ~MariaDBController();

    void Connect();
    void Disconnect() const;
    void AddEntryShotRecord() const;
    unsigned long GetLatestShotID() const;

    std::unique_ptr<sql::Driver> SQL_Driver;
    std::unique_ptr<sql::Connection> DB_Connection;
    sql::SQLString DB_URL;
    std::string DB_USER;
    std::string DB_PASSWORD;
    std::string DB_HOST;
    std::string DB_PORT;
    std::string DB_SCHEMA;

    DBEntry_t DBEntry;
};

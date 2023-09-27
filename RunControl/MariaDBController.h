#pragma once

#include <conncpp.hpp>
#include <boost/format.hpp>
//#include <tango.h>

class MariaDBController {
public:
    MariaDBController();
    ~MariaDBController();

    void Connect();
    void Disconnect();

    std::unique_ptr<sql::Driver> SQL_Driver;
    std::unique_ptr<sql::Connection> DB_Connection;
    sql::SQLString DB_URL;
    std::string DB_USER;
    std::string DB_PASSWORD;
    std::string DB_HOST;
    std::string DB_PORT;
    std::string DB_SCHEMA;
};

#include <MariaDBController.h>

MariaDBController::MariaDBController()
: SQL_Driver(sql::mariadb::get_driver_instance()),
  DB_Connection{nullptr} {
}

void MariaDBController::Connect() {
    sql::Properties properties({
        {"user", DB_USER},
        {"password", DB_PASSWORD}
    });
    DB_Connection.reset(SQL_Driver->connect(DB_URL, properties));
}

void MariaDBController::Disconnect() {

}

MariaDBController::~MariaDBController() {

}

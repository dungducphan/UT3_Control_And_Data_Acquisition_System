#include <CameraDriver.h>

CameraDriver::CameraDriver(std::string &ip_addr) :
ip_address(ip_addr),
spinnaker_camera_ptr(nullptr),
pylon_camera_ptr(nullptr),
pco_camera_ptr(nullptr) {
    std::cout << "CameraDriver constructor" << std::endl;
}

BaslerCameraDriver::BaslerCameraDriver(std::string &ip_addr) : CameraDriver(ip_addr) {
    std::cout << "BaslerCameraDriver constructor" << std::endl;
}

void BaslerCameraDriver::start_acquisition() {
    std::cout << "BaslerCameraDriver start_acquisition" << std::endl;
}

void BaslerCameraDriver::stop_acquisition() {
    std::cout << "BaslerCameraDriver stop_acquisition" << std::endl;
}

void BaslerCameraDriver::manual_trigger() {
    std::cout << "BaslerCameraDriver manual_trigger" << std::endl;
}

void BaslerCameraDriver::configure() {
std::cout << "BaslerCameraDriver configure" << std::endl;
}

PCOCameraDriver::PCOCameraDriver(std::string &ip_addr) : CameraDriver(ip_addr) {
    std::cout << "PCOCameraDriver constructor" << std::endl;
}

void PCOCameraDriver::start_acquisition() {
    std::cout << "PCOCameraDriver start_acquisition" << std::endl;
}

void PCOCameraDriver::stop_acquisition() {
    std::cout << "PCOCameraDriver stop_acquisition" << std::endl;
}

void PCOCameraDriver::manual_trigger() {
    std::cout << "PCOCameraDriver manual_trigger" << std::endl;
}

void PCOCameraDriver::configure() {
    std::cout << "PCOCameraDriver configure" << std::endl;
}

FLIRCameraDriver::FLIRCameraDriver(std::string &ip_addr) : CameraDriver(ip_addr) {
    std::cout << "FLIRCameraDriver constructor" << std::endl;
}

void FLIRCameraDriver::start_acquisition() {
    std::cout << "FLIRCameraDriver start_acquisition" << std::endl;
}

void FLIRCameraDriver::stop_acquisition() {
    std::cout << "FLIRCameraDriver stop_acquisition" << std::endl;
}

void FLIRCameraDriver::manual_trigger() {
    std::cout << "FLIRCameraDriver manual_trigger" << std::endl;
}

void FLIRCameraDriver::configure() {
    std::cout << "FLIRCameraDriver configure" << std::endl;
}


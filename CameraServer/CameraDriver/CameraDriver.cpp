#include <TANGOCamera.h>
#include <CameraDriver.h>
#include <utility>

CameraDriver::CameraDriver(std::string ip_addr) : IPAddress(std::move(ip_addr)), ParentTangoCameraPtr(nullptr) {
    std::cout << "CameraDriver constructor" << std::endl;
}

void CameraDriver::SetTangoCameraPtr(const TANGOCamera_ns::TANGOCamera* dev_ptr) {
    ParentTangoCameraPtr = const_cast<TANGOCamera_ns::TANGOCamera*>(dev_ptr);
}

BaslerCameraDriver::BaslerCameraDriver(const std::string &ip_addr) : CameraDriver(ip_addr) {
    std::cout << "BaslerCameraDriver constructor" << std::endl;
}

void BaslerCameraDriver::StartAcquisition() {
    std::cout << "BaslerCameraDriver StartAcquisition" << std::endl;
}

void BaslerCameraDriver::StopAcquisition() {
    std::cout << "BaslerCameraDriver StopAcquisition" << std::endl;
}

void BaslerCameraDriver::ManualTrigger() {
    std::cout << "BaslerCameraDriver manual_trigger" << std::endl;
}

void BaslerCameraDriver::Configure() {
std::cout << "BaslerCameraDriver configure" << std::endl;
}

PCOCameraDriver::PCOCameraDriver(const std::string &ip_addr) : CameraDriver(ip_addr) {
    std::cout << "PCOCameraDriver constructor" << std::endl;
}

void PCOCameraDriver::StartAcquisition() {
    std::cout << "PCOCameraDriver StartAcquisition" << std::endl;
}

void PCOCameraDriver::StopAcquisition() {
    std::cout << "PCOCameraDriver StopAcquisition" << std::endl;
}

void PCOCameraDriver::ManualTrigger() {
    std::cout << "PCOCameraDriver manual_trigger" << std::endl;
}

void PCOCameraDriver::Configure() {
    std::cout << "PCOCameraDriver configure" << std::endl;
}

FLIRCameraDriver::FLIRCameraDriver(const std::string &ip_addr) : CameraDriver(ip_addr) {
    std::cout << "FLIRCameraDriver constructor" << std::endl;
}

void FLIRCameraDriver::StartAcquisition() {
    std::cout << "FLIRCameraDriver StartAcquisition" << std::endl;
}

void FLIRCameraDriver::StopAcquisition() {
    std::cout << "FLIRCameraDriver StopAcquisition" << std::endl;
}

void FLIRCameraDriver::ManualTrigger() {
    std::cout << "FLIRCameraDriver manual_trigger" << std::endl;
}

void FLIRCameraDriver::Configure() {
    std::cout << "FLIRCameraDriver configure" << std::endl;

//    Spinnaker::CameraList camList = Spinnaker::System::GetInstance()->GetCameras();
//    bool foundDevice = false;
//    for (int i = 0; i < camList.GetSize(); i++) {
//        Spinnaker::CameraPtr pCam = camList.GetByIndex(i);
//        if (IsReadable(pCam->TLDevice.GevDeviceIPAddress)) {
//            if (pCam->TLDevice.GevDeviceIPAddress.GetValue() == deviceSerialNumber) {
//                foundDevice = true;
//                pCam->Init();
//                SpinnakerCameraPtr.reset(&pCam);
//                std::cout << "Found device " << device_name << "." << std::endl;
//            }
//        }
//    }
//    if (!foundDevice) {
//        std::cout << "Device " << device_name << " not found!" << std::endl;
//        set_state(Tango::OFF);
//    }
//
//    camList.Clear();
}


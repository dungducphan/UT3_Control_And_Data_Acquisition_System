#include <TANGOCamera.h>
#include <CameraDriver.h>

#include <utility>

CameraDriver::CameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) :
        TangoCameraPtr(const_cast<TANGOCamera_ns::TANGOCamera *>(tango_device_ptr)) {
    std::cout << "CameraDriver constructor" << std::endl;
}

/*--------------------------------------------------------------------------------------------------------------------*/

BaslerCameraDriver::BaslerCameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) : CameraDriver(
        tango_device_ptr) {
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

/*--------------------------------------------------------------------------------------------------------------------*/

PCOCameraDriver::PCOCameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) : CameraDriver(tango_device_ptr) {
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

/*--------------------------------------------------------------------------------------------------------------------*/

FLIRCameraDriver::FLIRCameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) : CameraDriver(
        tango_device_ptr) {
    std::cout << "FLIRCameraDriver constructor" << std::endl;

    Spinnaker::CameraList camList = Spinnaker::System::GetInstance()->GetCameras();
    bool foundDevice = false;
    for (int i = 0; i < camList.GetSize(); i++) {
        Spinnaker::CameraPtr pCam = camList.GetByIndex(i);
        if (IsReadable(pCam->TLDevice.GevDeviceIPAddress)) {
            std::cout << pCam->TLDevice.GevDeviceIPAddress.GetValue() << std::endl;
            if (pCam->TLDevice.GevDeviceIPAddress.GetValue() == stoi(TangoCameraPtr->ipaddress)) {
                foundDevice = true;
                pCam->Init();
                SpinnakerCameraPtr.reset(&pCam);
                std::cout << "Found device " << TangoCameraPtr->get_name() << "." << std::endl;
            }
        }
    }
    if (!foundDevice) {
        std::cout << "Device " << TangoCameraPtr->get_name() << " not found!" << std::endl;
        TangoCameraPtr->set_state(Tango::OFF);
    }

    camList.Clear();
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
}


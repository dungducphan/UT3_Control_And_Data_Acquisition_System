#include <TANGOCamera.h>
#include <CameraDriver.h>

#include <unistd.h>
#include <filesystem>
#include <string>

#include <boost/format.hpp>

CameraDriver::CameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) :
        TangoCameraPtr(const_cast<TANGOCamera_ns::TANGOCamera *>(tango_device_ptr)),
        LinuxTimestampMilliseconds(0) {
    CreateFullOutputPath();
}

int64_t CameraDriver::GetIPv4AddressInteger(const std::string& ipaddress) const {
    int result;
    int64_t IPv4Identifier = 0;
    struct in_addr addr{};
    result = inet_pton(AF_INET, ipaddress.c_str(), &(addr));

    if (result == -1 || result == 0) {
        std::cout << "Failed to convert the IP address " << ipaddress \
            << " of camera " << TangoCameraPtr->get_name() << "." << std::endl;
    } else IPv4Identifier = ntohl(*((uint32_t *) &(addr)));

    return (int64_t) IPv4Identifier;
}

void CameraDriver::CreateFullOutputPath() {
    FullOutputPath = TangoCameraPtr->attr_baseOutputPath_read[0];
    FullOutputPath += TangoCameraPtr->get_name();
    std::filesystem::create_directories(std::filesystem::path{FullOutputPath});
}

/*--------------------------------------------------------------------------------------------------------------------*/

BaslerCameraDriver::BaslerCameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) : CameraDriver(
        tango_device_ptr) {
}

void BaslerCameraDriver::StartAcquisition() {
}

void BaslerCameraDriver::StopAcquisition() {
}

void BaslerCameraDriver::ManualTrigger() {
}

void BaslerCameraDriver::Configure() {
}

/*--------------------------------------------------------------------------------------------------------------------*/

PCOCameraDriver::PCOCameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) : CameraDriver(tango_device_ptr) {
}

void PCOCameraDriver::StartAcquisition() {
}

void PCOCameraDriver::StopAcquisition() {
}

void PCOCameraDriver::ManualTrigger() {
}

void PCOCameraDriver::Configure() {
}

/*--------------------------------------------------------------------------------------------------------------------*/

#include <Spinnaker.h>
#include <SpinGenApi/SpinnakerGenApi.h>
#include <SpinnakerDefs.h>

FLIRCameraDriver::FLIRCameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) : CameraDriver(tango_device_ptr) {
    ResultImagePtr = nullptr;
    SpinnakerCameraPtr = nullptr;
    SpinnakerAcquisitionThread = nullptr;
    FLIRCameraInit();
}

void FLIRCameraDriver::StartAcquisition() {
    try {
        TangoCameraPtr->set_state(Tango::RUNNING);
        SpinnakerCameraPtr->BeginAcquisition();
        SpinnakerAcquisitionThread = new std::thread(&FLIRCameraDriver::AcquisitionLoop, this);
    } catch (Spinnaker::Exception& e) {
        std::cout << "Exception caught on  " << TangoCameraPtr->get_name() << ": " << e.what() << std::endl;
    }
}

void FLIRCameraDriver::StopAcquisition() {
    try {
        TangoCameraPtr->set_state(Tango::ON);
        auto currentTriggerSrc = SpinnakerCameraPtr->TriggerSource.GetValue();
        SpinnakerCameraPtr->TriggerSource.SetValue(Spinnaker::TriggerSourceEnums::TriggerSource_Software);
        SpinnakerCameraPtr->TriggerSoftware();
        usleep(100);
        SpinnakerCameraPtr->TriggerSource.SetValue(currentTriggerSrc);
        SpinnakerCameraPtr->EndAcquisition();
    } catch (Spinnaker::Exception& e) {
        std::cout << "Exception caught on  " << TangoCameraPtr->get_name() << ": " << e.what() << std::endl;
    }
}

void FLIRCameraDriver::ManualTrigger() {
    auto currentTriggerSrc = SpinnakerCameraPtr->TriggerSource.GetValue();
    SpinnakerCameraPtr->TriggerSource.SetValue(Spinnaker::TriggerSourceEnums::TriggerSource_Software);
    SpinnakerCameraPtr->TriggerSoftware();
    usleep(100);
    SpinnakerCameraPtr->TriggerSource.SetValue(currentTriggerSrc);
}

void FLIRCameraDriver::FLIRCameraInit() {
    Spinnaker::CameraList camList = Spinnaker::System::GetInstance()->GetCameras();
    bool foundDevice = false;
    for (int i = 0; i < camList.GetSize(); i++) {
        Spinnaker::CameraPtr pCam = camList.GetByIndex(i);
        if (IsReadable(pCam->TLDevice.DeviceSerialNumber)) {
            if (pCam->TLDevice.DeviceSerialNumber.GetValue() == TangoCameraPtr->serialNumber.c_str()) {
                foundDevice = true;
                SpinnakerCameraPtr = pCam;
            }
        }
    }
    if (foundDevice) {
        SpinnakerCameraPtr->Init();
        TangoCameraPtr->set_state(Tango::ON);
        std::cout << "Found device " << TangoCameraPtr->get_name() << "." << std::endl;
        Configure();

        // @ ver. 0.x, let's not worry about ROI at all, the image size is the maximum size.
        ImageWidth = SpinnakerCameraPtr->WidthMax.GetValue();
        ImageHeight = SpinnakerCameraPtr->HeightMax.GetValue();
        ImageDataPtr = std::shared_ptr<Tango::DevUShort>(new Tango::DevUShort[ImageWidth * ImageHeight], std::default_delete<Tango::DevUShort[]>());
    } else {
        TangoCameraPtr->set_state(Tango::OFF);
        std::cout << "Device " << TangoCameraPtr->get_name() << " not found!" << std::endl;
    }

    camList.Clear();
}

void FLIRCameraDriver::Configure() {
    try {
        SpinnakerCameraPtr->AcquisitionMode.SetValue(Spinnaker::AcquisitionModeEnums::AcquisitionMode_Continuous);
        SpinnakerCameraPtr->AcquisitionFrameRateEnable.SetValue(false);
        SpinnakerCameraPtr->DeviceLinkThroughputLimit.SetValue(SpinnakerCameraPtr->DeviceLinkThroughputLimit.GetMax());
        SpinnakerCameraPtr->ExposureMode.SetValue(Spinnaker::ExposureModeEnums::ExposureMode_Timed);
        SpinnakerCameraPtr->ExposureAuto.SetValue(Spinnaker::ExposureAutoEnums::ExposureAuto_Off);
        SpinnakerCameraPtr->ExposureTime.SetValue(1E5);
        SpinnakerCameraPtr->GainAuto.SetValue(Spinnaker::GainAutoEnums::GainAuto_Off);
        SpinnakerCameraPtr->Gain.SetValue(0);
        SpinnakerCameraPtr->Width.SetValue(SpinnakerCameraPtr->Width.GetMax());
        SpinnakerCameraPtr->Height.SetValue(SpinnakerCameraPtr->Height.GetMax());
        SpinnakerCameraPtr->PixelFormat.SetValue(Spinnaker::PixelFormatEnums::PixelFormat_Mono16);
        SpinnakerCameraPtr->BinningSelector.SetValue(Spinnaker::BinningSelectorEnums::BinningSelector_All);
        SpinnakerCameraPtr->BinningHorizontalMode.SetValue(Spinnaker::BinningHorizontalModeEnums::BinningHorizontalMode_Average);
        SpinnakerCameraPtr->BinningVerticalMode.SetValue(Spinnaker::BinningVerticalModeEnums::BinningVerticalMode_Average);
        SpinnakerCameraPtr->BinningHorizontal.SetValue(1);
        SpinnakerCameraPtr->BinningVertical.SetValue(1);
        SpinnakerCameraPtr->TriggerSelector.SetValue(Spinnaker::TriggerSelectorEnums::TriggerSelector_FrameStart);
        SpinnakerCameraPtr->TriggerMode.SetValue(Spinnaker::TriggerModeEnums::TriggerMode_On);
        SpinnakerCameraPtr->TriggerDelay.SetValue(SpinnakerCameraPtr->TriggerDelay.GetMin());

        // Default setting is automatic trigger (trigger signal comes from timing system)
        SpinnakerCameraPtr->TriggerSource.SetValue(Spinnaker::TriggerSourceEnums::TriggerSource_Line0);
        SpinnakerCameraPtr->TriggerActivation.SetValue(Spinnaker::TriggerActivationEnums::TriggerActivation_RisingEdge);
    } catch (Spinnaker::Exception& e) {
        std::cout << "Exception caught on  " << TangoCameraPtr->get_name() << ": " << e.what() << std::endl;
        TangoCameraPtr->set_state(Tango::FAULT);
    }
}

void FLIRCameraDriver::AcquisitionLoop() {
    while (TangoCameraPtr->get_state() == Tango::RUNNING) {
        ResultImagePtr = SpinnakerCameraPtr->GetNextImage();
        if (ResultImagePtr->IsIncomplete()) {
            std::cout << Spinnaker::Image::GetImageStatusDescription(ResultImagePtr->GetImageStatus()) << std::endl;
        } else {
            // Only handling data if the StopAcquisition has NOT been issue
            if (TangoCameraPtr->get_state() == Tango::RUNNING) {
                std::copy((Tango::DevUShort *) ResultImagePtr->GetData(),
                          (Tango::DevUShort *) ResultImagePtr->GetData() + ImageWidth * ImageHeight,
                          ImageDataPtr.get());
#ifdef ENABLE_DEBUG_FEATURES
                std::cout << "Pushing data ready event for " << TangoCameraPtr->get_name() << std::endl;
#endif
                TangoCameraPtr->push_data_ready_event("DynamicImage");
            }
        }
        ResultImagePtr->Release();
    }
}


#include <TANGOCamera.h>
#include <CameraDriver.h>

#include <unistd.h>
#include <filesystem>
#include <string>

#include <boost/format.hpp>

CameraDriver::CameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) :
        TangoCameraPtr(const_cast<TANGOCamera_ns::TANGOCamera *>(tango_device_ptr)),
        ManualTriggerSet(false),
        LinuxTimestampMilliseconds(0),
        ShotID(0) {
    CreateFullOutputPath();
}

int64_t CameraDriver::GetIPv4AddressInteger() const {
    int result;
    int64_t IPv4Identifier = 0;
    struct in_addr addr{};
    result = inet_pton(AF_INET, TangoCameraPtr->ipaddress.c_str(), &(addr));

    if (result == -1 || result == 0) {
        std::cout << "Failed to convert the IP address " << TangoCameraPtr->ipaddress \
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

FLIRCameraDriver::FLIRCameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) :
CameraDriver(tango_device_ptr),
SpinnakerCameraPtr(nullptr),
ResultImagePtr(nullptr),
SpinnakerAcquisitionThread(nullptr) {
    FLIRCameraInit();
}

void FLIRCameraDriver::StartAcquisition() {
    try {
        Configure();
        SpinnakerCameraPtr->BeginAcquisition();
        TangoCameraPtr->set_state(Tango::RUNNING);
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
    if (!ManualTriggerSet) {
        SpinnakerCameraPtr->TriggerSource.SetValue(Spinnaker::TriggerSourceEnums::TriggerSource_Software);
        ManualTriggerSet = true;
    }

    SpinnakerCameraPtr->TriggerSoftware();
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
        SpinnakerCameraPtr->PixelFormat.SetValue(Spinnaker::PixelFormatEnums::PixelFormat_Mono8);
        SpinnakerCameraPtr->BinningSelector.SetValue(Spinnaker::BinningSelectorEnums::BinningSelector_All);
        SpinnakerCameraPtr->BinningHorizontalMode.SetValue(Spinnaker::BinningHorizontalModeEnums::BinningHorizontalMode_Average);
        SpinnakerCameraPtr->BinningVerticalMode.SetValue(Spinnaker::BinningVerticalModeEnums::BinningVerticalMode_Average);
        SpinnakerCameraPtr->BinningHorizontal.SetValue(2);
        SpinnakerCameraPtr->BinningVertical.SetValue(2);
        SpinnakerCameraPtr->TriggerSelector.SetValue(Spinnaker::TriggerSelectorEnums::TriggerSelector_FrameStart);
        SpinnakerCameraPtr->TriggerMode.SetValue(Spinnaker::TriggerModeEnums::TriggerMode_On);
        SpinnakerCameraPtr->TriggerDelay.SetValue(SpinnakerCameraPtr->TriggerDelay.GetMin());

        // Default setting is automatic trigger (trigger signal comes from timing system)
        ManualTriggerSet = false;
        SpinnakerCameraPtr->TriggerSource.SetValue(Spinnaker::TriggerSourceEnums::TriggerSource_Line0);
        SpinnakerCameraPtr->TriggerActivation.SetValue(Spinnaker::TriggerActivationEnums::TriggerActivation_RisingEdge);
    } catch (Spinnaker::Exception& e) {
        std::cout << "Exception caught on  " << TangoCameraPtr->get_name() << ": " << e.what() << std::endl;
        TangoCameraPtr->set_state(Tango::FAULT);
    }
}

void FLIRCameraDriver::FLIRCameraInit() {
    Spinnaker::CameraList camList = Spinnaker::System::GetInstance()->GetCameras();
    bool foundDevice = false;
    for (int i = 0; i < camList.GetSize(); i++) {
        Spinnaker::CameraPtr pCam = camList.GetByIndex(i);
        if (IsReadable(pCam->TLDevice.GevDeviceIPAddress)) {
            if (pCam->TLDevice.GevDeviceIPAddress.GetValue() == GetIPv4AddressInteger()) {
                foundDevice = true;
                SpinnakerCameraPtr = pCam;
            }
        }
    }
    if (foundDevice) {
        SpinnakerCameraPtr->Init();
        TangoCameraPtr->set_state(Tango::ON);
        std::cout << "Found device " << TangoCameraPtr->get_name() << "." << std::endl;
    } else {
        TangoCameraPtr->set_state(Tango::OFF);
        std::cout << "Device " << TangoCameraPtr->get_name() << " not found!" << std::endl;
    }

    camList.Clear();
}

void FLIRCameraDriver::AcquisitionLoop() {
    // FIXME: No software synchronization between cameras now. \
    //  Synchronization is done in hardware via the trigger signal from the timing system. \
    //  This is OK for the shot mode, but if operators want to issue a manual trigger, that \
    //  trigger is not propagated to all the cameras and create an issue of mismatched ShotID

    std::string filename;
    while (TangoCameraPtr->get_state() == Tango::RUNNING) {
        try {
            ResultImagePtr = SpinnakerCameraPtr->GetNextImage();
            if (ResultImagePtr->IsIncomplete()) {
                std::cout << Spinnaker::Image::GetImageStatusDescription(ResultImagePtr->GetImageStatus()) << std::endl;
            } else {
                auto now = chrono::system_clock::now();
                LinuxTimestampMilliseconds = duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
                if (TangoCameraPtr->get_state() == Tango::RUNNING) {
                    if (!ManualTriggerSet) {
                        filename = (boost::format("%s/shot_%05d_%d.tiff") % FullOutputPath % ShotID %
                                                LinuxTimestampMilliseconds).str();
                    } else {
                        filename = (boost::format("%s/test_%05d_%d.tiff") % FullOutputPath % ShotID %
                                    LinuxTimestampMilliseconds).str();
                    }
                    ResultImagePtr->Save(filename.c_str());
#ifdef ENABLE_DEBUG_FEATURES
                    std::cout << "Image saved at " << filename.str() << std::endl;
#endif
                }
            }
            try {
                ResultImagePtr->Release();
            } catch (Spinnaker::Exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        catch (Spinnaker::Exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

        // Only increasing ShotID in AutomaticTrigger mode (shot mode)
        if (!ManualTriggerSet) ShotID++;
    }
}


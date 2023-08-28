#include <TANGOCamera.h>
#include <CameraDriver.h>

#include <unistd.h>
#include <filesystem>
#include <string>

CameraDriver::CameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) :
        TangoCameraPtr(const_cast<TANGOCamera_ns::TANGOCamera *>(tango_device_ptr)),
        RunningMode(RunningMode_t::UnsetMode),
        ImageWidth(0),
        ImageHeight(0) {
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

void BaslerCameraDriver::ConfigureShotMode() {
}

void BaslerCameraDriver::ConfigureFreeRunMode() {
}

void BaslerCameraDriver::ConfigureManualTriggerMode() {
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

void PCOCameraDriver::ConfigureShotMode() {
}

void PCOCameraDriver::ConfigureFreeRunMode() {
}

void PCOCameraDriver::ConfigureManualTriggerMode() {
}

/*--------------------------------------------------------------------------------------------------------------------*/

#include <Spinnaker.h>
#include <SpinGenApi/SpinnakerGenApi.h>

FLIRCameraDriver::FLIRCameraDriver(const TANGOCamera_ns::TANGOCamera *tango_device_ptr) : CameraDriver(tango_device_ptr) {
    ResultImagePtr = nullptr;
    SpinnakerCameraPtr = nullptr;
    SpinnakerAcquisitionThread = nullptr;

    FLIRCameraInit();
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
        SetGeneralConfiguration();

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

void FLIRCameraDriver::SetGeneralConfiguration() {
    try {
        SpinnakerCameraPtr->AcquisitionMode.SetValue(Spinnaker::AcquisitionModeEnums::AcquisitionMode_Continuous);
        SpinnakerCameraPtr->AcquisitionFrameRateEnable.SetValue(false);
        SpinnakerCameraPtr->DeviceLinkThroughputLimit.SetValue(SpinnakerCameraPtr->DeviceLinkThroughputLimit.GetMax());
        SpinnakerCameraPtr->ExposureMode.SetValue(Spinnaker::ExposureModeEnums::ExposureMode_Timed);
        SpinnakerCameraPtr->ExposureAuto.SetValue(Spinnaker::ExposureAutoEnums::ExposureAuto_Off);
        SpinnakerCameraPtr->ExposureTime.SetValue(5E4);
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
        SpinnakerCameraPtr->TriggerDelay.SetValue(SpinnakerCameraPtr->TriggerDelay.GetMin());
    } catch (Spinnaker::Exception& e) {
        std::cout << "Exception caught on configuring " << TangoCameraPtr->get_name() << ": " << e.what() << std::endl;
        TangoCameraPtr->set_state(Tango::FAULT);
    }
}

void FLIRCameraDriver::StartAcquisition() {
    if (RunningMode == RunningMode_t::UnsetMode) {
#ifdef ENABLE_DEBUG_FEATURES
        std::cout << "RunningMode is not set for " << TangoCameraPtr->get_name() << std::endl;
#endif
        return;
    }

    try {
        TangoCameraPtr->set_state(Tango::RUNNING);
        SpinnakerCameraPtr->BeginAcquisition();
        SpinnakerAcquisitionThread = new std::thread(&FLIRCameraDriver::AcquisitionLoop, this);
    } catch (Spinnaker::Exception& e) {
        std::cout << "Exception caught on starting acquisition:" << TangoCameraPtr->get_name() << ": " << e.what() << std::endl;
    }
}

void FLIRCameraDriver::StopAcquisition() {
    try {
        // TODO: thread-safe as long as timing system running (triggers are issued to the hardware).
        //  Might need a state-change safe-guard if the timing system is not running and AcquisitionLoop thread is stuck in the
        //  GetNextImage() call.
        TangoCameraPtr->set_state(Tango::ON);
        if (RunningMode == RunningMode_t::ManualTriggerMode) ManualTrigger();
        if (SpinnakerAcquisitionThread != nullptr) SpinnakerAcquisitionThread->join();
        SpinnakerCameraPtr->EndAcquisition();
    } catch (Spinnaker::Exception& e) {
        std::cout << "Exception caught on stopping acquisition:" << TangoCameraPtr->get_name() << ": " << e.what() << std::endl;
    }
}

void FLIRCameraDriver::ManualTrigger() {
    if (RunningMode != RunningMode_t::ManualTriggerMode) {
#ifdef ENABLE_DEBUG_FEATURES
        std::cout << "ManualTrigger is not allowed in FreeRunMode for " << TangoCameraPtr->get_name() << std::endl;
#endif
        return;
    }

    SpinnakerCameraPtr->TriggerSoftware();
    usleep(500);
}

void FLIRCameraDriver::ConfigureShotMode() {
    if (RunningMode == RunningMode_t::ShotMode) return;

    try {
        SpinnakerCameraPtr->TriggerSelector.SetValue(Spinnaker::TriggerSelectorEnums::TriggerSelector_AcquisitionStart);
        SpinnakerCameraPtr->TriggerMode.SetValue(Spinnaker::TriggerModeEnums::TriggerMode_Off);
        SpinnakerCameraPtr->TriggerSelector.SetValue(Spinnaker::TriggerSelectorEnums::TriggerSelector_FrameStart);
        SpinnakerCameraPtr->TriggerMode.SetValue(Spinnaker::TriggerModeEnums::TriggerMode_On);
        SpinnakerCameraPtr->TriggerSource.SetValue(Spinnaker::TriggerSourceEnums::TriggerSource_Line0);
        SpinnakerCameraPtr->TriggerActivation.SetValue(Spinnaker::TriggerActivationEnums::TriggerActivation_RisingEdge);
        RunningMode = RunningMode_t::ShotMode;
    } catch (Spinnaker::Exception& e) {
        std::cout << "Exception caught on configuring" << TangoCameraPtr->get_name() << ": " << e.what() << std::endl;
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
        if (ResultImagePtr.IsValid()) ResultImagePtr->Release();
    }
}

void FLIRCameraDriver::ConfigureFreeRunMode() {
    if (RunningMode == RunningMode_t::FreeRunMode) return;
    try {
        SpinnakerCameraPtr->TriggerSelector.SetValue(Spinnaker::TriggerSelectorEnums::TriggerSelector_FrameStart);
        SpinnakerCameraPtr->TriggerMode.SetValue(Spinnaker::TriggerModeEnums::TriggerMode_Off);
        SpinnakerCameraPtr->TriggerSelector.SetValue(Spinnaker::TriggerSelectorEnums::TriggerSelector_AcquisitionStart);
        SpinnakerCameraPtr->TriggerMode.SetValue(Spinnaker::TriggerModeEnums::TriggerMode_Off);
        RunningMode = RunningMode_t::FreeRunMode;
    } catch (Spinnaker::Exception& e) {
        std::cout << "Exception caught on configuring " << TangoCameraPtr->get_name() << ": " << e.what() << std::endl;
        TangoCameraPtr->set_state(Tango::FAULT);
    }
}

void FLIRCameraDriver::ConfigureManualTriggerMode() {
    if (RunningMode == RunningMode_t::ManualTriggerMode) return;
    try {
        SpinnakerCameraPtr->TriggerSelector.SetValue(Spinnaker::TriggerSelectorEnums::TriggerSelector_AcquisitionStart);
        SpinnakerCameraPtr->TriggerMode.SetValue(Spinnaker::TriggerModeEnums::TriggerMode_Off);
        SpinnakerCameraPtr->TriggerSelector.SetValue(Spinnaker::TriggerSelectorEnums::TriggerSelector_FrameStart);
        SpinnakerCameraPtr->TriggerMode.SetValue(Spinnaker::TriggerModeEnums::TriggerMode_On);
        SpinnakerCameraPtr->TriggerSource.SetValue(Spinnaker::TriggerSourceEnums::TriggerSource_Software);
        RunningMode = RunningMode_t::ManualTriggerMode;
    } catch (Spinnaker::Exception& e) {
        std::cout << "Exception caught on configuring " << TangoCameraPtr->get_name() << ": " << e.what() << std::endl;
        TangoCameraPtr->set_state(Tango::FAULT);
    }
}


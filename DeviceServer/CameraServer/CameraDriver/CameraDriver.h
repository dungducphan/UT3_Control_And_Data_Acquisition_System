#pragma once

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <arpa/inet.h>

namespace TANGOCamera_ns {
    class TANGOCamera;
}

enum RunningMode_t {
    UnsetMode,
    ShotMode,
    FreeRunMode,
    ManualTriggerMode
};

class CameraDriver {
public:
    explicit CameraDriver(const TANGOCamera_ns::TANGOCamera* tango_device_ptr);
    virtual void StartAcquisition() = 0;
    virtual void StopAcquisition() = 0;
    virtual void ManualTrigger() = 0;
    virtual void ConfigureShotMode() = 0;
    virtual void ConfigureFreeRunMode() = 0;
    virtual void ConfigureManualTriggerMode() = 0;

    TANGOCamera_ns::TANGOCamera* TangoCameraPtr;
    unsigned short ImageWidth{};
    unsigned short ImageHeight{};
    std::shared_ptr<Tango::DevUShort> ImageDataPtr;
    RunningMode_t RunningMode;
};

/*--------------------------------------------------------------------------------------------------------------------*/

#include <pylon/PylonIncludes.h>
#include <pylon/Device.h>
#include <pylon/TypeMappings.h>
#include <pylon/ConfigurationEventHandler.h>
#include <pylon/ImageEventHandler.h>
#include <pylon/GrabResultPtr.h>
#include <pylon/GrabResultData.h>
#include <pylon/InstantCamera.h>
#include <pylon/ParameterIncludes.h>
#include <pylon/EnumParameterT.h>
#include <pylon/EnumParameter.h>

class BaslerCameraDriver : public CameraDriver {
public:
    explicit BaslerCameraDriver(const TANGOCamera_ns::TANGOCamera* tango_device_ptr);
    void StartAcquisition() final;
    void StopAcquisition() final;
    void ManualTrigger() final;
    void ConfigureShotMode() final;
    void ConfigureFreeRunMode() final;
    void ConfigureManualTriggerMode() final;

private:
    std::unique_ptr<Pylon::CInstantCamera> PylonCameraPtr;
};

/*--------------------------------------------------------------------------------------------------------------------*/

#include <pco.camera/stdafx.h>
#include <pco.camera/camera.h>
#include <pco.camera/cameraexception.h>

class PCOCameraDriver : public CameraDriver {
public:
    explicit PCOCameraDriver(const TANGOCamera_ns::TANGOCamera* tango_device_ptr);
    void StartAcquisition() final;
    void StopAcquisition() final;
    void ManualTrigger() final;
    void ConfigureShotMode() final;
    void ConfigureFreeRunMode() final;
    void ConfigureManualTriggerMode() final;

private:
    std::shared_ptr<pco::Camera> PCOCameraPtr;
};

/*--------------------------------------------------------------------------------------------------------------------*/

#include <Spinnaker.h>
#include <SpinGenApi/SpinnakerGenApi.h>
#include <SpinnakerDefs.h>

class FLIRCameraDriver : public CameraDriver {
public:
    explicit FLIRCameraDriver(const TANGOCamera_ns::TANGOCamera* tango_device_ptr);
    void StartAcquisition() final;
    void StopAcquisition() final;
    void ManualTrigger() final;
    void ConfigureShotMode() final;
    void ConfigureFreeRunMode() final;
    void ConfigureManualTriggerMode() final;

private:
    Spinnaker::CameraPtr SpinnakerCameraPtr;
    Spinnaker::ImagePtr ResultImagePtr;
    std::thread* SpinnakerAcquisitionThread{};

    void FLIRCameraInit();
    void SetGeneralConfiguration();
    void AcquisitionLoop();
};
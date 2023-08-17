#pragma once

#include <string>
#include <iostream>

namespace TANGOCamera_ns {
    class TANGOCamera;
};

class CameraDriver {
public:
    explicit CameraDriver(const TANGOCamera_ns::TANGOCamera* tango_device_ptr);
    virtual void StartAcquisition() = 0;
    virtual void StopAcquisition() = 0;
    virtual void ManualTrigger() = 0;
    virtual void Configure() = 0;

    TANGOCamera_ns::TANGOCamera* TangoCameraPtr;
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
    void StartAcquisition() override;
    void StopAcquisition() override;
    void ManualTrigger() override;
    void Configure() override;
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
    void StartAcquisition() override;
    void StopAcquisition() override;
    void ManualTrigger() override;
    void Configure() override;
private:
    std::shared_ptr<pco::Camera> PCOCameraPtr;
};

/*--------------------------------------------------------------------------------------------------------------------*/

#include <Spinnaker.h>
#include <SpinGenApi/SpinnakerGenApi.h>
#include <SpinnakerDefs.h>

class FLIRCameraDriver : public CameraDriver {
public:
    explicit FLIRCameraDriver(const TANGOCamera_ns::TANGOCamera* tango_device_ptr);\
    void StartAcquisition() override;
    void StopAcquisition() override;
    void ManualTrigger() override;
    void Configure() override;
private:
    std::unique_ptr<Spinnaker::CameraPtr> SpinnakerCameraPtr;
};
#pragma once

#include <string>
#include <iostream>

#include <pylon/PylonIncludes.h>
#include <pylon/Device.h>
#include <pylon/TypeMappings.h>
#include <pylon/ConfigurationEventHandler.h>
#include <pylon/ImageEventHandler.h>

#include <Spinnaker.h>
#include <SpinGenApi/SpinnakerGenApi.h>

#include <pco.camera/stdafx.h>
#include <pco.camera/camera.h>
#include <pco.camera/cameraexception.h>

namespace TANGOCamera_ns {
    class TANGOCamera;
};

class CameraDriver {
public:
    explicit CameraDriver(std::string  ip_addr);
    virtual void StartAcquisition() = 0;
    virtual void StopAcquisition() = 0;
    virtual void ManualTrigger() = 0;
    virtual void Configure() = 0;
    virtual void SetTangoCameraPtr(const TANGOCamera_ns::TANGOCamera* dev_ptr);
private:
    std::string IPAddress;
    TANGOCamera_ns::TANGOCamera* ParentTangoCameraPtr;
};

class BaslerCameraDriver : public CameraDriver {
public:
    explicit BaslerCameraDriver(const std::string& ip_addr);
    void StartAcquisition() override;
    void StopAcquisition() override;
    void ManualTrigger() override;
    void Configure() override;
private:
    std::unique_ptr<Pylon::CInstantCamera> PylonCameraPtr;
};

class PCOCameraDriver : public CameraDriver {
public:
    explicit PCOCameraDriver(const std::string& ip_addr);
    void StartAcquisition() override;
    void StopAcquisition() override;
    void ManualTrigger() override;
    void Configure() override;
private:
    std::shared_ptr<pco::Camera> PCOCameraPtr;
};

class FLIRCameraDriver : public CameraDriver {
public:
    explicit FLIRCameraDriver(const std::string& ip_addr);
    void StartAcquisition() override;
    void StopAcquisition() override;
    void ManualTrigger() override;
    void Configure() override;
private:
    std::unique_ptr<Spinnaker::CameraPtr> SpinnakerCameraPtr;
};
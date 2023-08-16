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

class CameraDriver {
public:
    explicit CameraDriver(std::string& ip_addr);
    virtual void start_acquisition() = 0;
    virtual void stop_acquisition() = 0;
    virtual void manual_trigger() = 0;
    virtual void configure() = 0;

private:
    std::string ip_address;
    std::unique_ptr<Spinnaker::CameraPtr> spinnaker_camera_ptr;
    std::unique_ptr<Pylon::CInstantCamera> pylon_camera_ptr;
    std::shared_ptr<pco::Camera> pco_camera_ptr;
};

class BaslerCameraDriver : public CameraDriver {
public:
    explicit BaslerCameraDriver(std::string& ip_addr);
    void start_acquisition() override;
    void stop_acquisition() override;
    void manual_trigger() override;
    void configure() override;
};

class PCOCameraDriver : public CameraDriver {
public:
    explicit PCOCameraDriver(std::string& ip_addr);
    void start_acquisition() override;
    void stop_acquisition() override;
    void manual_trigger() override;
    void configure() override;
};

class FLIRCameraDriver : public CameraDriver {
public:
    explicit FLIRCameraDriver(std::string& ip_addr);
    void start_acquisition() override;
    void stop_acquisition() override;
    void manual_trigger() override;
    void configure() override;
};
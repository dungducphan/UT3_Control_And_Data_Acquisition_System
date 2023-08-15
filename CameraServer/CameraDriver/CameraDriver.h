#pragma once

#include <string>

class CameraDriver {
public:
    virtual ~CameraDriver();
    virtual std::string Operation() const = 0;
};

class BaslerCameraDriver : public CameraDriver {
public:
    std::string Operation() const override;
};

class PCOCameraDriver : public CameraDriver {
public:
    std::string Operation() const override;
};

class FLIRCameraDriver : public CameraDriver {
public:
    std::string Operation() const override;
};
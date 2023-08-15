#pragma once

#include "CameraDriver.h"

class CameraDriverCreator {
public:
    virtual ~CameraDriverCreator(){};
    virtual CameraDriver* FactoryMethod() const = 0;
};

class BaslerCameraDriverCreator : public CameraDriverCreator {
public:
    CameraDriver* FactoryMethod() const override {
        return new FLIRCameraDriver();
    }
};

class PCOCameraDriverCreator : public CameraDriverCreator {
public:
    CameraDriver* FactoryMethod() const override {
        return new FLIRCameraDriver();
    }
};

class FLIRCameraDriverCreator : public CameraDriverCreator {
public:
    CameraDriver* FactoryMethod() const override {
        return new FLIRCameraDriver();
    }
};
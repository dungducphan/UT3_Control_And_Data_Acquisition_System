#pragma once

#include <CameraDriver.h>

class CameraDriverFactory {
public:
    static CameraDriver* FactoryMethod(TANGOCamera_ns::TANGOCamera* dev_ptr);
};

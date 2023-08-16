#pragma once

#include "CameraDriver.h"

class CameraDriverCreator {
public:
    static CameraDriver* FactoryMethod(std::string& vendor, std::string& ipaddress) {
        if (vendor == "pco") {
            return new PCOCameraDriver(ipaddress);
        } else if (vendor == "basler") {
            return new BaslerCameraDriver(ipaddress);
        } else if (vendor == "flir") {
            return new FLIRCameraDriver(ipaddress);
        } else {
            return nullptr;
        }
    }
};

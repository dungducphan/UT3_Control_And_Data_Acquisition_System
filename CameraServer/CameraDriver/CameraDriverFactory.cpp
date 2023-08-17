#include <TANGOCamera.h>
#include <CameraDriverFactory.h>

CameraDriver* CameraDriverFactory::FactoryMethod(TANGOCamera_ns::TANGOCamera* dev_ptr) {
    try {
        if (dev_ptr->vendor == "pco") {
            auto driver = new PCOCameraDriver(dev_ptr->ipaddress);
            driver->SetTangoCameraPtr(dev_ptr);
            return driver;
        } else if (dev_ptr->vendor == "basler") {
            auto driver = new BaslerCameraDriver(dev_ptr->ipaddress);
            driver->SetTangoCameraPtr(dev_ptr);
            return driver;
        } else if (dev_ptr->vendor == "flir") {
            auto driver = new FLIRCameraDriver(dev_ptr->ipaddress);
            driver->SetTangoCameraPtr(dev_ptr);
            return driver;
        } else {
            throw std::runtime_error("Unknown camera vendor");
        }
    } catch (std::exception& e) {
        dev_ptr->set_state(Tango::FAULT);
        Tango::Except::throw_exception("CameraDriverFactory::FactoryMethod",
                                       e.what(),
                                       "CameraDriverFactory::FactoryMethod");
    }
}


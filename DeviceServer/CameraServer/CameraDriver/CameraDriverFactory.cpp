#include <TANGOCamera.h>
#include <CameraDriverFactory.h>

CameraDriver* CameraDriverFactory::FactoryMethod(TANGOCamera_ns::TANGOCamera* tango_device_ptr) {
    try {
        auto vendor = tango_device_ptr->vendor;
        /*
        if (vendor == "pco" || vendor == "Pco" || vendor == "PCO") {
            return new PCOCameraDriver(tango_device_ptr);
        } else if (vendor == "basler" || vendor == "Basler" || vendor == "BASLER") {
            return new BaslerCameraDriver(tango_device_ptr);
        } else
        */
        if (vendor == "flir" || vendor == "Flir" || vendor == "FLIR") {
            return new FLIRCameraDriver(tango_device_ptr);
        } else {
            throw std::runtime_error("Unknown camera vendor");
        }
    } catch (std::exception& e) {
        tango_device_ptr->set_state(Tango::FAULT);
        Tango::Except::throw_exception("CameraDriverFactory::FactoryMethod",
                                       e.what(),
                                       "CameraDriverFactory::FactoryMethod");
    }
}


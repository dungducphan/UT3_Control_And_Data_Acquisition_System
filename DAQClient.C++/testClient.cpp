#include <iostream>
#include <tango.h>

int main(int argc, char* argv[]) {
    std::string deviceName = "tango://localhost:10000/UT3/TauBeamline/ElectronSpectrometer_FirstScreen";

    try {
        Tango::DeviceProxy device(deviceName);
        Tango::DevState state;
        device.ping();
    } catch (const Tango::DevFailed& df) {
        std::cerr << "TANGO exception: " << df.errors[0].desc << std::endl;
    }

    return 0;
}

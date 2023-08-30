#pragma once

#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <cerrno>    // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

namespace TimingUnit_ns {
    class TimingUnit;
}

enum DelayLineID_t {
    DelayLine0,
    DelayLine1
};

class TimingUnitDriver {
public:
    explicit TimingUnitDriver(const TimingUnit_ns::TimingUnit* tango_device_ptr);
    ~TimingUnitDriver();
    void CloseUART() const;
    void GetDelayFromHardware();
    void SetDelayToHardware() const;
    void Start();
    void Stop();

private:
    void OpenUART();
    [[nodiscard]] Tango::DevLong GetDelayFromHardware(const DelayLineID_t& delayLineID) const;
    void SetDelayToHardware(const DelayLineID_t& delayLineID) const;
    static void ConvertIntegerBaseNToString(int value, const int &base, char *result);
    void ListenToTriggerEvent();

    std::thread* TimingEventListenerThreadPtr;
    Tango::DevLong DelayFromTriggerToLaserEventInMilliseconds;
    int SerialPort;
    TimingUnit_ns::TimingUnit* TimingUnitDevicePtr;
};

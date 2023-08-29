#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <cerrno>    // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()

class TimingUnitDriver {

private:
    void OpenUART();
    void CloseUART() const;
    void GetDelay();
    void SetDelay();

    int m_SerialPort{};
};

#include <TimingUnit.h>
#include <TimingUnitDriver.h>

unsigned char RETURN_SYMBOL = 13;

TimingUnitDriver::TimingUnitDriver(const TimingUnit_ns::TimingUnit *tango_device_ptr) :
        SerialPort(-1),
        TimingUnitDevicePtr(const_cast<TimingUnit_ns::TimingUnit *>(tango_device_ptr)),
        TimingEventListenerThreadPtr(nullptr) {
    // Hardcoded value for UT3
    DelayFromTriggerToLaserEventInMilliseconds = 100;

    try {
        OpenUART();
        if (SerialPort != -1) TimingUnitDevicePtr->set_state(Tango::ON);
        std::cout << "Found Timing Unit on port: " << TimingUnitDevicePtr->serialPort.c_str() << std::endl;
    } catch (std::exception& e) {
        TimingUnitDevicePtr->set_state(Tango::OFF);
        Tango::Except::throw_exception("TimingUnitDriver::TimingUnitDriver",
                                       e.what(),
                                       "TimingUnitDriver::TimingUnitDriver");
    }
}

void TimingUnitDriver::OpenUART() {
    // Open the serial port connected to the TM4C12x
    // Change device path as needed (currently set to a standard FTDI USB-UART cable type device)
    SerialPort = open(TimingUnitDevicePtr->serialPort.c_str(), O_RDWR);

    // Create new termios struct, we call it 'tty' for convention
    struct termios tty{};

    // Read in existing settings, and handle any error
    if (tcgetattr(SerialPort, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return;
    }

    tty.c_cflag &= ~PARENB;               // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB;               // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag &= ~CSIZE;                // Clear all bits that set the data size
    tty.c_cflag |= CS8;                   // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS;              // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL;        // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;                 // Disable echo
    tty.c_lflag &= ~ECHOE;                // Disable erasure
    tty.c_lflag &= ~ECHONL;               // Disable new-line echo
    tty.c_lflag &= ~ISIG;                 // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF
                          | IXANY);       // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK | BRKINT
                   | PARMRK | ISTRIP
                   | INLCR  | IGNCR
                   | ICRNL);              // Disable any special handling of received bytes
    tty.c_oflag &= ~OPOST;                // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR;                // Prevent conversion of newline to carriage return/line feed
    tty.c_cc[VTIME] = 1;                  // Wait for up to 1s (10 deciseconds), returning as soon as data is received
    tty.c_cc[VMIN] = 100;

    // Set in/out baud rate to be 115200
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Save tty settings, also checking for error
    if (tcsetattr(SerialPort, TCSANOW, &tty) != 0) return;
}

void TimingUnitDriver::CloseUART() const {
    ::close(SerialPort);
    TimingUnitDevicePtr->set_state(Tango::OFF);
}

void TimingUnitDriver::GetDelayFromHardware() {
    if (TimingUnitDevicePtr->get_state() == Tango::RUNNING) return;
    *(TimingUnitDevicePtr->attr_DelayPortB_read) = GetDelayFromHardware(DelayLineID_t::DelayLine0);
    *(TimingUnitDevicePtr->attr_DelayPortD_read) = GetDelayFromHardware(DelayLineID_t::DelayLine1);
}

Tango::DevLong TimingUnitDriver::GetDelayFromHardware(const DelayLineID_t &delayLineID) const {
    char read_buf[5];
    do {
        memset(read_buf, '\0', sizeof(read_buf));
        unsigned char msg[] = {'R', static_cast<unsigned char>('0' + delayLineID), RETURN_SYMBOL};
        write(SerialPort, msg, sizeof(msg));
        read(SerialPort, &read_buf, sizeof(read_buf));
    } while (read_buf[0] == 'E');

    if (0 < atoi(read_buf) && atoi(read_buf) < 100) return (Tango::DevLong) atoi(read_buf);
    else {
#ifdef ENABLE_DEBUG_FEATURES
        std::cout << "Invalid delay value received from hardware: "
                << "'" << read_buf[0] << "'"
                << "'" << read_buf[1] << "'"
                << "'" << read_buf[2] << "'"
                << "'" << read_buf[3] << "'"
                << "'" << read_buf[4] << "'"
                << std::endl;
#endif
        return -1;
    }
}

void TimingUnitDriver::SetDelayToHardware() const {
    SetDelayToHardware(DelayLineID_t::DelayLine0);
    SetDelayToHardware(DelayLineID_t::DelayLine1);
}

void TimingUnitDriver::Start() {
    TimingUnitDevicePtr->set_state(Tango::RUNNING);
    unsigned char msg[] = {'S', '\r'};
    write(SerialPort, msg, sizeof(msg));

    TimingEventListenerThreadPtr = new std::thread(&TimingUnitDriver::ListenToTriggerEvent, this);
}

void TimingUnitDriver::Stop() {
    TimingUnitDevicePtr->set_state(Tango::ON);
    usleep(200);
    unsigned char msg[] = {'P', '\r'};
    write(SerialPort, msg, sizeof(msg));
}

void TimingUnitDriver::ConvertIntegerBaseNToString(int value, const int &base, char *result) {
    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value = value / base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
}

void TimingUnitDriver::SetDelayToHardware(const DelayLineID_t &delayLineID) const {
    int inputDelay = (int) (delayLineID == DelayLineID_t::DelayLine0)
            ? *(TimingUnitDevicePtr->attr_DelayPortB_read)
            : *(TimingUnitDevicePtr->attr_DelayPortD_read);
    if (inputDelay <= 0 || inputDelay >= 100) return;

    char inputDelayStr[6] = {' ', ' ', ' ', ' ', ' ', ' '};
    ConvertIntegerBaseNToString(inputDelay, 10, inputDelayStr);
    unsigned char msg[10] = {'W', static_cast<unsigned char>('0' + delayLineID), ' ', ' ', ' ', ' ', ' ', ' ', ' ', RETURN_SYMBOL};
    for (unsigned int i = 0; i < 6; i++) {
        msg[3 + i] = inputDelayStr[i];
    }
    write(SerialPort, msg, 10);
}

void TimingUnitDriver::ListenToTriggerEvent() {
    char read_buf[1];
    while (TimingUnitDevicePtr->get_state() == Tango::RUNNING) {
        read(SerialPort, &read_buf, sizeof(read_buf));
        if (read_buf[0] == 'E') {
            auto now = std::chrono::system_clock::now();
            *(TimingUnitDevicePtr->attr_ShotID_read) = *(TimingUnitDevicePtr->attr_ShotID_read) + 1;
            *(TimingUnitDevicePtr->attr_LastLaserShotTimestamp_read)
                       = (Tango::DevLong64) std::chrono::duration_cast<std::chrono::milliseconds>(
                    now.time_since_epoch()).count() + DelayFromTriggerToLaserEventInMilliseconds;
            TimingUnitDevicePtr->push_change_event("ShotID", TimingUnitDevicePtr->attr_ShotID_read, 0);
        }
    }
}

TimingUnitDriver::~TimingUnitDriver() {
    CloseUART();
}

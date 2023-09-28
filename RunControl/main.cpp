#include <mainwindow.h>

#include <QApplication>

class TriggerCallback : public Tango::CallBack {
public:
    void push_event(Tango::DataReadyEventData*) override {
        std::cout << "Event received" << std::endl;
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    std::shared_ptr<Tango::DeviceProxy> TimingUnitTest = std::make_shared<Tango::DeviceProxy>("ut3/beamline/timingUnitTest");
    auto callback = new TriggerCallback();
    TimingUnitTest->subscribe_event("Timestamp", Tango::DATA_READY_EVENT, callback);
    std::shared_ptr<Tango::DeviceProxy> TopViewCamera = std::make_shared<Tango::DeviceProxy>("ut3/beamline/topview");
    std::shared_ptr<Tango::DeviceProxy> PointingCamera = std::make_shared<Tango::DeviceProxy>("ut3/beamline/pointing");
    std::shared_ptr<Tango::DeviceProxy> ElectronSpectrometerA = std::make_shared<Tango::DeviceProxy>("ut3/beamline/especA");
    std::shared_ptr<Tango::DeviceProxy> ElectronSpectrometerB = std::make_shared<Tango::DeviceProxy>("ut3/beamline/especB");

    MainWindow w;
    w.setDeviceProxy_TimingUnit(TimingUnitTest);
    w.setDeviceProxy_TopViewCamera(TopViewCamera);
    w.setDeviceProxy_PointingCamera(PointingCamera);
    w.setDeviceProxy_ElectronSpectrometerA(ElectronSpectrometerA);
    w.setDeviceProxy_ElectronSpectrometerB(ElectronSpectrometerB);
    w.show();

    return QApplication::exec();
}

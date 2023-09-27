#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    std::shared_ptr<Tango::DeviceProxy> TimingUnit = std::make_shared<Tango::DeviceProxy>("ut3/beamline/timingUnit");
    std::shared_ptr<Tango::DeviceProxy> TopViewCamera = std::make_shared<Tango::DeviceProxy>("ut3/beamline/topview");
    std::shared_ptr<Tango::DeviceProxy> PointingCamera = std::make_shared<Tango::DeviceProxy>("ut3/beamline/pointing");
    std::shared_ptr<Tango::DeviceProxy> ElectronSpectrometerA = std::make_shared<Tango::DeviceProxy>("ut3/beamline/especA");
    std::shared_ptr<Tango::DeviceProxy> ElectronSpectrometerB = std::make_shared<Tango::DeviceProxy>("ut3/beamline/especB");

    MainWindow w;
    w.setDeviceProxy_TimingUnit(TimingUnit);
    w.setDeviceProxy_TopViewCamera(TopViewCamera);
    w.setDeviceProxy_PointingCamera(PointingCamera);
    w.setDeviceProxy_ElectronSpectrometerA(ElectronSpectrometerA);
    w.setDeviceProxy_ElectronSpectrometerB(ElectronSpectrometerB);
    w.show();

    return QApplication::exec();
}

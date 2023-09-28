#include <mainwindow.h>
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("TauSystemsInc");
    QCoreApplication::setOrganizationDomain("tausystems.com");
    QCoreApplication::setApplicationName("UT3-Run-Control");

    MainWindow w;
    w.show();

    return QApplication::exec();
}

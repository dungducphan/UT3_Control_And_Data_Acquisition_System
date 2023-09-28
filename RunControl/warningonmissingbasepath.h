#ifndef WARNINGONMISSINGBASEPATH_H
#define WARNINGONMISSINGBASEPATH_H

#include <QDialog>

namespace Ui {
class WarningOnMissingBasePath;
}

class WarningOnMissingBasePath : public QDialog
{
    Q_OBJECT

public:
    explicit WarningOnMissingBasePath(QWidget *parent = nullptr);
    ~WarningOnMissingBasePath();

private:
    Ui::WarningOnMissingBasePath *ui;
};

#endif // WARNINGONMISSINGBASEPATH_H

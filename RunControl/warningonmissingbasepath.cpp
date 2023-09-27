#include "warningonmissingbasepath.h"
#include "ui_warningonmissingbasepath.h"

WarningOnMissingBasePath::WarningOnMissingBasePath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarningOnMissingBasePath)
{
    ui->setupUi(this);
}

WarningOnMissingBasePath::~WarningOnMissingBasePath()
{
    delete ui;
}

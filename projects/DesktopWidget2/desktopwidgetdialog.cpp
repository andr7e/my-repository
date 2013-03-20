#include "desktopwidgetdialog.h"
#include "ui_desktopwidgetdialog.h"

DesktopWidgetDialog::DesktopWidgetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DesktopWidgetDialog)
{
    ui->setupUi(this);

    ui->spinBox->setRange (24, 300);
}

DesktopWidgetDialog::~DesktopWidgetDialog()
{
    delete ui;
}

void DesktopWidgetDialog::setInfo (const QVariantHash &info)
{
    int size = info["icon_size"].toInt ();

    ui->spinBox->setValue (size);
}

QVariantHash DesktopWidgetDialog::getInfo ()
{
    QVariantHash info;

    info["icon_size"] = ui->spinBox->value ();

    return info;
}

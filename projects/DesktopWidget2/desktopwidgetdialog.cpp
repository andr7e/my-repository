#include "desktopwidgetdialog.h"
#include "ui_desktopwidgetdialog.h"

#include <QStringListModel>
#include <QDebug>
#include "desktopwidget.h"

DesktopWidgetDialog::DesktopWidgetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DesktopWidgetDialog)
{
    ui->setupUi(this);

    ui->spinBox->setRange (24, 300);

    model_ = new QStringListModel();
}

DesktopWidgetDialog::~DesktopWidgetDialog()
{
    delete model_;

    delete ui;
}

void DesktopWidgetDialog::setInfo (const QVariantHash &info)
{
    int size = DesktopWidget::getIconSizeFromHash (info);
    int direction = DesktopWidget::getDirectionFromHash (info);

    ui->spinBox->setValue (size);

    ui->comboBox->addItem (tr("Horizontal"));
    ui->comboBox->addItem (tr("Vertical"));

    ui->comboBox->setCurrentIndex (direction);

    QStringList items = DesktopWidget::getItemsFromHash (info);

    model_->setStringList (items);

    ui->listView->setModel(model_);
}

QVariantHash DesktopWidgetDialog::getInfo ()
{
    QVariantHash info;

    DesktopWidget::setIconSizeToHash (info, ui->spinBox->value ());
    DesktopWidget::setDirectionToHash (info, ui->comboBox->currentIndex());

    DesktopWidget::setItemsToHash (info, model_->stringList());

    return info;
}

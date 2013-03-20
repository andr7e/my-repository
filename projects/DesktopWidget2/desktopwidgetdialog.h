#ifndef DESKTOPWIDGETDIALOG_H
#define DESKTOPWIDGETDIALOG_H

#include <QDialog>
#include <QVariantHash>

namespace Ui {
class DesktopWidgetDialog;
}

class DesktopWidgetDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DesktopWidgetDialog(QWidget *parent = 0);
    ~DesktopWidgetDialog();

    void setInfo (const QVariantHash &info);
    QVariantHash getInfo ();
    
private:
    Ui::DesktopWidgetDialog *ui;
};

#endif // DESKTOPWIDGETDIALOG_H

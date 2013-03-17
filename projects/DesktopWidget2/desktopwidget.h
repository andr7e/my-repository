#ifndef DESKTOPWIDGET_H
#define DESKTOPWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QAction>
#include <QToolBar>

#include "desktopitem.h"

#define MAX_ACTION 128

namespace Ui {
class DesktopWidget;
}


class DesktopWidget : public QWidget
{
    Q_OBJECT

protected:
    virtual void mousePressEvent (QMouseEvent *pe);
    virtual void mouseMoveEvent (QMouseEvent *pe);

    void readSettings ();
    void writeSettings ();

    void setDesktopWidgetFlags ();
    void setDesktopWidget (bool mode);
    void setTransparentBackground (bool mode);

    //events
    void contextMenuEvent(QContextMenuEvent *event);

public:
    explicit DesktopWidget(QWidget *parent = 0);
    ~DesktopWidget();

    void addItem (const QString &fname);
    void removeItems ();

    void createView ();
    void reloadIconBar ();

    void executeApplication (const QString &path);

public slots:
    void executeApplicationSlot (QAction *action);

    void editSlot ();
    void applySlot ();
    
private:
    bool desktopMode_;
    QPoint pos_;
    QProcess process_;
    int iconSize_;
    QAction *actions_[MAX_ACTION];
    QToolBar *iconBar_;
    Ui::DesktopWidget *ui;

    QVector<DesktopItem> items;
};

#endif // DESKTOPWIDGET_H

#include "desktopwidget.h"
#include "ui_desktopwidget.h"

#include <QDebug>
#include <QToolBar>
#include <QMouseEvent>
#include <QSettings>
#include <QFile>
#include <QMenu>

#include "desktopwidgetdialog.h"
#include "utils.h"

DesktopWidget::DesktopWidget(QWidget *parent) :
    QWidget(parent), desktopMode_ (true), iconSize_(64),
    ui(new Ui::DesktopWidget)
{
    ui->setupUi(this);

    readSettings ();

    setDesktopWidgetFlags ();

    createView ();
}

void DesktopWidget::addItem (const QString &fname)
{
    DesktopItem desktopItem;
    desktopItem.load (fname);

    items.push_back(desktopItem);
}

void DesktopWidget::removeItems ()
{
    for (int i=0; i < items.size(); i++) items.pop_back();
}

void DesktopWidget::createView ()
{

    /*
    addItem ("/usr/share/applications/gimp.desktop");
    addItem ("/usr/share/applications/qtcreator.desktop");
    */

    //itemPaths_ << "/usr/share/applications/gimp.desktop" << "/usr/share/applications/qtcreator.desktop";

    for (int i=0; i < itemPaths_.size(); i++) addItem (itemPaths_[i].toString());

    iconBar_ = new QToolBar;

    ui->verticalLayout->insertWidget(0, iconBar_);

    connect (iconBar_, SIGNAL(actionTriggered(QAction*)), SLOT(executeApplicationSlot(QAction*)));

    reloadIconBar ();
}

void DesktopWidget::reloadIconBar ()
{
    QSize barSize = QSize (iconSize_, iconSize_);

    iconBar_->clear ();

    iconBar_->setIconSize (barSize);

    for (int i=0 ; i< items.size(); i++){
        actions_[i] = iconBar_->addAction(getResizedIcon (items[i].getIcon(), barSize), items[i].getName());
    }
}

DesktopWidget::~DesktopWidget()
{
    writeSettings ();

    removeItems ();

    delete ui;
}

//////////////////move by all point//////////////////
void DesktopWidget::mousePressEvent (QMouseEvent *pe)
{
    pos_ = pe->pos();
}

void DesktopWidget::mouseMoveEvent (QMouseEvent *pe)
{
    move (pe->globalPos() - pos_);
}

//////////////settings////////////////////

#define KEY_ICON_SIZE_STRING "/settings/icon-size"

#define KEY_ITEMS_LIST_STRING "/settings/items-list"

void DesktopWidget::readSettings ()
{
    //qDebug () << Q_FUNC_INFO;

    QPoint pos (0,50);
    QSize size (200,200);

    readWindowSettings (pos, size);

    QSettings s;

    iconSize_ = s.value (KEY_ICON_SIZE_STRING, 64).toInt();

    itemPaths_ = s.value (KEY_ITEMS_LIST_STRING, QVariantList()).toList();

    //qDebug () << size.width ();

    setGeometry (pos.x(), pos.y(), size.width (), size.height ());
}

void DesktopWidget::writeSettings ()
{
    //qDebug () << Q_FUNC_INFO;

    writeWindowSettings (pos (), size ());

    QSettings s;

    s.setValue (KEY_ICON_SIZE_STRING, iconSize_);

    s.setValue (KEY_ITEMS_LIST_STRING, itemPaths_);

    qDebug () << Q_FUNC_INFO << width() << " " << height();
}

void DesktopWidget::setDesktopWidgetFlags ()
{
    setDesktopWidget (desktopMode_);

    setTransparentBackground (desktopMode_);

    Qt::WindowFlags flags = 0;
    //flags |= Qt::FramelessWindowHint;
    //flags |= Qt::Tool;
    flags |= Qt::WindowStaysOnBottomHint;

    setWindowFlags(flags);
}

void DesktopWidget::setDesktopWidget (bool mode)
{
    setAttribute(Qt::WA_X11NetWmWindowTypeDesktop, mode);
}

void DesktopWidget::setTransparentBackground (bool mode)
{
    setAttribute(Qt::WA_TranslucentBackground, mode);
}

void DesktopWidget::editSlot ()
{
    qDebug () << Q_FUNC_INFO << desktopMode_;

    desktopMode_=!desktopMode_;

    setDesktopWidget (desktopMode_);
    //setTransparentBackground (desktopMode_);

    hide ();
    show ();
}

void DesktopWidget::editListSlot ()
{
    DesktopWidgetDialog *dialog = new DesktopWidgetDialog;

    dialog->setWindowTitle (tr("Settings"));

    QVariantHash info;

    info["icon_size"] = iconSize_;

    dialog->setInfo (info);

    if (dialog->exec () == QDialog::Accepted)
    {
        info = dialog->getInfo ();

        iconSize_ = info["icon_size"].toInt ();

        reloadIconBar ();

        qDebug () << Q_FUNC_INFO << desktopMode_;

        setDesktopWidget (desktopMode_);
        hide ();
        show ();
    }

    delete dialog;
}

void DesktopWidget::applySlot ()
{

}

void DesktopWidget::executeApplication (const QString &path)
{
    process_.start (path);
}

void DesktopWidget::executeApplicationSlot (QAction *action)
{
    qDebug () << Q_FUNC_INFO << action->text();

    QString path;

    for (int i=0; i < MAX_ACTION; i++)
    {
        if (actions_[i] == action)
        {
            path = items[i].getPath();
            break;
        }
    }

    if (!path.isEmpty())
    {
        int len = path.length();
        int ind = path.indexOf (" ");
        if (ind != -1) path.remove (ind, len - ind);
        executeApplication (path);
    }
    else
        qDebug () << Q_FUNC_INFO << "No execute path!";
}

void DesktopWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    QAction *editAct = menu.addAction(tr("Edit"));
    connect (editAct, SIGNAL(triggered()), SLOT(editSlot()));

    QAction *editListAct = menu.addAction(tr("Edit List"));
    connect (editListAct, SIGNAL(triggered()), SLOT(editListSlot()));

    QAction *exitAct = menu.addAction(tr("Exit"));
    connect (exitAct, SIGNAL(triggered()), SLOT(close()));

    menu.exec(event->globalPos());
}

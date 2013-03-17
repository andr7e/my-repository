#ifndef QSYSNOTIFY_H
#define QSYSNOTIFY_H

/*
 *Implement QSystemTrayIcon notification API based on libnotify
 *
 *If you have error GDK signals [protected], use #define QT_NO_KEYWORDS previous header declartion
 *and use "Q_SIGNALS" instead "signals".
 */

#include <QtGui>

class QSysNotify : public QObject{
    Q_OBJECT

public:
    QSysNotify(QObject *parent = 0);
    void showMessage(const QString &title, const QString &msg, const QString &icon = 0, int msecs = 10000, const QString &action = 0);
    void showMessage(const QString &title, const QString &msg, const QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information, int msecs = 10000, const QString &action = 0);

public Q_SLOTS:
    void onClick ();

Q_SIGNALS:
    void messageClicked();
};


class Proxy : public QObject{
    Q_OBJECT

private:
    static Proxy *singleton_;

public:
    Proxy(QObject *parent = 0);

    static Proxy* singleton(){ return singleton_;}

    void callback (){ Q_EMIT messageClicked();}

Q_SIGNALS:
    void messageClicked ();
};

#endif // QSYSNOTIFY_H

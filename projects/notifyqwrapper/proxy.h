#ifndef PROXY_H
#define PROXY_H

#include <QObject>

class Proxy : public QObject
{
    Q_OBJECT

private:
    static Proxy *singleton_;

public:
    Proxy(QObject *parent = 0);

    static Proxy* singleton();

    void callback ();

Q_SIGNALS:
    void messageClicked ();
};

#endif // PROXY_H

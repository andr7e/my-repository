#include "proxy.h"

//Proxy
Proxy::Proxy (QObject *parent) : QObject(parent){}

Proxy* Proxy::singleton()
{
    return singleton_;
}

void Proxy::callback ()
{
    Q_EMIT messageClicked();
}

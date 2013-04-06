#ifndef UTILS_H
#define UTILS_H

#include <QStringList>
#include <QHash>

class Utils
{
public:
    Utils();

    static bool ParseInfo (const char *fname, QHash <QString, QString> &map, const QStringList &keys);
};

#endif // UTILS_H

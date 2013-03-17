#include <QIcon>

QIcon getResizedIcon (const QString &fname, const QSize &size)
{
    QIcon icon;
    if (!fname.contains("/"))
    {
        icon = QIcon::fromTheme(fname);
    }
    else
    {
        icon = QIcon (fname);
    }

    if (!icon.isNull()){
        QPixmap pixmap = icon.pixmap (size);
        icon = QIcon (pixmap);
    }

    return icon;
}

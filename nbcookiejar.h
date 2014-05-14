#ifndef NBCOOKIEJAR_H
#define NBCOOKIEJAR_H

#include <QObject>
#include <QNetworkCookieJar>

class NBcookieJar : public QNetworkCookieJar
{
    Q_OBJECT
public:
    explicit NBcookieJar(QObject *parent = 0);

signals:

public slots:
    void loadSettings();
    void loadCookies();
    void saveCookies();
    void clearCookies();

};

#endif // NBCOOKIEJAR_H

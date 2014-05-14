#ifndef NBJSAPIOBJECT_H
#define NBJSAPIOBJECT_H

#include <QObject>
#include <QUrl>
#include <QDebug>

class NBjsApiObject : public QObject
{
    Q_OBJECT
public:
    explicit NBjsApiObject(QObject *parent = 0);

signals:
    void sigNewTab();
    void sigNewAppTab();
    void sigNewTabLink(QUrl url);
    void sigLoadApp(QUrl url);
    void sigNewWindow();
    void sigNewWindowLink(QUrl url);

public slots:
    void emit_sigNewTab();
    void emit_sigNewAppTab();
    void emit_sigNewTabLink(QUrl url);
    void emit_sigLoadApp(QUrl url);
    void emit_sigNewWindow();
    void emit_sigNewWindowLink(QUrl url);

};

#endif // NBJSAPIOBJECT_H

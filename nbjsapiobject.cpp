#include "nbjsapiobject.h"

NBjsApiObject::NBjsApiObject(QObject *parent) :
    QObject(parent)
{

}

void NBjsApiObject::emit_sigNewTab()
{
    qDebug() << "SLOT: emit_sigNewTab() STATUS: Called";
    emit sigNewTab();
    qDebug() << "SLOT: emit_sigNewTab() STATUS: Completed";
}

void NBjsApiObject::emit_sigNewAppTab()
{
    emit sigNewAppTab();
}

void NBjsApiObject::emit_sigNewTabLink(QUrl url)
{
    emit sigNewTabLink(url);
}

void NBjsApiObject::emit_sigLoadApp(QUrl url)
{
    emit sigLoadApp(url);
}

void NBjsApiObject::emit_sigNewWindow()
{
    emit sigNewWindow();
}

void NBjsApiObject::emit_sigNewWindowLink(QUrl url)
{
    emit sigNewWindowLink(url);
}

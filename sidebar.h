#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "mainview.h"
#include <mainview.h>

#include <QtCore>
#include <QPointer>
#include <QObject>
#include <QWidget>
#include <QWebView>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QTextEdit>
#include <QXmlQuery>
#include <QXmlSerializer>
#include <QXmlResultItems>
#include <QFuture>
#include <QtConcurrentRun>


class mainView;

class sideBar : public QWidget
{
    Q_OBJECT
public:
    explicit sideBar(QWidget *parent = 0);

signals:

public slots:
    void initializeSideBar();
    void createAppButton(QString name);

private:
    //QToolButton *viewAllAppsButton;
    QVBoxLayout *appViewLayout;
    QWidget *appPanel;
    QTabWidget *tabs;
    QWebView *appView;
    QToolButton *appButton;

    QObject *mainView_object_pointer;
};

#endif // SIDEBAR_H

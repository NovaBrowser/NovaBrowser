#ifndef APPTAB_H
#define APPTAB_H

#include <QWidget>
#include <QWebView>
#include <QToolButton>
#include <QToolBar>

#include "nbcookiejar.h"
#include "mainview.h"

class mainView;

class appTab : public QWidget
{
    Q_OBJECT
public:
    explicit appTab(QWidget *parent = 0, QString appURL = "http://www.google.com/", NBcookieJar *jar = 0);

public slots:
    void changeNewsButton();
    void revertNewsButton();

protected slots:

private:
    QToolBar *appNavBar;
    QToolButton *newsButton;
    QToolButton *sidebarBUtton;
    QWebView *appMenuWebview;

    QObject *mainView_object_pointer;

};

#endif // APPTAB_H

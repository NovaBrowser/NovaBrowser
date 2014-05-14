#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QToolButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QMdiArea>
#include <QWebFrame>

#include "apptab.h"
#include "browsetab.h"
#include "sidebar.h"
#include "nbcookiejar.h"
#include "qwmessagebox.h"
#include "qwwindow.h"
#include "sec_mainview.h"

extern QString privacyEnabled;

class mainView : public QMainWindow
{
    Q_OBJECT

public:
    mainView(QWidget *parent = 0, QString initialUrl = "file:///Users/nick/Desktop/files for NovaBrowser/startpages/novabrowser_searchpage.html");
    ~mainView(); 

signals:

public slots:
    void newTab();
    void newTabLink(QUrl url);
    void newAppTab();
    void pinTab();
    void enableSecure();
    void showSideBar();
    void hideSideBar();
    void changeSideBarButton();
    void revertSideBarButton();
    void showSideBarRight();
    void hideSideBarRight();
    void launchTabWidgetContextMenu();
    //void openSettingsDialog();
    void showMDIArea();
    void loadApp(QUrl url);
    void snapPage(QUrl url);

protected slots:
    void newWindow();
    void newWindowLink(QUrl url);
    void closeTab(int index);
    void setFullscreen();
    void setMaximized();
    void setWindowed();

private:
    QToolButton *sideBarButton;
    QToolButton *newTabButton;
    QToolButton *newAppTabButton;
    QWidget *rightCornerWidget;
    QTabWidget *tabWidget;
    QWebView *newsView;
    QDockWidget *sidebarRight;
    QDockWidget *sidebar;
    QWidget *mainWidget;
    mainView *new_mainView;
    sec_mainView *secureView;
    QMdiArea *mdiArea;
    NBcookieJar *cookieJar;

    QHBoxLayout *mainLayout;

    QWmessageBox *messageBox;
    QWwindow *qw;


};

#endif // MAINVIEW_H

#ifndef SEC_MAINVIEW_H
#define SEC_MAINVIEW_H

#include <QMainWindow>
#include <QToolButton>
#include <QMessageBox>

#include "sec_apptab.h"
#include "sec_browsetab.h"
//#include "sidebar.h"

extern QString privacyEnabled;

class sec_mainView : public QMainWindow
{
    Q_OBJECT

public:
    sec_mainView(QWidget *parent = 0);
    ~sec_mainView();

signals:

public slots:
    void newTab();
    void newAppTab();
    void enableSecure();

protected slots:
    void newWindow();
    void closeTab(int index);
    void setFullscreen();
    void setMaximized();
    void setWindowed();

private:
    QTabWidget *tabWidget;
    QDockWidget *sidebar;
/*
    QToolButton *newTabButton;
    QToolButton *newAppTabButton;
    QToolButton *menuButton;
    QAction *NBSenderAction;
    QAction *NBReceiverAction;
    QAction *FullscreenAction;
    QAction *MaximizedAction;
    QAction *WindowedAction;
    QAction *NewWindowAction;
    QAction *NewTabAction;
    QAction *AppsAction;
    QAction *BookmarksAction;
    QAction *HistoryAction;
    sec_appTab *Apps;
    QMenu *menuButtonMenu;
    QMenu *toolMenu;
    QMenu *viewMenu;
    QWidget *mainWidget;
    QDialog *receiverDialog;
    QDialog *senderDialog;
*/
    QWidget *mainWidget;
    sec_mainView *secureView;


};


#endif // SEC_MAINVIEW_H

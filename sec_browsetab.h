#ifndef SEC_BROWSETAB_H
#define SEC_BROWSETAB_H

#include <QWidget>
#include <QPointer>
#include <QLineEdit>
#include <QWebView>
#include <QToolBar>
#include <QObject>
#include <QTextEdit>
#include <QKeySequence>
#include <QActionGroup>

#include "sec_mainview.h"
#include <sec_mainview.h>

class sec_mainView;

class sec_browseTab : public QWidget
{
    Q_OBJECT
public:
    explicit sec_browseTab(QWidget *parent = 0);

    QWebView *webView;

signals:

protected slots:
    //void makeSearchURL();
    void makeSearch();
    void changeText();
    void changeTabText();
    void changeSearchBarColor();
    void showSideBar();
    void openBookmarkDialog();
    void exitBookmarkDialog();
    void addBookmark();
    void goToBookmarkURL();

private:
    //QWebView *webView;
    QToolBar *navBar;
    QLineEdit *SearchBar;
    QToolButton *sidebarButton;
    QToolButton *addTabButton;
    QToolButton *addAppTabButton;
    QToolButton *menuButton;
    QObject *mainView_object_pointer;

    QDialog *addBookmarkDialog;
    QLineEdit *bookmarkName;
    QToolButton *okButton;
    QToolButton *cancelButton;

    QDialog *historyDialog;
    QToolButton *clearHistoryButton;
    QToolButton *doneButton;

    QTextEdit *confTextEdit;
    QToolButton *confirmDeleteButton;
    QToolButton *closeButton;
    QToolButton *clearButton;
    QDialog *confDialog;

    QWidget *SideBar;
    QWebView *WebView;

    QMenu *toolMenu;
    QMenu *viewMenu;
    QMenu *menuButtonMenu;
    QAction *secureAction;
    QAction *FullscreenAction;
    QAction *MaximizedAction;
    QAction *WindowedAction;
    QAction *NewWindowAction;
    QAction *NewTabAction;
    QAction *AppsAction;
    QAction *OpenBookmarkDialogAction;
    //QAction *viewHistoryAction;
    //QAction *clearHistoryAction;
    QMenu *BookmarksMenu;
    //QMenu *HistoryMenu;

    //QAction *historyAction;

    QAction *bookmarkAction;

};


#endif // SEC_BROWSETAB_H

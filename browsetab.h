#ifndef BROWSETAB_H
#define BROWSETAB_H

#include <QWidget>
#include <QPointer>
#include <QLineEdit>
#include <QWebView>
#include <QToolBar>
#include <QObject>
#include <QTextEdit>
#include <QKeySequence>
#include <QActionGroup>

#include "mainview.h"
#include <mainview.h>
#include "nbcookiejar.h"
#include "nbhistory.h"
#include "nbjsapiobject.h"

class mainView;

class browseTab : public QWidget
{
    Q_OBJECT
public:
    explicit browseTab(QWidget *parent = 0, QString url = "file:///Users/nick/Desktop/files for NovaBrowser/startpages/novabrowser_searchpage.html", NBcookieJar *jar = 0);

    QWebView *webView;

signals:

protected slots:
    void makeSearch();
    void loadBar(int progress);
    void download(const QNetworkRequest &request);
    void changeText();
    void changeTabText();
    void changeSearchBarColor();
    void addToHistory();
    void viewAllHistory();
    void closeHistoryDialog();
    void clearHistory();
    void clearHistoryConfirmation();
    void closeHistoryConfirmationDialog();
    void openBookmarkDialog();
    void exitBookmarkDialog();
    void addBookmark();
    void goToBookmarkURL();

private:
    QToolBar *navBar;
    QLineEdit *SearchBar;
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
    QAction *viewHistoryAction;
    QAction *clearHistoryAction;
    QMenu *BookmarksMenu;
    NBhistoryInterface *historyManager;
    NBhistoryMenu *HistoryMenu;

    QAction *bookmarkAction;

    NBjsApiObject *jsApi;

};

#endif // BROWSETAB_H

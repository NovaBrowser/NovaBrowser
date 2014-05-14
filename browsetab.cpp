#include "browsetab.h"
#include "mainview.h"

#include <QtWidgets>

browseTab::browseTab(QWidget *parent, QString url, NBcookieJar *jar) :
    QWidget(parent),
    mainView_object_pointer(parent),
    historyManager()
{
    secureAction = new QAction(tr("New Secure Window"), this);
    connect(secureAction, SIGNAL(triggered()), mainView_object_pointer, SLOT(enableSecure()));

    //create a toolMenu.
    QMenu *toolMenu = new QMenu("Tools");

    //FullscreenAction makes window fullscreen.
    FullscreenAction = new QAction(tr("Fullscreen"), this);
    FullscreenAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    connect(FullscreenAction, SIGNAL(triggered()), mainView_object_pointer, SLOT(setFullscreen()));

    //MaximizedAction makes window expand to fill screen.
    MaximizedAction = new QAction(tr("Maximize"), this);
    connect(MaximizedAction, SIGNAL(triggered()), mainView_object_pointer, SLOT(setMaximized()));

    //WindowedAction makes window normal sized.
    WindowedAction = new QAction(tr("Window"), this);
    connect(WindowedAction, SIGNAL(triggered()), mainView_object_pointer, SLOT(setWindowed()));

    //viewMenu contains: FullscreenAction, MaximizedAction, WindowedAction.
    QMenu *viewMenu = new QMenu("View");
    viewMenu->addAction(FullscreenAction);
    viewMenu->addAction(MaximizedAction);
    viewMenu->addAction(WindowedAction);

    //NewWindowAction creates a new window.
    NewWindowAction = new QAction(tr("New Window"), this);
    connect(NewWindowAction, SIGNAL(triggered()), mainView_object_pointer, SLOT(newWindow()));

    //NewTabAction creates a new tab.
    NewTabAction = new QAction(tr("New Tab"), this);
    connect(NewTabAction, SIGNAL(triggered()), mainView_object_pointer, SLOT(newTab()));

    //AppsAction creates a new app tab.
    AppsAction = new QAction(tr("Apps"), this);
    connect(AppsAction, SIGNAL(triggered()), mainView_object_pointer, SLOT(newAppTab()));

    OpenBookmarkDialogAction = new QAction(tr("Add Bookmark"), this);
    connect(OpenBookmarkDialogAction, SIGNAL(triggered()), SLOT(openBookmarkDialog()));

    BookmarksMenu = new QMenu(tr("Bookmarks"));
    BookmarksMenu->addAction(OpenBookmarkDialogAction);
    BookmarksMenu->addSeparator();

    viewHistoryAction = new QAction(tr("View All History"), this);
    connect(viewHistoryAction, SIGNAL(triggered()), SLOT(viewAllHistory()));

    clearHistoryAction = new QAction(tr("Clear History"), this);
    connect(clearHistoryAction, SIGNAL(triggered()), SLOT(clearHistory()));

    //HistoryMenu = new QMenu(tr("History"));
    HistoryMenu = new NBhistoryMenu(this, historyManager);
    HistoryMenu->setTitle("History");
    HistoryMenu->addAction(viewHistoryAction);
    HistoryMenu->addAction(clearHistoryAction);
    HistoryMenu->addSeparator();
    HistoryMenu->setStyleSheet(
                "max-width:400px;"
                );

    //menuButtonMenu contains the above QActions, and QMenus.
    QMenu *menuButtonMenu = new QMenu("Menu");
    menuButtonMenu->addAction(NewWindowAction);
    menuButtonMenu->addAction(NewTabAction);
    menuButtonMenu->addAction(AppsAction);
    menuButtonMenu->addAction(secureAction);
    menuButtonMenu->addSeparator();
    menuButtonMenu->addMenu(BookmarksMenu);
    menuButtonMenu->addMenu(HistoryMenu);
    menuButtonMenu->addMenu(viewMenu);
    menuButtonMenu->addMenu(toolMenu);

    //menuButton contains menuButtonMenu.
    menuButton = new QToolButton;
    menuButton->setText("|||");
    menuButton->setPopupMode(QToolButton::InstantPopup);
    menuButton->setMenu(menuButtonMenu);
    menuButton->setStyleSheet(
                "font-size:120%;"
                "color:black;"
                );

    //QString url = "http://www.google.com";
    //QString newTabUrl = "file:///Users/nick/Desktop/novabrowser_searchpage.html";

    QWebSettings *settings = QWebSettings::globalSettings();
    settings->setAttribute (QWebSettings::PluginsEnabled, true);

    //creates new QWebView.
    webView = new QWebView;
    webView->load(url);
    webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    webView->page()->networkAccessManager()->setCookieJar(jar);
    webView->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    webView->pageAction(QWebPage::OpenLinkInNewWindow);
    webView->setStyleSheet(
                    "margin:0px;"
                    "margin-bottom:0px;"
                    "background-color: white;"
                    );
    //webView->pageAction(QWebPage::downloadRequested(QNetworkRequest));
    connect(webView->page(), SIGNAL(downloadRequested(QNetworkRequest)), SLOT(download(const QNetworkRequest&)));
    connect(webView, SIGNAL(loadFinished(bool)), SLOT(changeText()));
    connect(webView, SIGNAL(loadProgress(int)), SLOT(loadBar(int)));
    connect(webView, SIGNAL(loadFinished(bool)), SLOT(changeTabText()));
    connect(webView, SIGNAL(loadFinished(bool)), SLOT(changeSearchBarColor()));
    connect(webView, SIGNAL(loadFinished(bool)), SLOT(addToHistory()));
    connect(webView->pageAction(QWebPage::OpenLinkInNewWindow), SIGNAL(triggered()), mainView_object_pointer, SLOT(newWindow()));

    //creates SearchBar for URLs and searches.
    SearchBar = new QLineEdit(this);
    SearchBar->setPlaceholderText("Search");
    SearchBar->setStyleSheet(
                "background-color:white;"
                "color:black;"
                "QLineEdit {border-top-left-radius:10px;}"
                "QLineEdit {border-bottom-right-radius:10px;}"
                "QLineEdit {border:2px solid #FF9900;}"
                "border-bottom:2px solid #FF9900;"
                "margin:0px;"
                "margin-top:0px;"
                "margin-bottom:0px;"
                "margin-right:5px;"
                );
    connect(SearchBar, SIGNAL(returnPressed()), SLOT(makeSearch()));

    //navBar contains all of the above widgets and menus.
    QToolBar *navBar = new QToolBar;
    navBar->setStyleSheet(
                "height:20px;"
                "margin:0px;"
                "margin-top:0px;"
                //"border-bottom:2px solid #FF9900;"
                //"background-color: white;"
                //"border-left:1px solid black;"
                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 white, stop:0.3 white, stop:1 #DADADA);"
                );
    navBar->addAction(webView->pageAction(QWebPage::Back));
    navBar->addAction(webView->pageAction(QWebPage::Forward));
    navBar->addAction(webView->pageAction(QWebPage::Reload));
    navBar->addAction(webView->pageAction(QWebPage::Stop));
    navBar->addWidget(SearchBar);
    navBar->addWidget(menuButton);

    //creates a layout for the browseTab.
    QVBoxLayout *browseTabLayout = new QVBoxLayout;
    browseTabLayout->setMargin(0);
    browseTabLayout->setSpacing(0);
    browseTabLayout->setContentsMargins(0,0,0,0);
    browseTabLayout->addWidget(navBar);
    browseTabLayout->addWidget(webView);
    setLayout(browseTabLayout);

    jsApi = new NBjsApiObject;
    QWebFrame *frame = webView->page()->mainFrame();
    frame->addToJavaScriptWindowObject("jsApi", jsApi);
    connect(jsApi, SIGNAL(sigNewTab()), mainView_object_pointer, SLOT(newTab()));
}

//browseTab-- SLOTS

void browseTab::download(const QNetworkRequest &request)
{

}

//changes text in SearchBar to the web page title.
void browseTab::changeText()
{
    QString title = webView->title();

    QString url = webView->url().toString();

    //setWindowTitle(webView->title());

    if(url == "file:///Users/nick/Desktop/files for NovaBrowser/startpages/novabrowser_searchpage.html")
    {
        SearchBar->setPlaceholderText("Search");
    }
    else
    {
        SearchBar->setText(webView->url().toString());
        setWindowTitle(webView->title());
    }
}

//changes text in tabWidget to the web page title.
void browseTab::changeTabText()
{

}

void browseTab::loadBar(int progress)
{
    /*
    if(progress <= 25)
    {
        SearchBar->setStyleSheet(
                    "border-right:2px solid blue;"
                    );
    }
    else if(progress >= 50 && progress < 75)
    {
        SearchBar->setStyleSheet(
                    "border-right:2px solid blue;"
                    "border-bottom:2px solid blue;"
                    );
    }
    else if(progress >= 75 && progress < 100)
    {
        SearchBar->setStyleSheet(
                    "border-right:2px solid blue;"
                    "border-bottom:2px solid blue;"
                    "border-left:2px solid blue;"
                    );
    }
    else if(progress == 100)
    {
        SearchBar->setStyleSheet(
                    "border-right:2px solid blue;"
                    "border-bottom:2px solid blue;"
                    "border-left:2px solid blue;"
                    "border-top:2px solid blue;"
                    );
    }
    else if(progress == 101)
    {
        SearchBar->setStyleSheet(
                    "border-right:2px solid black;"
                    "border-bottom:2px solid black;"
                    "border-left:2px solid black;"
                    "border-top:2px solid black;"
                    );
    }
    */
}

//changes color of SearchBar based on security level.
void browseTab::changeSearchBarColor()
{
    QString input = SearchBar->text();

    if(input.startsWith("https://"))
    {
        SearchBar->setStyleSheet(
                    "color:green;"
                    "QLineEdit {border-top-left-radius:10px;}"
                    "QLineEdit {border-bottom-right-radius:10px;}"
                    "QLineEdit {border:2px solid #FF9900;}"
                    );
    }
    else
    {
        SearchBar->setStyleSheet(
                   "color:black;"
                   "QLineEdit {border-top-left-radius:10px;}"
                   "QLineEdit {border-bottom-right-radius:10px;}"
                   "QLineEdit {border:2px solid #FF9900;}"
                    );
    }
}

//makes a search based on the text in SearchBar.
void browseTab::makeSearch()
{
    QString input = SearchBar->text();
    QUrl query = SearchBar->text();

    QString home = "/home";
    QString google = "/google";
    QString newsfly = "/newsfly";
    QString facebook = "/facebook";
    QString twitter = "/twitter";

    QString searchEngine = "google";

    if(input.startsWith("http://"))
    {
        webView->setUrl(query);
    }

    else if(input.startsWith("/"))
    {        
        if(input == google)
        {
            webView->setUrl(QUrl(QString("http://www.google.com/")));
        }
        else if(input == newsfly)
        {
            webView->setUrl(QUrl(QString("http://www.newsfly.x10.mx/")));
        }
        else if(input == facebook)
        {
            webView->setUrl(QUrl(QString("https://www.facebook.com/")));
        }
        else if(input == twitter)
        {
            webView->setUrl(QUrl(QString("https://twitter.com")));
        }
        else if(input == home)
        {
            webView->setUrl(QUrl(QString("file:///Users/nick/Desktop/novabrowser_searchpage.html")));
        }
     }

    else if(input.startsWith("www."))
    {
        webView->setUrl(QUrl(QString("http://")+(SearchBar->text())));
    }

    else if(input.startsWith("file://"))
    {
        webView->setUrl(query);
    }

    else if(input.startsWith("https://"))
    {
        webView->setUrl(query);
    }

    else
    {
        if(searchEngine == "google")
        {
            webView->setUrl(QUrl(QString("http://www.google.com/search?fs&q=")+(SearchBar->text())));
        }
    }
}

//adds a URL to history, called whenever webView finishes loading.
void browseTab::addToHistory()
{
    QUrl url = webView->url();
    QString title = webView->title();
    historyManager->addHistoryEntry(title, url);

    HistoryMenu->populate();
}

//opens a pop-up window to view all history.
void browseTab::viewAllHistory()
{
    doneButton = new QToolButton;
    doneButton->setText("Okay");
    connect(doneButton, SIGNAL(clicked()), SLOT(closeHistoryDialog()));

    clearHistoryButton = new QToolButton;
    clearHistoryButton->setText("Clear History");
    connect(clearHistoryButton, SIGNAL(clicked()), SLOT(clearHistoryConfirmation()));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(clearHistoryButton);
    hLayout->addWidget(doneButton);
    setLayout(hLayout);

    QWidget *hLayoutWidget = new QWidget;
    hLayoutWidget->setLayout(hLayout);

    QVBoxLayout *vLayout = new QVBoxLayout;
    //vLayout->addWidget(doneButton);
    setLayout(vLayout);

    QWidget *vLayoutWidget = new QWidget;
    vLayoutWidget->setLayout(vLayout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(vLayoutWidget);
    layout->addWidget(hLayoutWidget);
    setLayout(layout);

    historyDialog = new QDialog;
    historyDialog->setStyleSheet(
                "QDialog::min-width:300px;"
                "QDialog::min-height:300px;"
                );
    historyDialog->setLayout(layout);
    historyDialog->show();
}

//opens dialog to confirm history clearing.
void browseTab::clearHistoryConfirmation()
{
    confTextEdit = new QTextEdit;
    confTextEdit->setText("WARNING: Clicking 'Confirm Delete' WILL delete all browser history, it is impossible to recover this data");
    confTextEdit->setReadOnly(true);

    confirmDeleteButton = new QToolButton;
    confirmDeleteButton->setText("Confirm Delete");
    connect(confirmDeleteButton, SIGNAL(clicked()), SLOT(clearHistory()));
    connect(confirmDeleteButton, SIGNAL(clicked()), SLOT(closeHistoryConfirmationDialog()));
    connect(confirmDeleteButton, SIGNAL(clicked()), SLOT(closeHistoryDialog()));

    closeButton = new QToolButton;
    closeButton->setText("Cancel");
    connect(closeButton, SIGNAL(clicked()), SLOT(closeHistoryConfirmationDialog()));

    QHBoxLayout *hConfLayout = new QHBoxLayout;
    hConfLayout->addWidget(closeButton);
    hConfLayout->addWidget(confirmDeleteButton);
    setLayout(hConfLayout);

    QWidget *hConfLayoutWidget = new QWidget;
    hConfLayoutWidget->setLayout(hConfLayout);

    QVBoxLayout *vConfLayout = new QVBoxLayout;
    vConfLayout->addWidget(confTextEdit);
    setLayout(vConfLayout);

    QWidget *vConfLayoutWidget = new QWidget;
    vConfLayoutWidget->setLayout(vConfLayout);

    QVBoxLayout *confLayout = new QVBoxLayout;
    confLayout->addWidget(vConfLayoutWidget);
    confLayout->addWidget(hConfLayoutWidget);
    setLayout(confLayout);

    confDialog = new QDialog;
    confDialog->setLayout(confLayout);
    confDialog->show();
}

//closes the clearHistoryConfirmationDialog.
void browseTab::closeHistoryConfirmationDialog()
{
    confDialog->close();
}

//clears history.
void browseTab::clearHistory()
{

}

//closes the history dialog.
void browseTab::closeHistoryDialog()
{
    historyDialog->close();
}

//opens a dialog to add a bookmark.
void browseTab::openBookmarkDialog()
{
    bookmarkName = new QLineEdit;
    bookmarkName->setText(webView->url().toString());
    connect(bookmarkName, SIGNAL(returnPressed()), SLOT(addBookmark()));
    connect(bookmarkName, SIGNAL(returnPressed()), SLOT(exitBookmarkDialog()));

    okButton = new QToolButton;
    okButton->setText("Okay");
    connect(okButton, SIGNAL(clicked()), SLOT(addBookmark()));
    connect(okButton, SIGNAL(clicked()), SLOT(exitBookmarkDialog()));

    cancelButton = new QToolButton;
    cancelButton->setText("Cancel");
    connect(cancelButton, SIGNAL(clicked()), SLOT(exitBookmarkDialog()));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(cancelButton);
    hLayout->addWidget(okButton);
    setLayout(hLayout);

    QWidget *hLayoutWidget = new QWidget;
    hLayoutWidget->setLayout(hLayout);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(bookmarkName);
    setLayout(vLayout);

    QWidget *vLayoutWidget = new QWidget;
    vLayoutWidget->setLayout(vLayout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(vLayoutWidget);
    layout->addWidget(hLayoutWidget);
    setLayout(layout);

    addBookmarkDialog = new QDialog;
    addBookmarkDialog->setLayout(layout);
    addBookmarkDialog->show();
}

//closes the addBookmarkDialog.
void browseTab::exitBookmarkDialog()
{
    addBookmarkDialog->close();
}

//adds bookmark to bookmarkMenu, called by openBookmarkDialog.
void browseTab::addBookmark()
{
    QString url = webView->url().toString();

    QString name = bookmarkName->text();

    bookmarkAction = new QAction(this);
    bookmarkAction->setText(name);
    bookmarkAction->setData(url);
    BookmarksMenu->addAction(bookmarkAction);
    connect(bookmarkAction, SIGNAL(triggered()), SLOT(goToBookmarkURL()));
}

//sets the webViewURL to the bookmark's URL.
void browseTab::goToBookmarkURL()
{
    QString url = bookmarkAction->data().toString();
    webView->setUrl(QUrl(url));
}


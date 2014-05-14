#include "sec_browsetab.h"
#include "sec_mainview.h"

#include <QtWidgets>

sec_browseTab::sec_browseTab(QWidget *parent) :
    QWidget(parent),
    mainView_object_pointer(parent)
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

    BookmarksMenu = new QMenu(tr("Bookmarks"), this);
    BookmarksMenu->addAction(OpenBookmarkDialogAction);
    BookmarksMenu->addSeparator();

    //menuButtonMenu contains the above QActions, and QMenus.
    QMenu *menuButtonMenu = new QMenu("Menu");
    menuButtonMenu->addAction(NewWindowAction);
    menuButtonMenu->addAction(NewTabAction);
    menuButtonMenu->addAction(AppsAction);
    menuButtonMenu->addAction(secureAction);
    menuButtonMenu->addSeparator();
    menuButtonMenu->addMenu(BookmarksMenu);
    menuButtonMenu->addMenu(viewMenu);
    menuButtonMenu->addMenu(toolMenu);

    sidebarButton = new QToolButton;
    sidebarButton->setText("|]");
    connect(sidebarButton, SIGNAL(clicked()), SLOT(showSideBar()));

    //menuButton contains menuButtonMenu.
    menuButton = new QToolButton;
    menuButton->setText("|||");
    menuButton->setPopupMode(QToolButton::InstantPopup);
    menuButton->setMenu(menuButtonMenu);

    QString url = "http://www.google.com";
    QString newTabUrl = "file:///Users/nick/Desktop/novabrowser_searchpage.html";
    QString secUrl = "file:///Users/nick/Desktop/novabrowser_secure_searchpage.html";

    //creates new QWebView.
    webView = new QWebView;
    webView->load(secUrl);
    webView->setStyleSheet(
                    "margin:0px;"
                    );
    connect(webView, SIGNAL(loadFinished(bool)), SLOT(changeText()));
    connect(webView, SIGNAL(loadFinished(bool)), SLOT(changeTabText()));
    connect(webView, SIGNAL(loadFinished(bool)), SLOT(changeSearchBarColor()));

    //creates SearchBar for URLs and searches.
    SearchBar = new QLineEdit(this);
    SearchBar->setStyleSheet(
                "background-color:white;"
                "color:black;"
                "border:1px solid black;"
                "margin:0px;"
                "margin-top:0px;"
                "margin-bottom:0px;"
                );
    connect(SearchBar, SIGNAL(returnPressed()), SLOT(makeSearch()));

    //button to add new tab.
    addTabButton = new QToolButton;
    addTabButton->setText("+");
    connect(addTabButton, SIGNAL(clicked()), mainView_object_pointer, SLOT(newTab()));

    //button to add new app tab.
    addAppTabButton = new QToolButton;
    addAppTabButton->setText("^");
    connect(addAppTabButton, SIGNAL(clicked()), mainView_object_pointer, SLOT(newAppTab()));

    //navBar contains all of the above widgets and menus.
    QToolBar *navBar = new QToolBar;
    navBar->setStyleSheet(
                "height:20px;"
                "margin:0px;"
                );
    navBar->addAction(webView->pageAction(QWebPage::Back));
    navBar->addAction(webView->pageAction(QWebPage::Forward));
    navBar->addAction(webView->pageAction(QWebPage::Reload));
    navBar->addAction(webView->pageAction(QWebPage::Stop));
    navBar->addWidget(sidebarButton);
    navBar->addWidget(menuButton);
    navBar->addWidget(SearchBar);
    navBar->addWidget(addTabButton);
    navBar->addWidget(addAppTabButton);

    //creates a layout for the browseTab.
    QVBoxLayout *browseTabLayout = new QVBoxLayout;
    browseTabLayout->setMargin(0);
    browseTabLayout->addWidget(navBar);
    browseTabLayout->addWidget(webView);
    setLayout(browseTabLayout);
}

//browseTab-- SLOTS
//toggles side bar.
void sec_browseTab::showSideBar()
{
    WebView = new QWebView;
    WebView->setUrl(QUrl(QString("http://www.google.com/")));

    QVBoxLayout *sidebarLayout = new QVBoxLayout;
    sidebarLayout->addWidget(WebView);

    SideBar = new QWidget;
    SideBar->setLayout(sidebarLayout);
    SideBar->setStyleSheet(
                "width:100px;"
                );

    webView->setStyleSheet(
                "width:500px;"
                "float:right;"
                );
}

//changes text in SearchBar to the web page title.
void sec_browseTab::changeText()
{
    QString title = webView->title();

    QString url = webView->url().toString();

    if(url == "file:///Users/nick/Desktop/novabrowser_searchpage.html")
    {
        SearchBar->setFocus();
        SearchBar->clear();
    }
    else if(url == "file:///Users/nick/Desktop/novabrowser_secure_searchpage.html")
    {
        SearchBar->setFocus();
        SearchBar->clear();
    }
    else
    {
        SearchBar->setText(webView->url().toString());
    }
}

//changes text in tabWidget to the web page title.
void sec_browseTab::changeTabText()
{

}

//changes color of SearchBar based on security level.
void sec_browseTab::changeSearchBarColor()
{
    QString input = SearchBar->text();

    if(input.startsWith("https://"))
    {
        SearchBar->setStyleSheet(
                    "color:green;"
                    );
    }
    else
    {
        SearchBar->setStyleSheet(
                   "color:black;"
                    );
    }
}

//makes a search based on the text in SearchBar.
void sec_browseTab::makeSearch()
{
    QString input = SearchBar->text();
    QUrl query = SearchBar->text();

    QString home = "%home";
    QString google = "%google";
    QString newsfly = "%newsfly";
    QString facebook = "%facebook";
    QString twitter = "%twitter";

    if(input.startsWith("http://"))
    {
        webView->setUrl(query);
    }

    else if(input.startsWith("%"))
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
        webView->setUrl(QUrl(QString("https://www.google.com/search?fs&q=")+(SearchBar->text())));
    }
}

//opens a dialog to add a bookmark.
void sec_browseTab::openBookmarkDialog()
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
void sec_browseTab::exitBookmarkDialog()
{
    addBookmarkDialog->close();
}

//adds bookmark to bookmarkMenu, called by openBookmarkDialog.
void sec_browseTab::addBookmark()
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
void sec_browseTab::goToBookmarkURL()
{
    QString url = bookmarkAction->data().toString();
    webView->setUrl(QUrl(url));
}


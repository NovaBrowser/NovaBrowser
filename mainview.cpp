#include <QtWidgets>

#include "mainview.h"

mainView::mainView(QWidget *parent, QString initialUrl)
    : QMainWindow(parent)
{
    //this->setAttribute( Qt::WA_TranslucentBackground );
    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setStyleSheet(
                //"background-color:#CFCFCF;"
                "background-color: #DADADA;"
                //"background-color: rgba(255,255,255,0.2);"
                //"background-color:black;"
                "QMainWindow::separator { width:0px; height:0px; margin:0px;}"
                );

    cookieJar = new NBcookieJar(this);

    sideBarButton = new QToolButton;
    sideBarButton->setText("|]");
    sideBarButton->setStyleSheet(
                "background-color:white;"
                "height:20px;"
                "width:20px;"
                "margin-bottom:1px;"
                "margin-right:8px;"
                //"border-left:1px solid black;"
                "border-right:2px solid #FF9900;"
                "border-top:2px solid #FF9900;"
                //"border-bottom:2px solid #dd4814;"
                "border-top-right-radius:6px;"
                "font-size:120%;"
                );
    connect(sideBarButton, SIGNAL(clicked()), SLOT(showSideBar()));
    connect(sideBarButton, SIGNAL(clicked()), SLOT(changeSideBarButton()));

    newTabButton = new QToolButton(this);
    newTabButton->setText("+");
    newTabButton->setStyleSheet(
                "background-color:white;"
                "height:20px;"
                "width:20px;"
                "margin-bottom:1px;"
                "margin-right:0px;"
                "border-left:2px solid #FF9900;"
                "border-right:2px solid #FF9900;"
                "border-top:2px solid #FF9900;"
                //"border-bottom:2px solid #dd4814;"
                "border-top-right-radius:6px;"
                "border-top-left-radius:6px;"
                "font-size:120%;"
                );
    connect(newTabButton, SIGNAL(clicked()), SLOT(newTab()));

    newAppTabButton = new QToolButton(this);
    newAppTabButton->setText("^");
    newAppTabButton->setStyleSheet(
                "background-color:white;"
                "height:20px;"
                "width:20px;"
                "margin-bottom:1px;"
                "border-left:2px solid #FF9900;"
                "border-right:2px solid #FF9900;"
                "border-top:2px solid #FF9900;"
                //"border-bottom:2px solid #dd4814;"
                "border-top-right-radius:6px;"
                "border-top-left-radius:6px;"
                "font-size:120%;"
                );
    connect(newAppTabButton, SIGNAL(clicked()), SLOT(newAppTab()));

    QHBoxLayout *rightCornerLayout = new QHBoxLayout;
    rightCornerLayout->setMargin(0);
    rightCornerLayout->addWidget(newTabButton);
    rightCornerLayout->addWidget(newAppTabButton);

    rightCornerWidget = new QWidget(this);
    rightCornerWidget->setStyleSheet(
                //"background-color:white;"
                "border-bottom:0px solid black;"
                );
    rightCornerWidget->setLayout(rightCornerLayout);

    //creates a tabWidget containing a BrowseTab.
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(new browseTab(this, initialUrl, cookieJar), tr("Search"));
    tabWidget->setCornerWidget(sideBarButton, Qt::TopLeftCorner);
    tabWidget->setCornerWidget(rightCornerWidget, Qt::TopRightCorner);
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    tabWidget->setDocumentMode(true);
    tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    tabWidget->setTabShape(QTabWidget::Rounded);
    tabWidget->setTabPosition(QTabWidget::North);
    tabWidget->tabBar()->setExpanding(true);
    tabWidget->setStyleSheet(
                "QTabBar::tab {height: 20px; }"
                "QTabBar::tab {background-color: #DADADA;}"
                "QTabBar::tab::selected, QTabBar::tab:hover {background-color:white; border:0px solid black;}"
                "QTabBar::tab::selected {margin-left:-4px; margin-right:-4px;}"
                "QTabBar::tab::selected {border-right:2px solid #FF9900; border-left:2px solid #FF9900; border-top:2px solid #FF9900; border-top-right-radius:6px; border-top-left-radius:6px;}"
                "QTabBar::tab::!selected {border-right:1px solid black; border-top-right-radius:5px; border-bottom-right-radius:5px;}"
                "QTabBar::tab::first {margin-left:0px; border-top-left-radius:6px; border-left:1px solid black;}"
                "QTabBar::tab::first::selected {margin-left:0px; border-top-left-radius:6px; border-left:2px solid #FF9900;}"
                "QTabBar::tab::only-one {margin-left:0px; border-left:2px solid #FF9900;}"
                "QTabBar::pane {border-top:2px solid #dd4814;}"
                "background-color: #DADADA;"
                "QTabBar::tab::close-button {image: url(:/User/nick/Desktop/Development/QT Dev/NovaBrowser_v7/close.png);}"
                "border-top:2px solid #dd4814;"
                );
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), SLOT(closeTab(int)));
    connect(tabWidget, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(launchTabWidgetContextMenu()));

    //sidebarContents = new sideBar();

    sidebar = new QDockWidget;
    sidebar->setFloating(false);
    sidebar->setAllowedAreas(Qt::RightDockWidgetArea);
    sidebar->setHidden(true);
    sidebar->setFeatures(QDockWidget::NoDockWidgetFeatures);
    sidebar->setStyleSheet(
                "width:150px;"
                "max-width:200px;"
                "QDockWidget {background-color:#1A1A1A;}"
                "border-style:none;"
                //"background-color:#1A1A1A;"
                "QDockWidget {border:0px solid black;}"
                "QMainWindow::separator{margin-right:0px;}"
                );
    sidebar->setWidget(new sideBar(this));

    QString newsUrl = "file:///Users/nick/Desktop/news.html";
    newsView = new QWebView;
    newsView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    /*newsView->setStyleSheet(
                "background-color:rgba(255,255,255,1.0);"
                );*/
    newsView->load(newsUrl);
    connect(newsView, SIGNAL(linkClicked(QUrl)), SLOT(loadApp(QUrl)));

    sidebarRight = new QDockWidget;
    sidebarRight->setFloating(false);
    sidebarRight->setAllowedAreas(Qt::RightDockWidgetArea);
    sidebarRight->setHidden(true);
    sidebarRight->setFeatures(QDockWidget::NoDockWidgetFeatures);
    sidebarRight->setStyleSheet(
                "min-width:430px;"
                "max-width:250px;"
                "QDockWidget {background-color:#1A1A1A;}"
                "border-style:none;"
                //"background-color:#1A1A1A;"
                "QDockWidget {border:0px solid black;}"
                );
    sidebarRight->setWidget(newsView);

    //contains a tabWidget with topRowLayout on top.
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(tabWidget);
    //mainLayout->addWidget(snapDock);
    mainLayout->addWidget(sidebarRight);
    setLayout(mainLayout);

    //contains mainLayout.
    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    setUnifiedTitleAndToolBarOnMac(true);
    setCentralWidget(mainWidget);

    messageBox = new QWmessageBox("Hello, this is a message box!", "OK", "Cancel");
    //messageBox->show();

    qw = new QWwindow(initialUrl);
    //qw->show();
}

mainView::~mainView()
{
}

//mainView--SLOTS
void mainView::launchTabWidgetContextMenu()
{
    QAction *pinTabAction = new QAction(this);
    pinTabAction->setText("Pin Tab");
    connect(pinTabAction, SIGNAL(triggered()), SLOT(pinTab()));

    QAction *closeTabAction = new QAction(this);
    closeTabAction->setText("Close Tab");
    connect(closeTabAction, SIGNAL(triggered()), SLOT(closeTab(int)));

    QAction *insertTabAction = new QAction(this);
    insertTabAction->setText("Insert Tab");

    QAction *disableTabDragAction = new QAction(this);
    disableTabDragAction->setText("Disable Tab Dragging");

    QMenu *tabWidgetContextMenu = new QMenu;
    tabWidgetContextMenu->addAction(pinTabAction);
    tabWidgetContextMenu->addAction(closeTabAction);
    tabWidgetContextMenu->addAction(insertTabAction);
    tabWidgetContextMenu->addAction(disableTabDragAction);
    tabWidgetContextMenu->exec();
}

void mainView::setFullscreen()
{
    this->setWindowState(Qt::WindowFullScreen);
}

void mainView::setMaximized()
{
    this->setWindowState(Qt::WindowMaximized);
}

void mainView::setWindowed()
{
    this->setWindowState(Qt::WindowMinimized);
}

void mainView::newWindow()
{
    new_mainView = new mainView(this, "file:///Users/nick/Desktop/files for NovaBrowser/startpages/novabrowser_searchpage.html");
    new_mainView->show();
}

void mainView::newWindowLink(QUrl url)
{
    QString urlString = url.toString();
    new_mainView = new mainView(this, urlString);
    new_mainView->show();
}

void mainView::newTab()
{
    QString newTabUrl = "file:///Users/nick/Desktop/files for NovaBrowser/startpages/novabrowser_searchpage.html";
    tabWidget->addTab(new browseTab(this, newTabUrl, cookieJar), tr("Search"));
    tabWidget->setFocus();
}

void mainView::newTabLink(QUrl url)
{

}

void mainView::closeTab(int index)
{
    tabWidget->removeTab(index);
}

void mainView::newAppTab()
{
    QString newTabUrl = "file:///Users/nick/Desktop/files for NovaBrowser/startpages/novabrowser_searchpage.html";
    tabWidget->addTab(new appTab(this, newTabUrl, cookieJar), tr("App Menu"));
}

void mainView::pinTab()
{
    tabWidget->setStyleSheet(
                "QTabBar::tab { height: 25px; width: 35px; }"
                "background-color: white;"
                );
    tabWidget->setTabShape(QTabWidget::Rounded);
}

void mainView::enableSecure()
{
    secureView = new sec_mainView;
    secureView->show();
}

void mainView::showSideBar()
{
    sidebar->show(); 
}

void mainView::hideSideBar()
{
    sidebar->hide();
}

void mainView::changeSideBarButton()
{
    sideBarButton->setText("[|");
    connect(sideBarButton, SIGNAL(clicked()), SLOT(hideSideBar()));
    connect(sideBarButton, SIGNAL(clicked()), SLOT(revertSideBarButton()));
}

void mainView::revertSideBarButton()
{
    sideBarButton->setText("|]");
    connect(sideBarButton, SIGNAL(clicked()), SLOT(showSideBar()));
    connect(sideBarButton, SIGNAL(clicked()), SLOT(changeSideBarButton()));
}

void mainView::showSideBarRight()
{
    sidebarRight->show();
}

void mainView::hideSideBarRight()
{
    sidebarRight->hide();
}

void mainView::showMDIArea()
{
    tabWidget->hide();
    mdiArea = new QMdiArea(this);
    /*mdiArea->setStyleSheet(
                "min-width:1300px;"
                "min-height:600px;"
                );*/
    mdiArea->addSubWindow(new mainView(this));
    mdiArea->show();
    mdiArea->setWindowState(Qt::WindowFullScreen);
}

void mainView::loadApp(QUrl url)
{
    /*if(this->tabWidget->currentWidget() == browseTab)
    {
        QString url = "http://www.google.com/";
        browseTab.webView->load(url);
    }*/

    QString urlString = url.toString();
    tabWidget->addTab(new appTab(this, urlString, cookieJar), tr("News"));
}

void mainView::snapPage(QUrl url)
{

}


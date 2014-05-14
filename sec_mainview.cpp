#include <QtWidgets>

#include "sec_mainview.h"

sec_mainView::sec_mainView(QWidget *parent)
    : QMainWindow(parent)
{
    this->setObjectName("myname");
        QString style = "QMainWindow#myname { background-color:rgba(0,0,0,0.8); }";
        this->setStyleSheet(style);

    //creates a tabWidget containing a BrowseTab.
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(new sec_browseTab(this), tr("Search"));
    tabWidget->setTabsClosable(true);
    tabWidget->setTabShape(QTabWidget::Rounded);
    tabWidget->setTabPosition(QTabWidget::North);
    tabWidget->setStyleSheet(
                "QTabBar::tab { height: 25px; }"
                );
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), SLOT(closeTab(int)));

    //sidebarContents = new sideBar();
/*
    sidebar = new QDockWidget;
    sidebar->setFloating(false);
    sidebar->setAllowedAreas(Qt::RightDockWidgetArea);
    sidebar->setStyleSheet(
                "width:100px;"
                "max-width:200px;"
                );
    //sidebar->setWidget(sidebarContents);
    sidebar->setWidget(new sideBar(this));
*/
    //contains a tabWidget with topRowLayout on top.
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    //mainLayout->addWidget(sidebar);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

    //contains mainLayout.
    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    setUnifiedTitleAndToolBarOnMac(true);
    setCentralWidget(mainWidget);
}

sec_mainView::~sec_mainView()
{
}

//mainView--SLOTS
void sec_mainView::setFullscreen()
{
    this->setWindowState(Qt::WindowFullScreen);
}

void sec_mainView::setMaximized()
{
    this->setWindowState(Qt::WindowMaximized);
}

void sec_mainView::setWindowed()
{
    this->setWindowState(Qt::WindowMinimized);
}

void sec_mainView::newWindow()
{

}

void sec_mainView::newTab()
{
    tabWidget->addTab(new sec_browseTab(this), tr("Search"));
}

void sec_mainView::closeTab(int index)
{
    tabWidget->removeTab(index);
}

void sec_mainView::newAppTab()
{
    tabWidget->addTab(new sec_appTab(this), tr("App Menu"));
}

void sec_mainView::enableSecure()
{
    secureView = new sec_mainView;
    secureView->show();
}

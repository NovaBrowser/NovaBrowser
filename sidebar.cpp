#include "sidebar.h"
#include "mainview.h"

#include <QtWidgets>

sideBar::sideBar(QWidget *parent) :
    QWidget(parent),
    mainView_object_pointer(parent)
{
    //initializeSideBar();
/*
    viewAllAppsButton = new QToolButton;
    viewAllAppsButton->setText("All Apps ->");
    connect(viewAllAppsButton, SIGNAL(clicked()), mainView_object_pointer, SLOT(newAppTab()));
*/
    //create all buttons and widgets for appView.
    QString appsUrl = "file:///Users/nick/Desktop/appdock.html";

    appView = new QWebView;
    appView->load(appsUrl);
    appView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    /*settingsView->setStyleSheet(
                "background-color:rgba(255,255,255,1.0);"
                );*/
    connect(appView, SIGNAL(linkClicked(QUrl)), mainView_object_pointer, SLOT(loadApp(QUrl)));

    QVBoxLayout *appViewLayout = new QVBoxLayout;
    appViewLayout->setMargin(0);
    appViewLayout->addWidget(appView);
    setLayout(appViewLayout);

    QWidget *appPanel = new QWidget;
    appPanel->setLayout(appViewLayout);

    //create the tabs and populate them with the above Views.
    tabs = new QTabWidget;
    tabs->setTabPosition(QTabWidget::West);
    tabs->setMovable(true);
    tabs->setDocumentMode(true);
    tabs->setStyleSheet(
                "QTabBar::tab { width: 25px; }"
                "QTabBar::tab:selected {background-color: white;}"
                );
    tabs->addTab(appPanel, tr("Apps"));
    //tabs->addTab(settingsPanel, tr("Settings"));

    //create layout containing tabs.
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(tabs);
    setLayout(layout);

    //initializeSideBar();
}

void sideBar::initializeSideBar()
{
    qlonglong pos1 = 1;
    qlonglong pos2 = 2;
    qlonglong pos3 = 3;
    qlonglong pos4 = 4;
    qlonglong pos5 = 5;
    QString itemName = "name";
    QString itemUrl = "url";

    QXmlQuery query1;
    QString name1;
    QString url1;

    QXmlQuery query2;
    QString name2;
    QString url2;

    QXmlQuery query3;
    QString name3;
    QString url3;

    QXmlQuery query4;
    QString name4;
    QString url4;

    QXmlQuery query5;
    QString name5;
    QString url5;

    QFile nameQuery("/Users/nick/Desktop/files for NovaBrowser/sidebarNameQuery.xq");
    QFile urlQuery("/Users/nick/Desktop/files for NovaBrowser/sidebarUrlQuery.xq");
    //1
    nameQuery.open(QIODevice::ReadWrite);
    urlQuery.open(QIODevice::ReadWrite);
    query1.bindVariable("pos", QVariant(pos1));
    //query1.bindVariable("item", QVariant(itemName));
    query1.setQuery(&nameQuery, QUrl::fromLocalFile(nameQuery.fileName()));
    query1.evaluateTo(&name1);
    query1.setQuery(&urlQuery, QUrl::fromLocalFile(urlQuery.fileName()));
    query1.evaluateTo(&url1);

    createAppButton(name1);
    nameQuery.close();
    urlQuery.close();
    //2
    nameQuery.open(QIODevice::ReadWrite);
    urlQuery.open(QIODevice::ReadWrite);
    query2.bindVariable("pos", QVariant(pos2));
    query2.setQuery(&nameQuery, QUrl::fromLocalFile(nameQuery.fileName()));
    query2.evaluateTo(&name2);
    query2.setQuery(&urlQuery, QUrl::fromLocalFile(urlQuery.fileName()));
    query2.evaluateTo(&url2);

    createAppButton(name2);
    nameQuery.close();
    urlQuery.close();
    //3
    nameQuery.open(QIODevice::ReadWrite);
    urlQuery.open(QIODevice::ReadWrite);
    query3.bindVariable("pos", QVariant(pos3));
    query3.setQuery(&nameQuery, QUrl::fromLocalFile(nameQuery.fileName()));
    query3.evaluateTo(&name3);
    query3.setQuery(&urlQuery, QUrl::fromLocalFile(urlQuery.fileName()));
    query3.evaluateTo(&url3);

    createAppButton(name3);
    nameQuery.close();
    urlQuery.close();
    //4
    nameQuery.open(QIODevice::ReadWrite);
    urlQuery.open(QIODevice::ReadWrite);
    query4.bindVariable("pos", QVariant(pos4));
    query4.setQuery(&nameQuery, QUrl::fromLocalFile(nameQuery.fileName()));
    query4.evaluateTo(&name4);
    query4.setQuery(&urlQuery, QUrl::fromLocalFile(urlQuery.fileName()));
    query4.evaluateTo(&url4);

    createAppButton(name4);
    nameQuery.close();
    urlQuery.close();
    //5
    nameQuery.open(QIODevice::ReadWrite);
    urlQuery.open(QIODevice::ReadWrite);
    query5.bindVariable("pos", QVariant(pos5));
    query5.setQuery(&nameQuery, QUrl::fromLocalFile(nameQuery.fileName()));
    query5.evaluateTo(&name5);
    query5.setQuery(&urlQuery, QUrl::fromLocalFile(urlQuery.fileName()));
    query5.evaluateTo(&url5);

    createAppButton(name5);
    nameQuery.close();
    urlQuery.close();
}

void sideBar::createAppButton(QString name)
{
    appButton = new QToolButton;
    appButton->setText(name);

    appViewLayout->addWidget(appButton);
}


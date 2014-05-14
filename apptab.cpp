#include "apptab.h"
#include "mainview.h"

#include <QtWidgets>

appTab::appTab(QWidget *parent, QString appURL, NBcookieJar *jar) :
    QWidget(parent),
    mainView_object_pointer(parent)
{
    newsButton = new QToolButton;
    newsButton->setText("View News");
    connect(newsButton, SIGNAL(clicked()), mainView_object_pointer, SLOT(showSideBarRight()));
    connect(newsButton, SIGNAL(clicked()), SLOT(changeNewsButton()));

    QToolBar *appNavBar = new QToolBar;
    appNavBar->setStyleSheet(
                "height:15px;"
                "margin:0px;"
                "background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 white, stop:0.6 white, stop:1 #DADADA);"
                );
    appNavBar->addWidget(newsButton);
    appNavBar->show();

    appMenuWebview = new QWebView;
    QString url = "http://www.google.com";
    appMenuWebview->load(appURL);
    appMenuWebview->page()->networkAccessManager()->setCookieJar(jar);

    QVBoxLayout *appMenuLayout = new QVBoxLayout;
    appMenuLayout->setMargin(0);
    appMenuLayout->addWidget(appNavBar);
    appMenuLayout->addWidget(appMenuWebview);
    setLayout(appMenuLayout);
}

void appTab::changeNewsButton()
{
    newsButton->setText("Hide News");
    connect(newsButton, SIGNAL(clicked()), mainView_object_pointer, SLOT(hideSideBarRight()));
    connect(newsButton, SIGNAL(clicked()), SLOT(revertNewsButton()));
}

void appTab::revertNewsButton()
{
    newsButton->setText("View News");
    connect(newsButton, SIGNAL(clicked()), mainView_object_pointer, SLOT(showSideBarRight()));
    connect(newsButton, SIGNAL(clicked()), SLOT(changeNewsButton()));
}

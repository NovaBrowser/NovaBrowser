#include "sec_mainview.h"
#include "sec_apptab.h"

#include <QtWidgets>

sec_appTab::sec_appTab(QWidget *parent) :
    QWidget(parent)
{
    appMenuWebview = new QWebView;
    QString url = "http://www.google.com";
    appMenuWebview->load(url);

    QVBoxLayout *appMenuLayout = new QVBoxLayout;
    appMenuLayout->setMargin(0);
    appMenuLayout->addWidget(appMenuWebview);
    setLayout(appMenuLayout);
}


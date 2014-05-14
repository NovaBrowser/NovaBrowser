#include "mainview.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("fusion"));
    mainView browser;
    browser.show();

    return a.exec();
}

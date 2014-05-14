#ifndef SEC_APPTAB_H
#define SEC_APPTAB_H

#include <QWidget>
#include <QWebView>
#include <QToolButton>

class mainView;

class sec_appTab : public QWidget
{
    Q_OBJECT
public:
    explicit sec_appTab(QWidget *parent = 0);

protected slots:

private:
    QWebView *appMenuWebview;

};


#endif // SEC_APPTAB_H

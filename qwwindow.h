#ifndef QWWINDOW_H
#define QWWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QLayout>
#include <QToolBar>
#include <QToolButton>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

class QWwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit QWwindow(QString url, QWidget *parent = 0);

signals:

public slots:
    void maximizeWindow();
    void minimizeWindow();
    void exitWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QToolBar *titleBar;
    QToolButton *exitButton;
    QToolButton *maximizeButton;
    QToolButton *minimizeButton;
    QWebView *centralWebView;
    QWidget *centralWidget;

    QPoint dragPosition;


};

#endif // QWWINDOW_H

#ifndef QWMESSAGEBOX_H
#define QWMESSAGEBOX_H

#include <QMainWindow>
#include <QMessageBox>
#include <QToolButton>
#include <QLayout>
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class QWmessageBox : public QMainWindow
{
    Q_OBJECT
public:
    explicit QWmessageBox(QString label, QString button1, QString button2, QWidget *parent = 0);
    ~QWmessageBox();

signals:

public slots:
    void quit();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QToolButton *button1;
    QToolButton *button2;
    QLabel *label;
    QWidget *centralWidget;

    QPoint dragPosition;

};

#endif // QWMESSAGEBOX_H

#include "qwmessagebox.h"

QWmessageBox::QWmessageBox(QString labeltext, QString button1text, QString button2text, QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setStyleSheet(
                "background-color:white;"
                );

    button1 = new QToolButton;
    button1->setText(button1text);

    button2 = new QToolButton;
    button2->setText(button2text);
    connect(button2, SIGNAL(clicked()), SLOT(quit()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    setLayout(buttonLayout);

    label = new QLabel;
    label->setText(labeltext);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(label);
    centralLayout->addLayout(buttonLayout);
    setLayout(centralLayout);

    centralWidget = new QWidget;
    centralWidget->setLayout(centralLayout);

    setCentralWidget(centralWidget);

}

QWmessageBox::~QWmessageBox()
{

}

void QWmessageBox::mousePressEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton) {
         dragPosition = event->globalPos() - frameGeometry().topLeft();
         event->accept();
     }
 }

void QWmessageBox::mouseMoveEvent(QMouseEvent *event)
 {
     if (event->buttons() & Qt::LeftButton) {
         move(event->globalPos() - dragPosition);
         event->accept();
     }
 }

void QWmessageBox::quit()
{
    this->destroy(true);
}

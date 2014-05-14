#include "qwwindow.h"

QWwindow::QWwindow(QString url, QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->setAttribute( Qt::WA_TranslucentBackground );
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setStyleSheet(
                "background-color:rgba(218,218,218,1.0);"
                );

    exitButton = new QToolButton;
    exitButton->setText("X");
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitWindow()));

    maximizeButton = new QToolButton;
    maximizeButton->setText("[]");
    connect(maximizeButton, SIGNAL(clicked()), this, SLOT(maximizeWindow()));

    minimizeButton = new QToolButton;
    minimizeButton->setText("_");
    connect(minimizeButton, SIGNAL(clicked()), this, SLOT(minimizeWindow()));

    titleBar = new QToolBar;
    titleBar->setAllowedAreas(Qt::TopToolBarArea);
    /*titleBar->setStyleSheet(
                "background-color: #DADADA;"
                );*/
    titleBar->addWidget(exitButton);
    titleBar->addWidget(maximizeButton);
    titleBar->addWidget(minimizeButton);

    centralWebView = new QWebView;
    centralWebView->load(url);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->setSpacing(0);
    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->addWidget(titleBar);
    centralLayout->addWidget(centralWebView);
    setLayout(centralLayout);

    centralWidget = new QWidget;
    centralWidget->setLayout(centralLayout);

    setCentralWidget(centralWidget);
}

void QWwindow::mousePressEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton) {
         dragPosition = event->globalPos() - frameGeometry().topLeft();
         event->accept();
     }
 }

void QWwindow::mouseMoveEvent(QMouseEvent *event)
 {
     if (event->buttons() & Qt::LeftButton) {
         move(event->globalPos() - dragPosition);
         event->accept();
     }
 }

void QWwindow::exitWindow()
{
    qDebug() << "SLOT: QWwindow::exitWindow() STATUS: Called";
    qDebug() << "SLOT: QWwindow::exitWindow() STATUS: Completed";
}

void QWwindow::maximizeWindow()
{
    qDebug() << "SLOT: QWwindow::maximizeWindow() STATUS: Called";
    //this->setWindowState(Qt::WindowFullScreen);
    this->showFullScreen();
    qDebug() << "SLOT: QWwindow::maximizeWindow() STATUS: Completed";
}

void QWwindow::minimizeWindow()
{
    qDebug() << "SLOT: QWwindow::minimizeWindow() STATUS: Called";
    this->setWindowState(Qt::WindowMinimized);
    qDebug() << "SLOT: QWwindow::minimizeWindow() STATUS: Completed";
}

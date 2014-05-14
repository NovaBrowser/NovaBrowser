#include "nbhistory.h"

NBhistoryInterface::NBhistoryInterface(QObject *parent)
    : QWebHistoryInterface(parent)
{
    //QList<QString> m_historyTitle;
}

void NBhistoryInterface::addHistoryEntry(QString Title, QUrl url)
{
    qDebug() << "SLOT: NBhistoryInterface::addHistoryEntry(QString Title, QUrl url) STATUS: Called";
    QString Url = url.toString();
    addHistoryItem(Title, Url);
    qDebug() << "SLOT: NBhistoryInterface::addHistoryEntry(QString Title, QUrl url) STATUS: Completed";
}

void NBhistoryInterface::addHistoryEntry(const QString & url) override
{
    qDebug() << "SLOT: NBhistoryInterface::addHistoryEntry(const QString & url) override STATUS: Called";
    addHistoryItem("Title", url);
    qDebug() << "SLOT: NBhistoryInterface::addHistoryEntry(const QString & url) override STATUS: Completed";
}

void NBhistoryInterface::addHistoryItem(QString title, QString url)
{
    qDebug() << "SLOT: NBhistoryInterface::addHistoryItem(QString title, QString url) STATUS: Called";
    qDebug() << "m_historyTitle.prepend() Called";
    m_historyTitle.prepend(title);
    qDebug() << "m_historyTitle.prepend() Completed";
    qDebug() << "SLOT: NBhistoryInterface::addHistoryItem(QString title, QString url) STATUS: Completed";
}

void NBhistoryInterface::saveHistory()
{

}

void NBhistoryInterface::clearHistory()
{
    m_historyTitle.clear();
    m_historyUrl.clear();
}

QString NBhistoryInterface::historyTitle(int x)
{
    return m_historyTitle.at(x);
}

QString NBhistoryInterface::historyUrl(int x)
{
    return m_historyUrl.at(x);
}



NBhistoryAction::NBhistoryAction(QWidget *parent)
    : QAction(parent)
{

}



NBhistoryMenu::NBhistoryMenu(QWidget *parent, NBhistoryInterface *interface)
    : QMenu(parent)
{
    m_history = interface;
}

void NBhistoryMenu::populate()
{
    qDebug() << "SLOT: NBhistoryMenu::populate() STATUS: Called";
    this->removeAction(action1);
    this->removeAction(action2);
    this->removeAction(action3);
    this->removeAction(action4);
    this->removeAction(action5);
    this->removeAction(action6);
    this->removeAction(action7);
    this->removeAction(action8);
    this->removeAction(action9);
    this->removeAction(action10);

    action1 = new NBhistoryAction(this);
    qDebug() << "Ln 81 Called";
    //QString text = m_history->historyTitle(0);
    qDebug() << "Ln 81 Complete";
    //action1->setText(text);
    addAction(action1);

    action2 = new NBhistoryAction(this);
    //action2->setHistoryItem(m_history->history(1));
    addAction(action2);

    action3 = new NBhistoryAction(this);
    //action3->setHistoryItem(m_history->history(2));
    addAction(action3);

    action4 = new NBhistoryAction(this);
    //action4->setHistoryItem(m_history->history(3));
    addAction(action4);

    action5 = new NBhistoryAction(this);
    //action5->setHistoryItem(m_history->history(4));
    addAction(action5);

    action6 = new NBhistoryAction(this);
    //action6->setHistoryItem(m_history->history(5));
    addAction(action6);

    action7 = new NBhistoryAction(this);
    //action7->setHistoryItem(m_history->history(6));
    addAction(action7);

    action8 = new NBhistoryAction(this);
    //action8->setHistoryItem(m_history->history(7));
    addAction(action8);

    action9 = new NBhistoryAction(this);
    //action9->setHistoryItem(m_history->history(8));
    addAction(action9);

    action10 = new NBhistoryAction(this);
    //action10->setHistoryItem(m_history->history(9));
    addAction(action10);
    qDebug() << "SLOT: NBhistoryMenu::populate() STATUS: Completed";
}

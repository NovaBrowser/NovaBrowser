#ifndef NBHISTORY_H
#define NBHISTORY_H

#include <QObject>
#include <QWebHistoryInterface>
#include <QDateTime>
#include <QUrl>
#include <QString>
#include <QMenu>
#include <QDebug>


class NBhistoryInterface : public QWebHistoryInterface
{
    Q_OBJECT
public:
    explicit NBhistoryInterface(QObject *parent = 0);
    void addHistoryEntry(QString Title, QUrl url);
    void addHistoryItem(QString title, QString url);
    void saveHistory();
    void clearHistory();
    QString historyTitle(int x);
    QString historyUrl(int x);

    QList<QString> m_historyTitle;
    QList<QString> m_historyUrl;

virtual
    void addHistoryEntry(const QString & url) = 0;
    bool historyContains(const QString &url) const = 0;

signals:

public slots:


private:


};

class NBhistoryAction : public QAction
{
    Q_OBJECT
public:
    explicit NBhistoryAction(QWidget *parent = 0);

private:
};




class NBhistoryMenu : public QMenu
{
    Q_OBJECT
public:
    explicit NBhistoryMenu(QWidget *parent = 0, NBhistoryInterface *interface = 0);
    void populate();

private:
    NBhistoryInterface *m_history;
    NBhistoryAction *action1;
    NBhistoryAction *action2;
    NBhistoryAction *action3;
    NBhistoryAction *action4;
    NBhistoryAction *action5;
    NBhistoryAction *action6;
    NBhistoryAction *action7;
    NBhistoryAction *action8;
    NBhistoryAction *action9;
    NBhistoryAction *action10;
};

#endif // NBHISTORY_H

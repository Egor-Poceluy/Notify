#include "timermanager.h"
#include "notificationmanager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QPushButton>

TimerManager::TimerManager(QTableWidget* tableWidget, QObject *parent)
    : QObject(parent), notificationTable(tableWidget) {}


void TimerManager::addTimer(int hours, int minutes, const QString& message, const QString& soundName)
{
    QTime targetTime(hours, minutes);
    int msecsDifference = QTime::currentTime().msecsTo(targetTime);

    if (msecsDifference < 0)
        msecsDifference += (24 * 60 * 60 * 1000);

    QTimer *timer = new QTimer(this);
    int row = notificationTable->rowCount();

    timer->setProperty("row", row);
    timer->setProperty("message", message);
    timer->setProperty("soundName", soundName);

    connect(timer, &QTimer::timeout, this, [this, timer, message, soundName]() {
        NotificationManager::createNotificationManager().showNotification(message, soundName);
        timers.removeOne(timer);
        timer->deleteLater();

        int row = timer->property("row").toInt();

        if(row >= 0 && row < notificationTable->rowCount()){
            notificationTable->removeRow(row);

            for (int i = row; i < notificationTable->rowCount(); ++i)
                timers.at(i)->setProperty("row", i);
        }
    });

    timer->start(msecsDifference);
    timers.append(timer);

    QString time = QString("%1 : %2")
                       .arg(hours, 2, 10, QLatin1Char('0'))
                       .arg(minutes, 2, 10, QLatin1Char('0'));

    addTimerToTable(time, timer);
}


void TimerManager::addTimerToTable(const QString& time, QTimer* timer)
{
    int row = notificationTable->rowCount();
    notificationTable->insertRow(row);

    QTableWidgetItem *timeItem = new QTableWidgetItem(time);
    notificationTable->setItem(row, 0, timeItem);

    QPushButton *deleteButton = new QPushButton();
    deleteButton->setIcon(QIcon(":/icons/delete.png"));
    notificationTable->setCellWidget(row, 1, deleteButton);

    connect(deleteButton, &QPushButton::clicked, this, [this, timer]() {
        timers.removeOne(timer);
        timer->deleteLater();

        int row = timer->property("row").toInt();

        if(row >= 0 && row < notificationTable->rowCount()){
            notificationTable->removeRow(row);

            for (int i = row; i < notificationTable->rowCount(); ++i)
                timers.at(i)->setProperty("row", i);
        }
    });
}


void TimerManager::saveTimers()
{
    QJsonArray notificationArray;

    for(int i = 0; i < notificationTable->rowCount(); ++i) {
        QTableWidgetItem *timeItem = notificationTable->item(i, 0);

        QStringList timeParts = timeItem->text().split(" : ");
        int hours = timeParts[0].toInt();
        int minutes = timeParts[1].toInt();

        QTimer *timer = timers.at(i);
        QString message = timer->property("message").toString();
        QString soundName = timer->property("soundName").toString();

        QJsonObject notificationObject;
        notificationObject["hours"] = hours;
        notificationObject["minutes"] = minutes;
        notificationObject["message"] = message;
        notificationObject["soundName"] = soundName;

        notificationArray.append(notificationObject);

        QJsonDocument document(notificationArray);
        QFile file("notification.json");
        if(file.open(QIODevice::WriteOnly)) {
            file.write(document.toJson());
            file.close();
        }
    }
}


void TimerManager::loadTimers() {
    QFile file("notification.json");
    if(file.open(QIODevice::ReadOnly)) {
        QJsonDocument document = QJsonDocument::fromJson(file.readAll());
        QJsonArray notificationArray = document.array();

        for(const auto& i : notificationArray) {
            QJsonObject notificationObject = i.toObject();

            int hours = notificationObject["hours"].toInt();
            int minutes = notificationObject["minutes"].toInt();
            QString message = notificationObject["message"].toString();
            QString soundName = notificationObject["soundName"].toString();

            addTimer(hours, minutes, message, soundName);
        }
        file.close();
    }
}

#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include "notification.h"

#include <QList>
#include <QObject>

class NotificationManager : public QObject
{
    Q_OBJECT

public:
    static NotificationManager& createNotificationManager();
    void showNotification(const QString& message, const QString& soundName);
    void updateNotificationPosition();

    QList<Notification*> currentNotifications;

private:
    NotificationManager(QObject* parent = nullptr);
    ~NotificationManager() = default;

    QPropertyAnimation animation;
};

#endif // NOTIFICATIONMANAGER_H

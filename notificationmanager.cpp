#include "notificationmanager.h"

NotificationManager& NotificationManager::createNotificationManager()
{
    static NotificationManager singletonManager;
    return singletonManager;
}


NotificationManager::NotificationManager(QObject* parent)
    : QObject(parent) {}


void NotificationManager::showNotification(const QString& message, const QString& soundName) {
    Notification *notification = new Notification();
    notification->setMessage(message);
    notification->setSound(soundName);
    notification->show();

    currentNotifications.append(notification);
    updateNotificationPosition();

    connect(notification, &Notification::closed, this, [this, notification]() {
        currentNotifications.removeOne(notification);
        notification->deleteLater();
        updateNotificationPosition();
    });
}


void NotificationManager::updateNotificationPosition()
{
    int x = QApplication::desktop()->availableGeometry().width() - 320 - 36;
    int y = QApplication::desktop()->availableGeometry().height() - 100 - 36;

    for(int i = 0; i < currentNotifications.size(); ++i) {
        int offset = i * (currentNotifications[i]->height() + 18);
        currentNotifications[i]->move(x, y - offset);
    }
}

#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <QObject>
#include <QTimer>
#include <QTableWidget>

class TimerManager : public QObject
{
    Q_OBJECT
public:
    explicit TimerManager(QTableWidget* tableWidget, QObject *parent = nullptr);

    void addTimer(int hours, int minutes, const QString& message, const QString& soundName);
    void saveTimers();
    void loadTimers();

private:
    QTableWidget* notificationTable;
    QList<QTimer*> timers;

    void addTimerToTable(const QString& time, QTimer* timer);
};

#endif // TIMERMANAGER_H

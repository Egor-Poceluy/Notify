#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "timermanager.h"
#include "settingswindow.h"
#include "createwindow.h"

#include <QMainWindow>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void notify(QTimer* timer, const QString& msg = "Это пустое уведомление");
    void addTimerToTable(const QString& time, QTimer* timer);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void settingButton_clicked();
    void createNotificationButton_clicked();
    void handleCreateNotification(int hours, int minutes, const QString& message, const QString& soundName);

signals:
    void createNotification(int hours, int minutes, const QString& message, const QString& soundName);

private:
    Ui::MainWindow *ui;
    void setupTrayIcon();

    QTableWidget *currentTimers;
    TimerManager *timeManager;
    Settings *settingsWindow = nullptr;
    CreateWindow *createWindow = nullptr;
    QList<QTimer*> timers;
    QSystemTrayIcon *trayIcon;
};
#endif // MAINWINDOW_H

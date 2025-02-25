#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTime>
#include <QList>
#include <QTableWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

class Notification;
class Settings;
class CreateWindow;

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

private:
    Ui::MainWindow *ui;
    void notify(const QString& message, const QString& soundName);
    void setupTrayIcon();

    Notification *notification;
    Settings *settingsWindow = nullptr;
    CreateWindow *createWindow = nullptr;
    QList<QTimer*> timers;
    QTableWidget *currentTimers;
    QSystemTrayIcon *trayIcon;
};
#endif // MAINWINDOW_H

#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "notification.h"
#include "settingswindow.h"
#include "createwindow.h"

#include <QMainWindow>
#include <QTime>
#include <QList>
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

private slots:
    void settingButton_clicked();
    void createNotificationButton_clicked();
    void handleCreateNotification(int hours, int minutes, const QString& message, const QString& soundName);

private:
    Ui::MainWindow *ui;
    void notify(const QString& message, const QString& soundName);

    Notification *notification;
    Settings *settingsWindow = nullptr;
    CreateWindow *createWindow = nullptr;
    QList<QTimer*> timers;
};
#endif // MAINWINDOW_H

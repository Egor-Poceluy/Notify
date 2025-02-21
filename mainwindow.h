#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "notification.h"

#include <QMainWindow>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QTime>

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

public slots:
    void notifyButton_clicked();
    void notify();

private:
    Ui::MainWindow *ui;
    Notification *notification;

    QLineEdit *hours;
    QLineEdit *minutes;
    QTimer *timer;
};
#endif // MAINWINDOW_H

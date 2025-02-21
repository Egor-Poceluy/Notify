#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "notification.h"

#include <QMainWindow>

#include <QPushButton>
#include <QHBoxLayout>
#include <QTextEdit>

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
    void testNotify();

private:
    Ui::MainWindow *ui;
    Notification *notification;
};
#endif // MAINWINDOW_H

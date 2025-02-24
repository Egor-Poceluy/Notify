#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "notification.h"

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

public slots:
    void testNotify();

private:
    Ui::Settings *ui;
    Notification *notification;
};

#endif // SETTINGSWINDOW_H

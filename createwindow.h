#pragma once
#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QRegExpValidator>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class CreateWindow;
}

class CreateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateWindow(QWidget *parent = nullptr);
    ~CreateWindow();

signals:
    void createNotification(int hours, int minutes, const QString& message, const QString& soundName);

private:
    Ui::CreateWindow *ui;

    QLineEdit *hours;
    QLineEdit *minutes;
    QLineEdit *msg;
    QString soundName;
};

#endif // CREATEWINDOW_H

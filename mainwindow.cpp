#include "mainwindow.h"
#include "notification.h"
#include "settingswindow.h"
#include "createwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), notification(new Notification()), currentTimers(new QTableWidget())
{
    ui->setupUi(this);
    setFixedSize(350, 400);
    setWindowTitle("Notify");

    QPushButton *settingsButton = new QPushButton(this);
    settingsButton->setIcon(QIcon(":/icons/settings.png"));
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::settingButton_clicked);

    //QSpacerItem *spacer = new QSpacerItem(10, 10, QSizePolicy::MinimumExpanding);

    QPushButton *createNotificationButton = new QPushButton(this);
    createNotificationButton->setIcon(QIcon(":/icons/notify.png"));
    connect(createNotificationButton, &QPushButton::clicked, this, &MainWindow::createNotificationButton_clicked);

    currentTimers->setColumnCount(2);
    currentTimers->setHorizontalHeaderLabels({"Время", "Удалить"});
    currentTimers->setColumnWidth(0, 150);
    currentTimers->setColumnWidth(1, 150);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(createNotificationButton);
    //btnLayout->addSpacerItem(spacer);
    btnLayout->addWidget(settingsButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(currentTimers);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete notification;
}


void MainWindow::createNotificationButton_clicked()
{
    if (createWindow != nullptr) {
        createWindow->raise();
        createWindow->activateWindow();
        return;
    }

    createWindow = new CreateWindow(this);
    connect(createWindow, &CreateWindow::createNotification, this, &MainWindow::handleCreateNotification);
    connect(createWindow, &QWidget::destroyed, this, [this]() { createWindow = nullptr; });

    createWindow->show();
}


void MainWindow::settingButton_clicked()
{
    if (settingsWindow != nullptr) {
        settingsWindow->raise();
        settingsWindow->activateWindow();
        return;
    }

    settingsWindow = new Settings(this);
    connect(settingsWindow, &QWidget::destroyed, this, [this]() { settingsWindow = nullptr; });

    settingsWindow->show();
}


void MainWindow::notify(const QString& message, const QString& soundName)
{
    notification->setMessage(message);
    notification->setSound(soundName);
    notification->show();
}


void MainWindow::handleCreateNotification(int hours, int minutes, const QString& message, const QString& soundName)
{
    QTime targetTime(hours, minutes);
    int msecsDifference = QTime::currentTime().msecsTo(targetTime);

    if (msecsDifference < 0)
        msecsDifference += (24 * 60 * 60 * 1000);

    QTimer *timer = new QTimer(this);
    int row = currentTimers->rowCount();
    timer->setProperty("row", row);

    connect(timer, &QTimer::timeout, this, [this, timer, message, soundName]() {
        notify(message, soundName);
        timers.removeOne(timer);
        timer->deleteLater();

        int row = timer->property("row").toInt();

        if(row >= 0 && row < currentTimers->rowCount()){
            currentTimers->removeRow(row);

            for (int i = row; i < currentTimers->rowCount(); ++i)
                timers.at(i)->setProperty("row", i);
        }
    });

    timer->start(msecsDifference);
    timers.append(timer);

    QString time = QString("%1 : %2")
                       .arg(hours, 2, 10, QLatin1Char('0'))
                       .arg(minutes, 2, 10, QLatin1Char('0'));

    addTimerToTable(time, timer);
}


void MainWindow::addTimerToTable(const QString& time, QTimer* timer)
{
    int row = currentTimers->rowCount();
    currentTimers->insertRow(row);

    QTableWidgetItem *timeItem = new QTableWidgetItem(time);
    currentTimers->setItem(row, 0, timeItem);

    QPushButton *deleteButton = new QPushButton();
    deleteButton->setIcon(QIcon(":/icons/delete.png"));
    currentTimers->setCellWidget(row, 1, deleteButton);

    connect(deleteButton, &QPushButton::clicked, this, [this, timer]() {
        timers.removeOne(timer);
        timer->deleteLater();

        int row = timer->property("row").toInt();

        if(row >= 0 && row < currentTimers->rowCount()){
            currentTimers->removeRow(row);

            for (int i = row; i < currentTimers->rowCount(); ++i)
                timers.at(i)->setProperty("row", i);
        }
    });
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), notification(new Notification())
{
    ui->setupUi(this);
    setFixedSize(350, 400);
    setWindowTitle("Notify");

    QPushButton *settingsButton = new QPushButton(this);
    settingsButton->setIcon(QIcon(":/icons/settings.png"));
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::settingButton_clicked);

    QPushButton *createNotificationButton = new QPushButton("+ Создать уведомление", this);
    connect(createNotificationButton, &QPushButton::clicked, this, &MainWindow::createNotificationButton_clicked);


    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(createNotificationButton);
    btnLayout->addWidget(settingsButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(btnLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}


MainWindow::~MainWindow()
{
    delete notification;
    delete ui;
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
    connect(timer, &QTimer::timeout, this, [this, timer, message, soundName]() {
        notify(message, soundName);
        timers.removeOne(timer);
        timer->deleteLater();
    });

    timer->start(msecsDifference);
    timers.append(timer);
}

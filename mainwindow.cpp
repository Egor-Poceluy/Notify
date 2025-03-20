#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), currentTimers(new QTableWidget(this)), timeManager(new TimerManager(currentTimers, this)), trayIcon(new QSystemTrayIcon(this))
{
    ui->setupUi(this);
    setFixedSize(350, 400);
    setWindowTitle("Notify");

    QPushButton *settingsButton = new QPushButton(this);
    settingsButton->setIcon(QIcon(":/icons/settings.png"));
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::settingButton_clicked);
    setWindowIcon(QIcon(":/icons/app-icon.png"));

    QPushButton *createNotificationButton = new QPushButton(this);
    createNotificationButton->setIcon(QIcon(":/icons/notify.png"));
    connect(createNotificationButton, &QPushButton::clicked, this, &MainWindow::createNotificationButton_clicked);

    currentTimers->setColumnCount(2);
    currentTimers->setHorizontalHeaderLabels({"Время", "Удалить"});
    currentTimers->setColumnWidth(0, 150);
    currentTimers->setColumnWidth(1, 150);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(createNotificationButton);
    btnLayout->addWidget(settingsButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(currentTimers);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    timeManager->loadTimers();
    setupTrayIcon();
    //this->hide();
}


MainWindow::~MainWindow()
{
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


void MainWindow::handleCreateNotification(int hours, int minutes, const QString& message, const QString& soundName)
{
    timeManager->addTimer(hours, minutes, message, soundName);
}


void MainWindow::setupTrayIcon()
{
    trayIcon->setIcon(QIcon(":/icons/app-icon.png"));

    QMenu *trayMenu = new QMenu(this);
    QAction *openAction = new QAction("Открыть", this);
    QAction *quitAction = new QAction("Выйти", this);

    trayMenu->addAction(openAction);
    trayMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayMenu);

    connect(openAction, &QAction::triggered, this, &MainWindow::show);
    connect(quitAction, &QAction::triggered, qApp, [this]() {
        timeManager->saveTimers();
        QApplication::quit();
    });
    trayIcon->show();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    this->hide();
    trayIcon->showMessage("Notify", "Приложение свернуто в трей");
    event->ignore();
}

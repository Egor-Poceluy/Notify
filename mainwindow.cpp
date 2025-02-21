#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , notification(new Notification())
    , hours(new QLineEdit())
    , minutes(new QLineEdit())
{
    ui->setupUi(this);
    setFixedSize(350, 200);

    QRegExpValidator *hourValidator = new QRegExpValidator(QRegExp("^([01]?[0-9]|2[0-3])$"), this);
    QRegExpValidator *minuteValidator = new QRegExpValidator(QRegExp("^([0-5]?[0-9])$"), this);

    hours->setAlignment(Qt::AlignRight);
    hours->setValidator(hourValidator);

    QLabel* colon = new QLabel(":");

    minutes->setAlignment(Qt::AlignLeft);
    minutes->setValidator(minuteValidator);


    QPushButton *notifyButton = new QPushButton("Создать напоминание");
    connect(notifyButton, &QPushButton::clicked, this, &MainWindow::notifyButton_clicked);


    QHBoxLayout *clockLayout = new QHBoxLayout(this);
    clockLayout->addWidget(hours);
    clockLayout->addWidget(colon);
    clockLayout->addWidget(minutes);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(clockLayout);
    mainLayout->addWidget(notifyButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::notifyButton_clicked()
{
    int inputHour = hours->text().toInt();
    int inputMinute = minutes->text().toInt();

    QTime targetTime(inputHour, inputMinute);

    int msecsDifference = QTime::currentTime().msecsTo(targetTime);

    if (msecsDifference < 0)
        msecsDifference += (24 * 60 * 60 * 1000);

    timer = new QTimer(this);
    timer->start(msecsDifference);

    connect(timer, &QTimer::timeout, this, &MainWindow::notify);
}


void MainWindow::notify()
{
    timer->stop();
    notification->setMessage("TEST TEST TEST");
    notification->show();
}

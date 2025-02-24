#include "settingswindow.h"
#include "ui_settingswindow.h"

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings)
    , notification(new Notification())
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Настройки");
    setFixedSize(350, 200);

    QPushButton *testNotificationButton = new QPushButton("test");

    connect(testNotificationButton, &QPushButton::clicked, this, &Settings::testNotify);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(testNotificationButton);
}

Settings::~Settings()
{
    delete ui;
}


void Settings::testNotify()
{
    notification->setMessage("ЭТО ТЕСТОВОЕ СООБЩЕНИЕ!!!");
    notification->show();
}

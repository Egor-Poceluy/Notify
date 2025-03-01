#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "notificationmanager.h"

#include <QPushButton>

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Настройки");
    setFixedSize(350, 200);

    QPushButton *testNotificationButton = new QPushButton("test");

    connect(testNotificationButton, &QPushButton::clicked, this, []{
        NotificationManager::createNotificationManager().showNotification("ТЕСТОВОЕ СООБЩЕНИЕ", "default");
    });

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(testNotificationButton);
}

Settings::~Settings()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , notification(new Notification())
{
    ui->setupUi(this);
    setFixedSize(350, 200);

    QPushButton *btn = new QPushButton("Тест");

    QTextEdit *msg = new QTextEdit();
    msg->setPlaceholderText("Введите ваше сообщение");

    connect(btn, &QPushButton::clicked, this, [this, msg]() {
        notification->setMessage(msg->toPlainText());
        notification->show();
    });

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(btn);
    layout->addWidget(msg);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testNotify()
{

}

#include "createwindow.h"
#include "ui_createwindow.h"

CreateWindow::CreateWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateWindow), hours(new QLineEdit()), minutes(new QLineEdit()), msg(new QLineEdit())
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Новое уведомление");
    setFixedSize(350, 400);


    QRegExpValidator *hourValidator = new QRegExpValidator(QRegExp("^([01]?[0-9]|2[0-3])$"), this);
    hours->setAlignment(Qt::AlignRight);
    hours->setValidator(hourValidator);

    QLabel *colon = new QLabel(":");

    QRegExpValidator *minuteValidator = new QRegExpValidator(QRegExp("^([0-5]?[0-9])$"), this);
    minutes->setAlignment(Qt::AlignLeft);
    minutes->setValidator(minuteValidator);


    msg->setPlaceholderText("Ваше сообщение...");


    QComboBox *sounds = new QComboBox();
    sounds->addItem("Звук1", "default");
    sounds->addItem("Звук2", "ring");
    soundName = sounds->itemData(sounds->currentIndex()).toString();

    connect(sounds, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this, sounds](int index) {
        soundName = sounds->itemData(sounds->currentIndex()).toString();
    });


    QPushButton *saveNotificationButton = new QPushButton("Создать напоминание", this);
    connect(saveNotificationButton, &QPushButton::clicked, this, [this]() {
        if(!hours->text().isEmpty() && !minutes->text().isEmpty()) {
            int h = hours->text().toInt();
            int m = minutes->text().toInt();
            QString message = msg->text();
            emit createNotification(h, m, message, soundName);
        }
        // вывод в статус бар если пустое время
    });


    QHBoxLayout *clockLayout = new QHBoxLayout();
    clockLayout->addWidget(hours);
    clockLayout->addWidget(colon);
    clockLayout->addWidget(minutes);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(clockLayout);
    mainLayout->addWidget(msg);
    mainLayout->addWidget(sounds);
    mainLayout->addWidget(saveNotificationButton);
}

CreateWindow::~CreateWindow()
{
    delete ui;
}

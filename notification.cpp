#include "notification.h"

Notification::Notification(QWidget *parent)
    : QWidget{parent}, notificationLifeTime(5000), transparency(1.0), progress(1.0), ring(new QSoundEffect(this)), timer(new QTimer())
{
    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::Tool |
                   Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    animation.setTargetObject(this);
    animation.setPropertyName("transparency");

    label.setAlignment(Qt::AlignCenter);
    label.setStyleSheet("color: black;");
    label.setFixedSize(320, 100);

    layout.addWidget(&label);
    setLayout(&layout);

    connect(timer, &QTimer::timeout, this, &Notification::calculateTime);
}


void Notification::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect notifyRect = rect();
    notifyRect.setX(notifyRect.x());
    notifyRect.setY(notifyRect.y());
    notifyRect.setSize(QSize(notifyRect.width(), notifyRect.height()));

    painter.setBrush(QBrush(QColor(255, 255, 255)));
    painter.setPen(Qt::NoPen);
    painter.drawRect(notifyRect);

    QRect progressRect;
    progressRect.setX(notifyRect.x());
    progressRect.setY(notifyRect.y());
    progressRect.setSize(QSize(rect().width() * progress, 4));

    painter.setBrush(QBrush(QColor(0, 122, 255)));
    painter.setPen(Qt::NoPen);
    painter.drawRect(progressRect);
}


void Notification::setMessage(const QString& msg)
{
    label.setText(msg);
    adjustSize();
}


float Notification::getTransparency() const noexcept
{
    return transparency;
}


void Notification::setTransparency(float _transparency)
{
    transparency = _transparency;
    setWindowOpacity(_transparency);
}


void Notification::show()
{
    animation.setDuration(500);
    animation.setStartValue(0);
    animation.setEndValue(1);

    ring->play();
    QWidget::show();

    animation.start();
    timer->start(10);
}


void Notification::hideAnimation()
{
    animation.setDuration(1000);
    animation.setStartValue(1.0);
    animation.setEndValue(0.0);

    connect(&animation, &QAbstractAnimation::finished, this, [this]() {
        if(getTransparency() == 0) {
            QWidget::hide();
            emit closed();
        }
    });

    animation.start();
}


void Notification::calculateTime()
{
    notificationLifeTime -= 10;
    progress = static_cast<float>(notificationLifeTime) / 5000.0f;
    if(notificationLifeTime <= 0) {
        timer->stop();
        hideAnimation();
    }
    update();
}


void Notification::setSound(const QString& path, int volume)
{
    ring->setSource(QUrl("qrc:/sounds/" + path + ".wav"));
    ring->setVolume(volume);
}

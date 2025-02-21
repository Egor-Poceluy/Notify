#include "notification.h"

#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>

Notification::Notification(QWidget *parent)
    : QWidget{parent}, timer(new QTimer())
{
    setWindowFlags(Qt::FramelessWindowHint |
                   Qt::Tool |
                   Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);


    animation.setTargetObject(this);
    animation.setPropertyName("transparency");
    connect(&animation, &QAbstractAnimation::finished, this, [this]() {
        if(getTransparency() == 0) QWidget::hide();
    });


    label.setAlignment(Qt::AlignCenter);
    label.setStyleSheet("color: white");


    layout.addWidget(&label);
    setLayout(&layout);

    connect(timer, &QTimer::timeout, this, &Notification::hideAnimation);
}


void Notification::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect notifyRect;
    notifyRect.setX(rect().x() + 5);
    notifyRect.setY(rect().y() + 5);
    notifyRect.setSize(QSize(rect().width() - 10, rect().height() - 10));

    painter.setBrush(QBrush(QColor(0, 0, 0, 180)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(notifyRect, 10, 10);
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

    setGeometry(QApplication::desktop()->availableGeometry().width() - 36 - width() + QApplication::desktop() -> availableGeometry().x(),
                QApplication::desktop()->availableGeometry().height() - 36 - height() + QApplication::desktop() -> availableGeometry().y(),
                width(),
                height());
    QWidget::show();

    animation.start();
    timer->start(5000);
}


void Notification::hideAnimation()
{
    timer->stop();
    animation.setDuration(1000);
    animation.setStartValue(1.0);
    animation.setEndValue(0.0);

    animation.start();
}

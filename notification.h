#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>

class Notification : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(float transparency READ getTransparency WRITE setTransparency)

public:
    explicit Notification(QWidget *parent = nullptr);


public slots:
    void show();
    void setMessage(const QString& msg);

private slots:
    void hideAnimation();

private:
    float getTransparency() const noexcept;
    void setTransparency(float _transparency);
    void paintEvent(QPaintEvent *event);

    float transparency;
    QTimer* timer;
    QLabel label;
    QGridLayout layout;
    QPropertyAnimation animation;
};

#endif // NOTIFICATION_H

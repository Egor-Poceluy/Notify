#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include <QSoundEffect>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QUrl>

class Notification : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(float transparency READ getTransparency WRITE setTransparency)

public:
    explicit Notification(QWidget *parent = nullptr);


public slots:
    void show();
    void setMessage(const QString& msg);
    void setSound(const QString& path, int volume = 100);

private slots:
    void calculateTime();

signals:
    void closed();

private:
    float getTransparency() const noexcept;
    void setTransparency(float _transparency);
    void paintEvent(QPaintEvent *event) override;
    void hideAnimation();

    int notificationLifeTime;
    float transparency;
    float progress;

    QSoundEffect *ring;
    QTimer* timer;
    QLabel label;
    QGridLayout layout;
    QPropertyAnimation animation;
};

#endif // NOTIFICATION_H

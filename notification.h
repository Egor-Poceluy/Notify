#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMediaPlayer>
#include <QSoundEffect>

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

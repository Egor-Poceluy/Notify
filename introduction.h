#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QMainWindow>
#include <QObject>

class introduction : public QObject
{
    Q_OBJECT
public:
    explicit introduction(QObject *parent = nullptr);

signals:
};

#endif // INTRODUCTION_H

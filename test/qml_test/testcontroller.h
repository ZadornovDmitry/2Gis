#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>

class TestController : public QObject
{
    // running state
    Q_PROPERTY(bool running  MEMBER running_ NOTIFY runningChanged)
    // current calculation state
    Q_PROPERTY(QString state  MEMBER state_ NOTIFY stateChanged)
    // property for progress bar when reading file
    Q_PROPERTY(float countingProgress  MEMBER countingProgress_ NOTIFY countingProgressChanged)

    Q_OBJECT

public:
    explicit TestController(QObject *parent = nullptr);
    ~TestController();

    Q_INVOKABLE void setRunning(bool b);
    Q_INVOKABLE void setState(const QString &state);
    Q_INVOKABLE void setCountingProgress(float f);
    Q_INVOKABLE void reset();

signals:
    void repetitionsChanged(const QVariantMap &ratings) const;
    void runningChanged();
    void stateChanged();
    void countingProgressChanged();

private:
    bool running_ = false;
    QString state_;
    float countingProgress_ = 0.0;
};

#endif // TESTCONTROLLER_H

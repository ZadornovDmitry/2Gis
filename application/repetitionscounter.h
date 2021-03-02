#ifndef REPETITIONSCOUNTER_H
#define REPETITIONSCOUNTER_H

#include <QObject>
#include <QMap>
#include <QFutureWatcher>
#include <QFile>

class RepetitionsCounter : public QObject
{
    // running state
    Q_PROPERTY(bool running  MEMBER running_ NOTIFY runningChanged)
    // current calculation state
    Q_PROPERTY(QString state  MEMBER state_ NOTIFY stateChanged)
    // property for progress bar when reading file
    Q_PROPERTY(float countingProgress  MEMBER countingProgress_ NOTIFY countingProgressChanged)

    Q_OBJECT

public:
    explicit RepetitionsCounter(QObject *parent = nullptr);
    ~RepetitionsCounter();
    // prepare and start calculations
    Q_INVOKABLE void run();
    // set input file path
    Q_INVOKABLE void setInputFile(const QString &fName);

signals:
    void repetitionsChanged(const QVariantMap &ratings) const;
    void runningChanged() const;
    void stateChanged() const;
    void countingProgressChanged() const;

private:
    QVariantMap calcRepetitions() const;
    // counting words reepetitions in file
    QMap<QString, int> countWords(QIODevice *fin) const;
    QMultiMap<int, QString>sortByRepetitions(const QMap<QString, int> &) const;
    // get first fifteen most repeatance words in file sorting by alphabet
    QVariantMap getFirstFifteen(const QMultiMap<int, QString> &) const;

private:

    QFutureWatcher<QVariantMap> warcher_;
    QString inputFileName_;
    mutable QString state_;
    bool running_ = false;
    mutable float countingProgress_ = 0;
public:
    friend class RepetitionsTest;

};

#endif // REPETITIONSCOUNTER_H

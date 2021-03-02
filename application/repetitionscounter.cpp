#include "repetitionscounter.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>


RepetitionsCounter::RepetitionsCounter(QObject *parent) : QObject(parent)
{

}

RepetitionsCounter::~RepetitionsCounter()
{

}

void RepetitionsCounter::run()
{
    connect(&warcher_, &QFutureWatcher<QVariantMap>::finished, this, [this]{
        // when calculations done - emit signal
        running_ = false;
        countingProgress_ = 0;
        state_.clear();
        emit runningChanged();
        if (!warcher_.result().isEmpty())
            emit repetitionsChanged(warcher_.result());
    });
    // preparing to run in new thread
    running_ = true;
    emit runningChanged();
    QFuture<QVariantMap> f = QtConcurrent::run(this, &RepetitionsCounter::calcRepetitions);
    warcher_.setFuture(f);
}

void RepetitionsCounter::setInputFile(const QString &fName)
{
    inputFileName_ = fName;
}

QVariantMap RepetitionsCounter::calcRepetitions() const
{
    QFile in(inputFileName_);
    if (!in.open(QIODevice::ReadOnly)){
        qDebug() << in.errorString();
        return QVariantMap();
    }
    state_ = QString("reading input file...");
    emit stateChanged();
    // counting words repetitions
    QMap<QString, int> words(countWords(&in));
    // sorting by repetitions
    QMultiMap<int, QString> rating(sortByRepetitions(words));
    // return first fifteen words sorted by repetitions
    return getFirstFifteen(rating);

}

QMap<QString, int> RepetitionsCounter::countWords(QIODevice *fin) const
{
    if (fin->isOpen()){
        fin->close();
    }

    fin->open(QIODevice::ReadOnly);

    QMap<QString, int> words;
    QTextStream s(fin);
    state_ = QString("counting words repetitions...");
    emit stateChanged();

    quint64 lines = 0;
    float oneLinePercents = 0;
    // thats not good design
    // first run through file to get amount of lines
    while (!s.atEnd()) {
        s.readLine();
        ++lines;
    }

    if (!lines){
        return words;
    }
    // get percents when one line processed
    oneLinePercents = 100.0/(float)lines;

    s.seek(0);

    while (!s.atEnd()) {
        // here is iportant thing, i asume that separator is a 'space'
        for (auto &word: s.readLine().split(" ")){
            words.insert(word, words.value(word, 0) + 1);
        }
        // updating progress
        countingProgress_+=oneLinePercents;
        emit countingProgressChanged();
    }

    countingProgress_= 100;
    emit countingProgressChanged();

    return words;
}

QMultiMap<int, QString> RepetitionsCounter::sortByRepetitions(const QMap<QString, int> &words) const
{
    // QMap sorting data by key
    // QMultiMap to store multiple data with same key(repetitions)
    QMultiMap<int, QString> rating;

    state_ = QString("sorting data...");
    emit stateChanged();

    for (auto i = words.begin(); i != words.end(); ++i){
        rating.insert(i.value(), i.key());
    }

    return rating;
}

QVariantMap RepetitionsCounter::getFirstFifteen(const QMultiMap<int, QString> &rating) const
{
    state_ = QString("get first fifteen words...");
    emit stateChanged();
    auto max = 0;
    QVariantMap lst;

    QMapIterator<int, QString> r_it(rating);
    r_it.toBack();
    int key = 0;

    // iterating backward to get first fifteen
    while ( max < 15 && r_it.hasPrevious()){
        r_it.previous();
        if (key == r_it.key()) continue;
        key = r_it.key();

        QStringList words(rating.values(r_it.key()));
        // iterating backward to get words by alphabet in sertain repetition

        for (auto w_it = words.rbegin(); w_it != words.rend(); ++w_it ){

            if (++max > 15)
                break;

            // qmap sort data by key(alphabet words sorting required)
            lst.insert(*w_it, r_it.key());
        }
    }

    return lst;
}




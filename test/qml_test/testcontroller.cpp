#include "testcontroller.h"

TestController::TestController(QObject *parent) : QObject(parent)
{

}

TestController::~TestController()
{

}

void TestController::setRunning(bool b)
{
    running_ = b;
    emit runningChanged();
}

void TestController::setState(const QString &state)
{
    state_ = state;
    emit stateChanged();
}

void TestController::setCountingProgress(float f)
{
    countingProgress_ = f;
    emit countingProgressChanged();
}

void TestController::reset()
{
    running_ = false;
    countingProgress_ = 0.0;
    state_.clear();

    emit runningChanged();
    emit stateChanged();
    emit countingProgressChanged();
}

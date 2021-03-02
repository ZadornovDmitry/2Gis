#include <QtQuickTest>
#include <QQmlEngine>
#include <QQmlContext>
//#include "../../application/repetitionscounter.h"
#include "testcontroller.h"

class Setup : public QObject
{
    Q_OBJECT

public:
    Setup() {}

public slots:
    void qmlEngineAvailable(QQmlEngine */*engine*/)
    {
        qmlRegisterType<TestController>("TestController", 1, 0, "TestController");
    }
};

int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    app.setOrganizationName("2Gis");
    app.setApplicationName("Test App");
    QTEST_SET_MAIN_SOURCE_PATH
    Setup setup;
    return quick_test_main_with_setup(argc, argv, "tst_repetitions", QUICK_TEST_SOURCE_DIR, &setup);
}



#include "setup.moc"

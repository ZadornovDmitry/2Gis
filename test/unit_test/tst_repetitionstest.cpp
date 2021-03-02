#include <QtTest>
#include <QCoreApplication>
#include "../../application/repetitionscounter.h"
#include <QDebug>

// add necessary includes here

class RepetitionsTest : public QObject
{
    Q_OBJECT

public:
    RepetitionsTest();
    ~RepetitionsTest();

private slots:
    void count_words_test();
    void sort_repetitions_test();
    void get_first_fifteen_test();
};

RepetitionsTest::RepetitionsTest()
{

}

RepetitionsTest::~RepetitionsTest()
{

}

void RepetitionsTest::count_words_test()
{
    RepetitionsCounter rc;
    QFile f("test");
    f.open(QIODevice::ReadWrite);
    QTextStream ts(&f);
    ts << "aaaa bbbb bbbb bbb cccc cccc cccc dddd eeee ffff";

    auto out = rc.countWords(&f);
    QMap<QString, int> ex;

    ex.insert("aaaa", 1);
    ex.insert("bbbb", 2);
    ex.insert("bbb",  1);
    ex.insert("cccc", 3);
    ex.insert("dddd", 1);
    ex.insert("eeee", 1);
    ex.insert("ffff", 1);

    QCOMPARE(out, ex);
    f.remove();
}

void RepetitionsTest::sort_repetitions_test()
{
     RepetitionsCounter rc;
     QMap<QString, int> in;
     in.insert("aaaa", 1);
     in.insert("bbbb", 2);
     in.insert("bbb",  1);
     in.insert("cccc", 2);
     in.insert("dddd", 1);
     in.insert("eeee", 3);
     in.insert("ffff", 2);

     QMultiMap<int, QString> ex;
     ex.insert(1, "aaaa" );
     ex.insert(2, "bbbb" );
     ex.insert(1, "bbb"  );
     ex.insert(2, "cccc" );
     ex.insert(1, "dddd" );
     ex.insert(3, "eeee" );
     ex.insert(2, "ffff" );

     auto out = rc.sortByRepetitions(in);

     QCOMPARE(out, ex);
     QCOMPARE(out.values(2), QStringList() << "ffff" << "cccc" << "bbbb");
     QCOMPARE(out.values(1), QStringList() << "dddd" << "bbb" << "aaaa");

}
void RepetitionsTest::get_first_fifteen_test()
{
    RepetitionsCounter rc;

    QMultiMap<int, QString> in;
    in.insert(10, "aaaa" );
    in.insert(10, "abbb" );
    in.insert(9, "bbbb"  );
    in.insert(9, "cccc" );
    in.insert(9, "dddd" );
    in.insert(1, "eeee" );
    in.insert(4, "ffff" );
    in.insert(7, "gggg" );
    in.insert(8, "gaaa" );
    in.insert(2, "iiii" );
    in.insert(2, "kkkk" );
    in.insert(2, "llll" );
    in.insert(2, "mmmm" );
    in.insert(2, "nnnn" );
    in.insert(2, "oooo" );
    in.insert(2, "pppp" );


    QVariantMap ex;
    ex.insert("aaaa", 10);
    ex.insert("abbb", 10);
    ex.insert("bbbb", 9);
    ex.insert("cccc", 9);
    ex.insert("dddd", 9);
    ex.insert("ffff", 4);
    ex.insert("gaaa", 8);
    ex.insert("gggg", 7);
    ex.insert("iiii", 2);
    ex.insert("kkkk", 2);
    ex.insert("llll", 2);
    ex.insert("mmmm", 2);
    ex.insert("nnnn", 2);
    ex.insert("oooo", 2);
    ex.insert("pppp", 2);


    auto out = rc.getFirstFifteen(in);

    QCOMPARE(out.size(), 15);
    QCOMPARE(out,ex);

    in.clear();
    ex.clear();
    in.insert(10, "aaaa" );
    ex.insert("aaaa", 10);
    out = rc.getFirstFifteen(in);

    QCOMPARE(out, ex);
}

QTEST_MAIN(RepetitionsTest)

#include "tst_repetitionstest.moc"

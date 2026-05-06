#include <QTest>
#include "../domain.h"
// add necessary includes here
using namespace std;
class test_domain : public QObject
{
    Q_OBJECT

public:
    test_domain();
    ~test_domain();

private slots:
    void initTestCase();
    void init();
    void cleanupTestCase();
    void cleanup();
    void test_case1();

private:
    std::vector<std::string> forbidden_domains_;
    std::vector<std::string> test_domains_;
};

test_domain::test_domain() {}

test_domain::~test_domain() {}

void test_domain::initTestCase()
{
    // code to be executed before the first test function
    forbidden_domains_ = {"gdz.ru", "maps.me", "m.gdz.ru","com"};
    test_domains_  = {"gdz.ru", "gdz.com", "m.maps.me","alg.m.gdz.ru","maps.com","maps.ru","gdz.ua"};

}

void test_domain::init()
{
    // code to be executed before each test function
}

void test_domain::cleanupTestCase()
{
    // code to be executed after the last test function
}

void test_domain::cleanup()
{
    // code to be executed after each test function
}

void test_domain::test_case1() {}

QTEST_APPLESS_MAIN(test_domain)

#include "tst_test_domain.moc"

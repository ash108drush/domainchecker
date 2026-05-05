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
};

test_domain::test_domain() {}

test_domain::~test_domain() {}

void test_domain::initTestCase()
{
    // code to be executed before the first test function
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
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

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
    void test_subdomain();

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

void test_domain::test_subdomain() {
    for(auto& d1: forbidden_domains_){
        Domain dom1 = Domain(d1);
            for(auto& d2: forbidden_domains_){
                Domain dom2 = Domain(d2);
                if(dom1.IsSubdomain(dom2)){
                    std::cout << dom1.GetString() << " is subdomain: " << dom2.GetString() << std::endl;
                }


            }


    }

}

QTEST_APPLESS_MAIN(test_domain)

#include "tst_test_domain.moc"

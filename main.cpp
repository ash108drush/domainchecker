#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <functional>
#include <typeinfo>
#include <iterator>

using namespace std;



class Domain {
    // разработайте класс домена
public:
    Domain(std::string str):domain_name_(str){

    }
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами

    // разработайте operator==
 //   operator==(Domain& domain ){
 //       return true;
 //   }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& domain){
        return true;
    }
private:
    string domain_name_;
};

class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    DomainChecker(std::vector<Domain>::iterator first,std::vector<Domain>::iterator last):domains_(first,last) {

    }

    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(Domain domain){
        return true;
    }
    private:
    std::vector<Domain> domains_;

};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа


template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}



template <typename Number>
const std::vector<Domain> ReadDomains(istream& input, Number&& num) {
    std::vector<Domain> domains;
    std::ostringstream ss;
    ss << num;
    size_t count = // Читаем количество доменов
    std::istringstream(ss.str()) >> count;
    for (size_t i = 0; i < count; ++i) {
        string domain_str;
        getline(input, domain_str);
        domains.push_back(Domain(domain_str)); // Предполагаем конструктор Domain(string)
    }

    return domains;
}

int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}

/*
 4
gdz.ru
maps.me
m.gdz.ru
com
7
gdz.ru
gdz.com
m.maps.me
alg.m.gdz.ru
maps.com
maps.ru
gdz.ua
*/

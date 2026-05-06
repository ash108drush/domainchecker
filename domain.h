#ifndef DOMAIN_H
#define DOMAIN_H
#include <sstream>
#include <string_view>
#include <vector>
#include <functional>
#include <typeinfo>
#include <iterator>
#include <iostream>
using namespace std;



class Domain {
    // разработайте класс домена
public:
    Domain(std::string str):domain_name_(str){

    }
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами

    // разработайте operator==
    bool operator==(Domain& domain ){
        if(*this == domain) return true;

        return domain.domain_name_ == domain_name_;
    }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& domain){
        return (domain_name_.find("." + domain.domain_name_) != string::npos);

    }

    std::string GetString(){
        return domain_name_;
    }
private:
    string domain_name_;
};



class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template <typename InputIt>
    DomainChecker(InputIt begin, InputIt end):domains_(begin,end) {

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
    size_t count = 0;
    std::istringstream(ss.str()) >> count;
    for (size_t i = 0; i < count; ++i) {
        string domain_str;
        getline(input, domain_str);
        domains.push_back(Domain(domain_str));
    }

    return domains;
}
#endif // DOMAIN_H

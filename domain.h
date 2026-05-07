#ifndef DOMAIN_H
#define DOMAIN_H
#include <sstream>
#include <string_view>
#include <vector>
#include <functional>
#include <typeinfo>
#include <iterator>
#include <iostream>
#include <algorithm>

using namespace std;



class Domain {
    // разработайте класс домена
public:
    Domain(const std::string str):domain_name_(str),rev_domain_name_(str){
        rev_domain_name_.append(".");
        std::reverse(rev_domain_name_.begin(), rev_domain_name_.end());
       // std::cout << "rev-name: " << rev_domain_name_ << std::endl;

    }
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами

    // разработайте operator==
    bool operator==(Domain& domain ){
        return domain.domain_name_ == domain_name_;
    }

    bool operator==(const Domain& domain ){
        return domain.domain_name_ == domain_name_;
    }

    bool operator !=(Domain& domain ){
        return domain.domain_name_ != domain_name_;
    }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& domain) const{
        int min = std::min(rev_domain_name_.size(), domain.rev_domain_name_.size());
        return (rev_domain_name_.compare(0, min, domain.rev_domain_name_) == 0);

    }

    std::string GetString() const{
        return domain_name_;
    }
    std::string_view GetReverse() const{
        return rev_domain_name_;
    }
private:
    string domain_name_;
    string rev_domain_name_;
};



class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template <typename InputIt>
    DomainChecker(InputIt begin, InputIt end):domains_(begin,end) {
        std::vector<Domain> domains;
        for(auto& d1: domains_){
            Domain dom1 = Domain(d1);
            bool single = true;
            for(auto& d2: domains_){
                Domain dom2 = Domain(d2);
                if((dom1 != dom2) && dom1.IsSubdomain(dom2)){
                    single = false;
                }
            }
            if(single){
                domains.push_back(dom1);
            }
        }
        domains_ = std::move(domains);
    }


    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain domain){
        for(auto& d: domains_){
            int min = std::min(d.GetReverse().size(), domain.GetReverse().size());
            return (domain.GetReverse().compare(0, min, d.GetReverse()) == 0);

        }

        return false;
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

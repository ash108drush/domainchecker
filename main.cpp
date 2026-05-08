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
    Domain(const std::string str):domain_name_(str){
        std::string rev_name = "." +domain_name_;
        //std::reverse(rev_name.begin(), rev_name.end());
        rev_domain_name_ = std::string(rev_name.rbegin(),rev_name.rend());
        //std::reverse(rev_domain_name_.begin(), rev_domain_name_.end());
        // std::cout << "rev-name: " << rev_domain_name_ << std::endl;

    }
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами

    // разработайте operator==

/*
    bool operator !=(Domain& domain ){
        return domain.domain_name_ != domain_name_;
    }
*/
    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& domain) const{
        int min = std::min(rev_domain_name_.size(), domain.rev_domain_name_.size());
        if(rev_domain_name_.compare(0, min, domain.rev_domain_name_) == 0){
           // std::cout << "found subdomain" << std::endl;
            return true;
        }
        //std::cout << " not found subdomain: " << rev_domain_name_  << "===" << domain.rev_domain_name_ << std::endl;
        return false;

    }

    bool IsSubdomain(const string_view domain) const{
        int min = std::min(rev_domain_name_.size(), domain.size());
        if(rev_domain_name_.compare(0, min, domain) == 0){
            return true;
        }
       // std::cout << " not found subdomain: " << rev_domain_name_  << "===" << domain << std::endl;
        return false;

    }

    std::string_view GetString() const{
        return domain_name_;
    }
    std::string_view GetReverse() const{
        return rev_domain_name_;
    }
    friend bool operator==(Domain& domain1,Domain& domain2 );
    friend bool operator==(const Domain& domain1,const Domain& domain2 );
private:
    string domain_name_;
    string rev_domain_name_;
};



class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template <typename InputIt>
    DomainChecker(InputIt begin, InputIt end):domains_(begin,end) {
        for(auto i= domains_.begin(); i != domains_.end(); ++i){
            rev_names_.push_back(i->GetReverse());
        }
        std::sort(domains_.begin(),domains_.end(),[](const Domain& left, const Domain& right  ){
            std::string_view lstring = left.GetReverse();
            std::string_view rstring = right.GetReverse();
            return std::lexicographical_compare( lstring.begin(), lstring.end(),rstring.begin(), rstring.end());
        });

        std::sort(rev_names_.begin(),rev_names_.end(),[](const string_view left, const string_view right  ){
            return std::lexicographical_compare( left.begin(), left.end(),right.begin(), right.end());
        });

        auto last = std::unique(domains_.begin(),domains_.end(),[](const Domain& left, const Domain& right ){
            bool subdomain = right.IsSubdomain(left);
            bool equal = (left == right);
            return (subdomain || equal);
        });

        //auto lasts = std::unique(rev_names_.begin(),rev_names_.end(),[](const string_view left, const string_view right){
//

       //     return std::lexicographical_compare( left.begin(), left.end(),right.begin(), right.end());

      //  });

        //rev_names_.erase(lasts,rev_names_.end());
        domains_.erase(last, domains_.end());


  }

    void PrintDomains(){
        for(auto& d: rev_names_){
            std::cout << "vector name:" << d << std::endl;
        }
        for(auto& d: domains_){
            std::cout << "rev_name:" << d.GetReverse() << std::endl;
        }
    }

    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain& domain){

        std::cout << "++++++++++++++++++" << std::endl;
/*
        for(auto d:domains_){
            bool subdomain = (d.IsSubdomain(domain) || domain.IsSubdomain(d));
            bool equal = (domain == d);
            if(subdomain || equal){
                return true;
            }
        }

*/
        //std::cout << "size:" << domains_.size() << std::endl;
     auto upper = std::upper_bound(domains_.begin(), domains_.end(),domain,[](const Domain& value, const Domain& forbidden  ){
            //std::string lstring = value.GetReverse();
            //std::string rstring = forbidden.GetReverse();
            //std::cout <<"compare: "   << lstring << " to: " << rstring << std::endl;
            //return (lstring.compare(rstring) <=0);
            return value.IsSubdomain(forbidden);

//                (lstring.compare(rstring) <= 0);
//value.IsSubdomain(forbidden) || forbidden.IsSubdomain(value) ||

        });
        if(upper == domains_.begin()){
            cout << "begin:" << upper->GetString() << std::endl;
            return false;
        }
        if(upper == domains_.end()){
            std::cout << "out of range: "  << domain.GetString()<< std::endl;
            return false;
        }else{
            cout << "upper:" << upper->GetString() << std::endl;
        }

        return true;
    }
private:
    std::vector<Domain> domains_;
    std::vector<std::string_view> rev_names_;


};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
bool operator==(Domain& domain1,Domain& domain2 ){
    if(&domain1 ==  &domain2) return true;
    return domain1.domain_name_ == domain2.domain_name_;
}

bool operator==(const Domain& domain1,const Domain& domain2 ){
    if(&domain1 ==  &domain2) return true;
    return domain1.domain_name_ == domain2.domain_name_;
}

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


int main() {
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());


    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));

   checker.PrintDomains();
/*
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
        //cout << domain.GetString() << endl;
    }
*/
}



/*
 *
 *

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

1
a
4
aaaa.aa
aaaa.aaa.a
a.a.a
a


1
a
1
aaaa.aa



*/


/*
 *4
1
com1
7
gdz.ru
gdz.com
m.maps.me
alg.m.gdz.ru
maps.com
maps.ru
gdz.ua
*/

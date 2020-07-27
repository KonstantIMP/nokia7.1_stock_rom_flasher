#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <cstddef>

#include <string>
#include <ctime>

namespace KonstantIMP {

class log {
public:
    log(std::ostream *);

    virtual void make_record(const std::string &);

protected:
    std::ostream * os;

    std::string get_date() const;
};

};

#endif // LOG_HPP

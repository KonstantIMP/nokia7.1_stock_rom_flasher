#include "../include/log.hpp"

namespace KonstantIMP {

log::log(std::ostream * out) : os(out) {}

void log::make_record(const std::string & msg) {
    *os << "[ " << get_date() << " ] " << msg << "\r\n" << std::flush;
}

std::string log::get_date() const {
    time_t t = time(nullptr);

    tm * t_info = localtime(&t);

    char buffer[18];
    for(std::size_t i{0}; i < 18; i++) buffer[i] = 0;

    std::strftime(buffer, sizeof (buffer), "%d.%m.%y %H:%M:%S", t_info);

    return std::string(buffer);
}

};

#include "../include/log.hpp"

namespace KonstantIMP {

log::log(std::ostream * out) : os(out) {
    get_datetime();
}

void log::make_record(const std::string & record) {
    *os << '[' << this->get_datetime() << "] " << record << "\r\n";
}

std::string log::get_datetime() const {
    time_t t = time(nullptr);
    tm * timeinfo;

    timeinfo = localtime(&t);

    char buffer[18];
    for(std::size_t i{0}; i < 18; i++) buffer[i] = 0;

    strftime(buffer, sizeof (buffer), "%d.%m.%y %H:%M:%S", timeinfo);

    std::cout << buffer;

    return std::string(buffer);
}

}

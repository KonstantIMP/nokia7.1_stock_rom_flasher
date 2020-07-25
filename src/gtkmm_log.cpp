#include "../include/gtkmm_log.hpp"

KonstantIMP::gtkmm_log::gtkmm_log(std::ostream * out, Gtk::TextView * log_v) : KonstantIMP::log(out), log_viewer(log_v) {}

void KonstantIMP::gtkmm_log::make_record(const std::string & record) {
    std::string tmp = '[' + this->get_datetime() + "] " + record + "\r\n";
    *os << tmp << std::flush; log_viewer->get_buffer()->set_text(log_viewer->get_buffer()->get_text() + tmp);
}

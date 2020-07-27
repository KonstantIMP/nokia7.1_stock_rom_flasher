#include "../include/gtkmm_log.hpp"

namespace KonstantIMP {

gtkmm_log::gtkmm_log(std::ostream * out) : KonstantIMP::log(out) {
    this->add(log_viewer);

    log_viewer.get_buffer()->create_mark("last_line", log_viewer.get_buffer()->end());
}

void gtkmm_log::make_record(const std::string & msg) {
    std::string record = "[ " + get_date() + " ] " + msg + "\r\n";

    log_viewer.get_buffer()->set_text(log_viewer.get_buffer()->get_text() + record);
    *os << record << std::flush;

    auto mark = log_viewer.get_buffer()->get_mark("last_line");
    log_viewer.get_buffer()->move_mark(mark, log_viewer.get_buffer()->end());

    log_viewer.scroll_to(mark);
}

};

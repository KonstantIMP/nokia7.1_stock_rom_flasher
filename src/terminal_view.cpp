#include "../include/terminal_view.hpp"

namespace KonstantIMP {

terminal_view::terminal_view(const std::string & prf) : Gtk::ScrolledWindow(), prefix(prf) {
    this->add(terminal);

    terminal.set_editable(false);
    terminal.get_buffer()->create_mark("last_line", terminal.get_buffer()->end());
    terminal.get_buffer()->set_text('[' + prf + "] ");
}

void terminal_view::run_process(const std::string & command) {
    terminal.get_buffer()->set_text(terminal.get_buffer()->get_text() + command + "\r\n");

    system(std::string(command + " >> p_out.txt").c_str());

    std::ifstream fin("p_out.txt"); std::string buf = "";

    if(!fin.is_open()) return;

    while(!fin.eof()) {
        std::getline(fin, buf);
        terminal.get_buffer()->set_text(terminal.get_buffer()->get_text() + buf + "\r\n");
    }

    fin.close(); std::remove("p_out.txt");

    terminal.get_buffer()->set_text(terminal.get_buffer()->get_text() + '[' + prefix + "] ");

    auto mark = terminal.get_buffer()->get_mark("last_line");
    terminal.get_buffer()->move_mark(mark, terminal.get_buffer()->end());

    terminal.scroll_to(mark);
}

Glib::ustring terminal_view::get_buffer_text() const {
    return terminal.get_buffer()->get_text();
}


};

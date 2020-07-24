#include "../include/terminalview.hpp"

TerminalView::TerminalView(const Glib::ustring & command) : Gtk::TextView() {
    this->set_editable(false);
    this->get_buffer()->set_text("");
    this->set_buffer(this->get_buffer());

    if(command != "") this->run_process(command);
}

void TerminalView::set_prefix(const Glib::ustring & prf) {
    prefix = prf;

    this->get_buffer()->set_text(prf);
    this->set_buffer(this->get_buffer());
}

Glib::ustring TerminalView::get_prefix() const {
    return prefix;
}

void TerminalView::print_message(const Glib::ustring & msg) {
    this->get_buffer()->set_text(this->get_buffer()->get_text() + " [MESSAGE] " + msg + "\n" + prefix);
}

void TerminalView::run_process(const Glib::ustring & command) {
    if(command == "") throw std::runtime_error("Command can\'t be empty");

    this->get_buffer()->set_text(this->get_buffer()->get_text() + " " + command + "\n\t");

    char buffer[2];
    buffer[1] = 0;

    FILE * process = popen(command.c_str(), "r");

    if(process == nullptr) throw std::runtime_error("fork() or pipe(): can\'t allocate memory for process");

    while (fread(buffer, 1, 1, process)) {
        this->get_buffer()->set_text(this->get_buffer()->get_text() + buffer);
        if(buffer[0] == '\n') this->get_buffer()->set_text(this->get_buffer()->get_text());
        buffer[0] = 0; buffer[1] = 0;
    }

    this->get_buffer()->set_text(this->get_buffer()->get_text() + prefix);

    pclose(process);
}

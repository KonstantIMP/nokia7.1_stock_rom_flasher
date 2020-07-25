#ifndef FLASHER_HPP
#define FLASHER_HPP

#include "terminalview.hpp"

#include <fstream>

#include <mutex>

class Flasher {
public:
    Flasher(TerminalView *, std::ofstream *, Gtk::TextView *);

    double get_fraction();

    void do_work(const Glib::ustring &, const Glib::ustring &, Glib::Dispatcher *);

private:
    TerminalView * term;

    std::ofstream * log;

    Gtk::TextView * log_text;

    double fraction;

    std::mutex mtx;
};

#endif // FLASHER_HPP

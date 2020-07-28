#ifndef TERMINAL_VIEW_HPP
#define TERMINAL_VIEW_HPP

#include <fstream>
#include <cstdio>

#include <gtkmm.h>
#include <string>

namespace KonstantIMP {

class terminal_view : public Gtk::ScrolledWindow {
public:
    terminal_view(const std::string &);

    void run_process(const std::string &);

private:
    Gtk::TextView terminal;

    std::string prefix;
};

};

#endif // TERMINAL_VIEW_HPP

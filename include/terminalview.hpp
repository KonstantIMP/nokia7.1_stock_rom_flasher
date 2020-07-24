#ifndef TERMINALVIEW_HPP
#define TERMINALVIEW_HPP

#include <gtkmm.h>

#include <cstdio>

class TerminalView : public Gtk::TextView {
public:
    TerminalView(const Glib::ustring & = "");

    void set_prefix(const Glib::ustring &);
    Glib::ustring get_prefix() const;

    void print_message(const Glib::ustring &);

    void run_process(const Glib::ustring &);

private:
    Glib::ustring prefix;
};

#endif // TERMINALVIEW_HPP

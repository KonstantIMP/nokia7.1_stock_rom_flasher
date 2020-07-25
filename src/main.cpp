#include "../include/mainwindow.hpp"

#include <gtkmm.h>

int main(int argc, char * argv[]) {
    Glib::RefPtr<Gtk::Application> nokia_tool = Gtk::Application::create(argc, argv, "org.gtkmm.base");

    MainWindow win;

    win.show_all();

    nokia_tool->run(win);

    return 0;
}

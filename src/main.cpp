#include "../include/mainwindow.hpp"

int main(int argc, char * argv[]) {
    auto nokia = Gtk::Application::create(argc, argv, "org.nokia.flasher.base");

    MainWindow m_win;

    m_win.show_all();

    return nokia->run(m_win);
}


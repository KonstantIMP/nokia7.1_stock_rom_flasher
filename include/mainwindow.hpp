#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "terminalview.hpp"

#include <fstream>

#include <gtkmm.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();

protected:
    void create_ui();

    void connect_sig();

    void on_adb_clicked();
    void on_rom_clicked();

private:
    Gtk::Label adb_msg;
    Gtk::Label rom_msg;

    Gtk::Button adb_btn;
    Gtk::Button rom_btn;
    Gtk::Button info_btn;

    Gtk::Label log_msg;

    Gtk::TextView log_text;

    Gtk::Grid main_grid;

    TerminalView term;

    Gtk::Button flash_btn;

    Gtk::ProgressBar load_bar;

    Gtk::Entry adb_en;
    Gtk::Entry rom_en;

    Gtk::Button set_adb_btn;
    Gtk::Button set_rom_btn;

    Gtk::ScrolledWindow terminal_scrol;
    Gtk::ScrolledWindow log_scrol;

    std::ofstream log;
};

#endif // MAINWINDOW_HPP

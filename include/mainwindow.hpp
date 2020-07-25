#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "terminalview.hpp"
#include "flasher.hpp"

#include <fstream>

#include <thread>

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

    void on_help_clicked();

    void set_adb_path();
    void set_rom_path();

    void start_flash();

    void work_done();

    void update_widgets();

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

    std::thread * flash_t;

    Glib::Dispatcher work_d;

    Flasher worker;
};

#endif // MAINWINDOW_HPP

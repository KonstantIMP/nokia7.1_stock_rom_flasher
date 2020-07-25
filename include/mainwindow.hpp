#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "terminalview.hpp"
#include "gtkmm_log.hpp"

#include <gtkmm.h>

#include <fstream>
#include <thread>

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    virtual ~MainWindow();

    void notify();

protected:
    void create_ui();

    void connect_sig();

    void on_adb_clicked();
    void on_rom_clicked();

    void on_help_clicked();

    void set_adb_path();
    void set_rom_path();

    void start_flash();

    void flash_finished_sig();

private:
    Gtk::Grid main_grid;

    Gtk::Entry adb_en;
    Gtk::Entry rom_en;

    Gtk::Label adb_msg;
    Gtk::Label rom_msg;

    Gtk::Label log_msg;

    Gtk::Button adb_btn;
    Gtk::Button rom_btn;
    Gtk::Button info_btn;

    Gtk::Button flash_btn;

    Gtk::Button set_adb_btn;
    Gtk::Button set_rom_btn;

    TerminalView term;
    Gtk::TextView log_viewer;

    Gtk::ProgressBar load_bar;

    Gtk::ScrolledWindow log_scrol;
    Gtk::ScrolledWindow terminal_scrol;

    KonstantIMP::gtkmm_log logger;
    std::ofstream log;


    std::thread * f_thread;

    Glib::Dispatcher f_dispatcher;
};

#endif // MAINWINDOW_HPP

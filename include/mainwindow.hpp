#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "gtkmm_log.hpp"

#include <fstream>
#include <gtkmm.h>

#include <string>

namespace KonstantIMP {

#ifdef __linux
    const std::string os = " LINUX ";
#else
    const std::string os = "WINDOWS";
#endif

const std::string log_name = "nokia7.1_flash.log";

class MainWindow : public Gtk::Window {
public:
    MainWindow();

    virtual ~MainWindow();

protected:
    void create_ui();
    void connect_signals();

private:
    Gtk::Grid main_grid;

    Gtk::Label adb_msg;
    Gtk::Label rom_msg;
    Gtk::Label log_msg;
    Gtk::Label cmd_msg;

    Gtk::Button flash_btn;

    Gtk::Button get_adb_btn;
    Gtk::Button get_rom_btn;
    Gtk::Button get_help_btn;
    Gtk::Button set_adb_path_btn;
    Gtk::Button set_rom_path_btn;

    Gtk::Entry adb_path_en;
    Gtk::Entry rom_path_en;

    Gtk::ProgressBar flash_load;

    std::ofstream log_file;
    KonstantIMP::gtkmm_log logger;
};

};

#endif // MAINWINDOW_HPP

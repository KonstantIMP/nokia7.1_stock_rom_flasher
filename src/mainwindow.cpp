#include "../include/mainwindow.hpp"

namespace KonstantIMP {

MainWindow::MainWindow() : log_file(log_name, std::ios_base::app) , logger(&log_file), term(KonstantIMP::os) {
    this->set_title("Nokia7.1 Stock Rom Flasher");

    create_ui();
    connect_signals();

    logger.make_record("Program started");

    if(os == " LINUX ") {
        logger.make_record("ADB will be finded in the PATH");
        set_adb_path_btn.set_sensitive(false);
        adb_path_en.set_sensitive(false);
        adb_path_en.set_text("PATH");
    }
}

MainWindow::~MainWindow() {
    logger.make_record("Program closed");
    log_file.close();
}

void MainWindow::create_ui() {
    adb_msg.set_text("ADB");
    adb_msg.set_xalign(0.f);

    rom_msg.set_text("ROM");
    rom_msg.set_xalign(0.f);

    log_msg.set_text("LOG");
    log_msg.set_xalign(0.f);

    cmd_msg.set_text("Fastboot out");
    cmd_msg.set_xalign(0.f);

    flash_load.set_text("Flashing...");
    flash_load.set_show_text(true);

    set_adb_path_btn.set_label("...");
    set_rom_path_btn.set_label("...");

    get_adb_btn.set_label("Get ADB");
    get_rom_btn.set_label("Get ROM");
    get_help_btn.set_label("Get help");

    flash_btn.set_label("Flash Nokia 7.1");

    main_grid.attach(adb_msg, 0, 0, 2, 1);
    main_grid.attach(rom_msg, 0, 1, 2, 1);
    main_grid.attach(log_msg, 0, 3, 9, 1);
    main_grid.attach(cmd_msg, 9, 0, 9, 1);

    main_grid.attach(adb_path_en, 2, 0, 6, 1);
    main_grid.attach(rom_path_en, 2, 1, 6, 1);

    main_grid.attach(flash_load, 9, 7, 9, 1);

    main_grid.attach(set_adb_path_btn, 8, 0, 1, 1);
    main_grid.attach(set_rom_path_btn, 8, 1, 1, 1);

    main_grid.attach(get_adb_btn, 0, 2, 3, 1);
    main_grid.attach(get_rom_btn, 3, 2, 3, 1);
    main_grid.attach(get_help_btn, 6, 2, 3, 1);

    main_grid.attach(flash_btn, 9, 8, 9, 1);

    main_grid.attach(logger, 0, 4, 9, 4);
    main_grid.attach(term, 9, 1, 9, 6);

    this->set_border_width(10);
    main_grid.set_row_spacing(10);
    main_grid.set_column_spacing(10);

    main_grid.set_row_homogeneous(true);
    main_grid.set_column_homogeneous(true);

    this->add(main_grid);
}

void MainWindow::connect_signals() {
    set_adb_path_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_set_adb_path_clocked));
    set_rom_path_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_set_rom_path_clocked));
}

void MainWindow::on_set_adb_path_clocked() {
    Gtk::FileChooserDialog adb_path(*this, "Set ADB path", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    adb_path.add_button("Cancel", Gtk::RESPONSE_NO);
    adb_path.add_button("OK", Gtk::RESPONSE_OK);

    if(adb_path.run() == Gtk::RESPONSE_OK) adb_path_en.set_text(adb_path.get_filename());
}

void MainWindow::on_set_rom_path_clocked() {
    Gtk::FileChooserDialog rom_path(*this, "Set ROM path", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    rom_path.add_button("Cancel", Gtk::RESPONSE_NO);
    rom_path.add_button("OK", Gtk::RESPONSE_OK);

    if(rom_path.run() == Gtk::RESPONSE_OK) rom_path_en.set_text(rom_path.get_filename());
}

};

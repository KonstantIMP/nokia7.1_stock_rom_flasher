#include "../include/mainwindow.hpp"

MainWindow::MainWindow() {
    this->set_title("Nokia7.1 Stock Rom Flasher");

    create_ui();
    connect_signals();
}

MainWindow::~MainWindow()
{

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

    main_grid.attach(adb_msg, 0, 0, 3, 1);
    main_grid.attach(rom_msg, 0, 1, 3, 1);
    main_grid.attach(log_msg, 0, 3, 9, 1);
    main_grid.attach(cmd_msg, 9, 0, 9, 1);

    main_grid.attach(adb_path_en, 3, 0, 5, 1);
    main_grid.attach(rom_path_en, 3, 1, 5, 1);

    main_grid.attach(flash_load, 9, 7, 9, 1);

    main_grid.attach(set_adb_path_btn, 8, 0, 1, 1);
    main_grid.attach(set_rom_path_btn, 8, 1, 1, 1);

    main_grid.attach(get_adb_btn, 0, 2, 3, 1);
    main_grid.attach(get_rom_btn, 3, 2, 3, 1);
    main_grid.attach(get_help_btn, 6, 2, 3, 1);

    main_grid.attach(flash_btn, 9, 8, 9, 1);

    this->set_border_width(10);
    main_grid.set_row_spacing(10);
    main_grid.set_column_spacing(10);

    main_grid.set_row_homogeneous(true);
    main_grid.set_column_homogeneous(true);

    this->add(main_grid);
}

void MainWindow::connect_signals()
{

}

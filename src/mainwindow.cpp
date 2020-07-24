#include "mainwindow.hpp"

#include <string>

#ifdef __linux
    const std::string prf = "[ LINUX ]";
#else
    const std::string prf = "[WINDOWS]";
#endif

MainWindow::MainWindow() {
    this->set_title("Nokia 7.1 stock rom flasher");

    flash_btn.set_label("Flash Nokia 7.1");

    this->create_ui();

    term.set_prefix(prf);

    adb_msg.set_text("ADB path :");
    rom_msg.set_text("ROM path :");

    adb_btn.set_label("Get ADB");
    rom_btn.set_label("Get ROM");
    info_btn.set_label("HELP");

    log_msg.set_text("Flasher LOGs :");

    set_adb_btn.set_label("...");
    set_rom_btn.set_label("...");

    log.open("nokia7.1_flash.log", std::ios_base::app);

    log << "[LOG] Programm started\r\n";
    log_text.get_buffer()->set_text(log_text.get_buffer()->get_text() + "[LOG] Programm started\r\n");

    if(prf == "[ LINUX ]") {
        log << "[LOG] You use linux. ADB will be finded in the PATH\r\n";
        log_text.get_buffer()->set_text(log_text.get_buffer()->get_text() + "[LOG] You use linux. ADB will be finded in the PATH\r\n");

        adb_en.set_text("PATH");
        adb_en.set_editable(false);

        set_adb_btn.set_can_focus(false);
        set_adb_btn.set_visible(false);
    }

    this->connect_sig();
}

MainWindow::~MainWindow() {
    log << "[LOG] Programm closed\r\n";
    log_text.get_buffer()->set_text(log_text.get_buffer()->get_text() + "[LOG] Programm closed\r\n");

    log.close();
}

void MainWindow::create_ui() {
    this->set_border_width(10);

    this->add(main_grid);

    log_msg.set_alignment(0);

    terminal_scrol.add(term);

    main_grid.attach(adb_msg, 0, 0, 3, 1);
    main_grid.attach(rom_msg, 0, 1, 3, 1);

    main_grid.attach(adb_btn, 0, 2, 4, 1);
    main_grid.attach(rom_btn, 4, 2, 4, 1);
    main_grid.attach(info_btn, 8, 2, 2, 1);

    main_grid.attach(log_msg, 0, 3, 10, 1);

    log_scrol.add(log_text);

    main_grid.attach(log_scrol, 0, 4, 10, 4);

    main_grid.attach(terminal_scrol, 10, 0, 11, 10);

    main_grid.attach(load_bar, 0, 8, 10, 1);
    main_grid.attach(flash_btn, 0, 9, 10, 1);

    main_grid.attach(adb_en, 3, 0, 6, 1);
    main_grid.attach(rom_en, 3, 1, 6, 1);

    main_grid.attach(set_adb_btn, 9, 0, 1, 1);
    main_grid.attach(set_rom_btn, 9, 1, 1, 1);

    main_grid.set_row_homogeneous(true);
    main_grid.set_column_homogeneous(true);

    main_grid.set_row_spacing(5);
    main_grid.set_column_spacing(5);

    log_text.set_left_margin(3);
    log_text.set_border_width(2);
}

void MainWindow::connect_sig() {
    adb_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_adb_clicked));
    rom_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_rom_clicked));
}

void MainWindow::on_adb_clicked() {
    Gtk::MessageDialog adb(*this, "How to get ADB", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);

    adb.set_secondary_text("To download adb and fastboot visit https://developer.android.com/studio/releases/platform-tools and download it for your system, or if you use Linux you can download it using your packet manager");

    adb.run();
}

void MainWindow::on_rom_clicked() {
    Gtk::MessageDialog rom(*this, "How to get ROM", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);

    rom.set_secondary_text("To download stock ROM for NOKIA 7.1 visit https://raghuvarma331.github.io/Nokia-SDM660-Stock-ROMS/");

    rom.run();
}

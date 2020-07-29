#include "../include/mainwindow.hpp"

namespace KonstantIMP {

MainWindow::MainWindow() : log_file(log_name, std::ios_base::app) , logger(&log_file), term(KonstantIMP::os) {
    this->set_title("Nokia7.1 Stock Rom Flasher");
    this->set_icon(Gdk::Pixbuf::create_from_resource("/nokia/logo.png"));

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
    get_info_btn.set_label("Get info");

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
    main_grid.attach(get_info_btn, 6, 2, 3, 1);

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
    flash_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_flash_clicked));

    get_adb_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_get_adb_clicked));
    get_rom_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_get_rom_clicked));
    get_info_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_get_info_clicked));

    set_adb_path_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_set_adb_path_clicked));
    set_rom_path_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_set_rom_path_clicked));
}

void MainWindow::on_flash_clicked() {
    flash_load.set_fraction(0.f);

    if(adb_path_en.get_text() == "") {
        logger.make_record("[ERROR] You must set PATH to ADB");
        return;
    }

    if(os == "WINDOWS") {
        std::ifstream checker;

        checker.open(adb_path_en.get_text() + "\\adb.exe", std::ios_base::in | std::ios_base::binary);
        if(!checker.is_open()) {
            logger.make_record("[ERROR] Can\'t find adb.exe");
            return;
        } checker.close();

        checker.open(adb_path_en.get_text() + "\\fastboot.exe", std::ios_base::in | std::ios_base::binary);
        if(!checker.is_open()) {
            logger.make_record("[ERROR] Can\'t find fastboot.exe");
            return;
        } checker.close();
    }

    logger.make_record("platform-tools was founded");
}

void MainWindow::on_get_adb_clicked() {
    Gtk::MessageDialog get_adb(*this, "How to get ADB", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);

    if(os == " LINUX ") {
        get_adb.set_secondary_text("<b>Hello!</b>\r\n"
                                   "I see, you don\' know how you can get <i>ADB</i>\r\n"
                                   "You use <i>Linux</i> and need download <i>platform-tools</i> "
                                   "from <a href=\"https://clck.ru/Px6a7\">official ADB website</a> or do it using your packet manager\r\n"
                                   "The app will automaticly find ADB in the PATH", true);
    }
    else {
        get_adb.set_secondary_text("<b>Hello!</b>\r\n"
                                   "I see, you don\' know how you can get <i>ADB</i>\r\n"
                                   "You use <i>Windows</i> and need download <i>platform-tools</i> "
                                   "from <a href=\"https://clck.ru/Px6a7\">official ADB website</a>\r\n"
                                   "Download it and unarchive, than set PATH in the app", true);
    }

    get_adb.run();
}

void MainWindow::on_get_rom_clicked() {
    Gtk::MessageDialog get_rom(*this, "Where you can find stock ROM", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);

    get_rom.set_secondary_text("<b>Hello!</b>\r\n"
                               "To flash your Nokia 7.1 you need download <i>stock ROM</i>\r\n"
                               "You can download it from <a href=\"https://clck.ru/PxCLZ\">this website</a>\r\n"
                               "Unarchive it adn set ROM PATH to it", true);

    get_rom.run();
}

void MainWindow::on_get_info_clicked() {
    Gtk::AboutDialog about;
    about.set_transient_for(*this);

    about.set_license("LGPL");
    about.set_version("1.0.2");
    about.set_copyright("KonstantIMP");
    about.set_website_label("Github project repository");
    about.set_program_name("nokia7.1_stock_rom_flasher");
    about.set_authors(std::vector<Glib::ustring>{"KonstantIMP"});
    about.set_logo(Gdk::Pixbuf::create_from_resource("/nokia/logo.png"));
    about.set_comments("This is an app to flash your Nokia 7.1 to stock rom");
    about.set_website("https://github.com/KonstantIMP/nokia7.1_stock_rom_flasher");

    about.run();
}

void MainWindow::on_set_adb_path_clicked() {
    Gtk::FileChooserDialog adb_path(*this, "Set ADB path", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    adb_path.add_button("Cancel", Gtk::RESPONSE_NO);
    adb_path.add_button("OK", Gtk::RESPONSE_OK);

    if(adb_path.run() == Gtk::RESPONSE_OK) adb_path_en.set_text(adb_path.get_filename());
}

void MainWindow::on_set_rom_path_clicked() {
    Gtk::FileChooserDialog rom_path(*this, "Set ROM path", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    rom_path.add_button("Cancel", Gtk::RESPONSE_NO);
    rom_path.add_button("OK", Gtk::RESPONSE_OK);

    if(rom_path.run() == Gtk::RESPONSE_OK) rom_path_en.set_text(rom_path.get_filename());
}

};

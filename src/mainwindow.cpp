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
    flash_btn.set_sensitive(false);
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
            flash_btn.set_sensitive();
            return;
        } checker.close();

        checker.open(adb_path_en.get_text() + "\\fastboot.exe", std::ios_base::in | std::ios_base::binary);
        if(!checker.is_open()) {
            logger.make_record("[ERROR] Can\'t find fastboot.exe");
            flash_btn.set_sensitive();
            return;
        } checker.close();
    }

    flash_load.set_fraction(0.01);
    logger.make_record("platform-tools was founded");

    if(rom_path_en.get_text() == "") {
        logger.make_record("[ERROR] You must set PATH to ROM");
        flash_btn.set_sensitive();
        return;
    }

    logger.make_record("Checking images");

    std::array<std::string, 23> images {
        "abl.img", "bluetooth.img", "boot.img",
        "cda.img", "cmnlib64.img", "cmnlib.img",
        "devcfg.img", "dsp.img", "hidden.img",
        "hyp.img", "keymaster.img", "mdtp.img",
        "mdtpsecapp.img", "modem.img", "nvdef.img",
        "pmic.img", "rpm.img", "splash.img",
        "system.img", "systeminfo.img", "tz.img",
        "vendor.img", "xbl.img"
    };

    for(std::size_t i{0}; i < images.size(); i++) {
        std::ifstream checker(rom_path_en.get_text() + dir_sym + images[i], std::ios_base::in | std::ios_base::binary);
        if(!checker.is_open()) {
            logger.make_record(std::to_string(i + 1) + '/' + std::to_string(images.size()) + ' ' + images[i] + " - not found");
            flash_btn.set_sensitive();
            checker.close(); return;
        } checker.close();
        logger.make_record(std::to_string(i) + '/' + std::to_string(images.size()) + ' ' + images[i] + " - found");
    }

    flash_load.set_fraction(0.05);
    logger.make_record("Checking done");

    std::string adb = "", fastboot = "";

    if(os == " LINUX ") {
        fastboot = "sudo fastboot";
        adb = "sudo adb";
    }
    else {
        fastboot = adb_path_en.get_text() + "\\fastboot.exe";
        adb = adb_path_en.get_text() + "\\adb.exe";
    }

    flash_load.set_fraction(0.07);

    logger.make_record("Flashing abl_a");
    term.run_process(fastboot + " flash abl_a " + rom_path_en.get_text() + dir_sym + "abl.img");


    logger.make_record("Flashing abl_b");
    term.run_process(fastboot + " flash abl_b " + rom_path_en.get_text() + dir_sym + "abl.img");


    logger.make_record("Flashing xbl_a");
    term.run_process(fastboot + " flash xbl_a " + rom_path_en.get_text() + dir_sym + "xbl.img");


    logger.make_record("Flashing xbl_b");
    term.run_process(fastboot + " flash xbl_b " + rom_path_en.get_text() + dir_sym + "xbl.img");


    logger.make_record("Flashing bluetooth_a");
    term.run_process(fastboot + " flash bluetooth_a " + rom_path_en.get_text() + dir_sym + "bluetooth.img");


    logger.make_record("Flashing boot_a");
    term.run_process(fastboot + " flash boot_a " + rom_path_en.get_text() + dir_sym + "boot.img");


    logger.make_record("Flashing cda_a");
    term.run_process(fastboot + " flash cda_a " + rom_path_en.get_text() + dir_sym + "cda.img");


    logger.make_record("Flashing cmnlib_a");
    term.run_process(fastboot + " flash cmnlib_a " + rom_path_en.get_text() + dir_sym + "cmnlib.img");


    logger.make_record("Flashing cmnlib64_a");
    term.run_process(fastboot + " flash cmnlib64_a " + rom_path_en.get_text() + dir_sym + "cmnlib64.img");


    logger.make_record("Flashing devcfg_a");
    term.run_process(fastboot + " flash devcfg_a " + rom_path_en.get_text() + dir_sym + "devcfg.img");


    logger.make_record("Flashing dsp_a");
    term.run_process(fastboot + " flash dsp_a " + rom_path_en.get_text() + dir_sym + "dsp.img");


    logger.make_record("Flashing hidden_a");
    term.run_process(fastboot + " flash hidden_a " + rom_path_en.get_text() + dir_sym + "hidden.img");


    logger.make_record("Flashing hyp_a");
    term.run_process(fastboot + " flash hyp_a " + rom_path_en.get_text() + dir_sym + "hyp.img");


    logger.make_record("Flashing keymaster_a");
    term.run_process(fastboot + " flash keymaster_a " + rom_path_en.get_text() + dir_sym + "keymaster.img");


    logger.make_record("Flashing mdtp_a");
    term.run_process(fastboot + " flash mdtp_a " + rom_path_en.get_text() + dir_sym + "mdtp.img");


    logger.make_record("Flashing mdtpsecapp_a");
    term.run_process(fastboot + " flash mdtpsecapp_a " + rom_path_en.get_text() + dir_sym + "mdtpsecapp.img");


    logger.make_record("Flashing modem_a");
    term.run_process(fastboot + " flash modem_a " + rom_path_en.get_text() + dir_sym + "modem.img");


    logger.make_record("Flashing nvdef_a");
    term.run_process(fastboot + " flash nvdef_a " + rom_path_en.get_text() + dir_sym + "nvdef.img");


    logger.make_record("Flashing pmic_a");
    term.run_process(fastboot + " flash pmic_a " + rom_path_en.get_text() + dir_sym + "pmic.img");


    logger.make_record("Flashing rpm_a");
    term.run_process(fastboot + " flash rpm_a " + rom_path_en.get_text() + dir_sym + "rpm.img");


    logger.make_record("Flashing splash_a");
    term.run_process(fastboot + " flash splash_a " + rom_path_en.get_text() + dir_sym + "splash.img");


    logger.make_record("Flashing system_a");
    term.run_process(fastboot + " flash system_a " + rom_path_en.get_text() + dir_sym + "system.img");


    logger.make_record("Flashing systeminfo_a");
    term.run_process(fastboot + " flash systeminfo_a " + rom_path_en.get_text() + dir_sym + "systeminfo.img");


    logger.make_record("Flashing tz_a");
    term.run_process(fastboot + " flash tz_a " + rom_path_en.get_text() + dir_sym + "tz.img");


    logger.make_record("Flashing vendor_a");
    term.run_process(fastboot + " flash vendor_a " + rom_path_en.get_text() + dir_sym + "vendor.img");


    logger.make_record("Erasing ssd");
    term.run_process(fastboot + " erase ssd");


    logger.make_record("Erasing misc");
    term.run_process(fastboot + " erase misc");


    logger.make_record("Erasing sti");
    term.run_process(fastboot + " erase sti");


    logger.make_record("Erasing ddr");
    term.run_process(fastboot + " erase ddr");


    logger.make_record("Erasing securefs");
    term.run_process(fastboot + " erase securefs");


    logger.make_record("Erasing box");
    term.run_process(fastboot + " erase box");


    logger.make_record("Erasing boot_b");
    term.run_process(fastboot + " erase boot_b");


    logger.make_record("Set \'A\' as active slot");
    term.run_process(fastboot + " --set-active=a");


    logger.make_record("Factory reset");
    term.run_process(fastboot + " -w");


    logger.make_record("Reboot");
    term.run_process(fastboot + " reboot");


    logger.make_record("Flashing done");


    flash_load.set_fraction(1.f);
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

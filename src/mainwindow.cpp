#include "mainwindow.hpp"

#include <cstddef>

#include <string>

#include <array>

#ifdef __linux
    const std::string prf = "[ LINUX ]";
#else
    const std::string prf = "[WINDOWS]";
#endif

MainWindow::MainWindow() : logger(&log, &log_text) {
    this->set_title("Nokia 7.1 stock rom flasher");
    this->set_icon(Gdk::Pixbuf::create_from_resource("/nokia/icons8-circled-n-50.png"));

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

    logger.make_record("Programm started");

    if(prf == "[ LINUX ]") {
        logger.make_record("You use linux. ADB will be finded in the PATH");

        adb_en.set_text("PATH");
        adb_en.set_editable(false);

        set_adb_btn.set_can_focus(false);
        set_adb_btn.set_visible(false);
    }

    this->connect_sig();

    term.print_message("Set your phone to Download mode");
}

MainWindow::~MainWindow() {
    logger.make_record("Programm closed");

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

    info_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_help_clicked));

    set_adb_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::set_adb_path));
    set_rom_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::set_rom_path));

    flash_btn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::start_flash));
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

void MainWindow::on_help_clicked() {
    Gtk::MessageDialog help(*this, "Help", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);

    help.set_secondary_text("The programm was made using GTKMM and its license is LGPLv3\n\nDeveloper : KonstantIMP (mihedovkos@gmail.com)");

    help.run();
}

void MainWindow::set_adb_path() {
    if(prf == "[ LINUX ]") {
        logger.make_record("You don\'t need set ADB path");

        return;
    }

    Gtk::FileChooserDialog a(*this, "Set ROM PATH", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    a.add_button("OK", Gtk::RESPONSE_OK);
    a.add_button("Cancel", Gtk::BUTTONS_CANCEL);

    if(a.run() == Gtk::RESPONSE_OK) {
        adb_en.set_text(a.get_filename());
    }
}

void MainWindow::set_rom_path() {
    Gtk::FileChooserDialog a(*this, "Set ROM PATH", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    a.add_button("OK", Gtk::RESPONSE_OK);
    a.add_button("Cancel", Gtk::BUTTONS_CANCEL);

    if(a.run() == Gtk::RESPONSE_OK) {
        rom_en.set_text(a.get_filename());
    }
}

void MainWindow::start_flash() {
    Glib::ustring fastboot = "", adb = "";

    std::ifstream checker;

    load_bar.set_fraction(0.f);

    logger.make_record("Flash started");

    if(prf == "[ LINUX ]") {
        fastboot = "sudo fastboot";
        adb = "adb";
    }
    else {
        fastboot = adb_en.get_text() + "/fastboot.exe";
        adb = adb_en.get_text() + "/adb.exe";

        if(adb_en.get_text() == "") {
            adb = "adb.exe";
            fastboot = "fastboot.exe";
        }

        checker.open(adb);
        if(!checker.is_open()) {
            logger.make_record("[ERROR] can\'t find ADB");

            return;
        }
        checker.close();

        checker.open(fastboot);
        if(!checker.is_open()) {
            logger.make_record("[ERROR] can\'t find FASTBOOT");

            checker.close();

            return;
        }
        checker.close();
    }

    load_bar.set_fraction(0.01);

    std::array<std::string, 23> images {"abl.img", "xbl.img", "bluetooth.img",
                                         "boot.img", "cda.img", "cmnlib.img",
                                         "cmnlib64.img", "devcfg.img", "dsp.img",
                                         "hidden.img", "hyp.img", "keymaster.img",
                                         "mdtp.img", "mdtpsecapp.img", "modem.img",
                                         "nvdef.img", "pmic.img", "rpm.img",
                                         "splash.img", "system.img", "systeminfo.img",
                                         "tz.img", "vendor.img"};

    for(std::size_t i{0}; i < images.size(); i++) {
        checker.open(rom_en.get_text() + "/" + images[i]);

        if(!checker.is_open()) {
            logger.make_record("[ERROR] checking " + std::to_string(i + 1) + '/' + std::to_string(images.size()) + ' ' + images[i] + " - not founded");

            checker.close();

            return;
        }

        logger.make_record("Checking " + std::to_string(i + 1) + '/' + std::to_string(images.size()) + ' ' + images[i] + " - founded");

        checker.close();
    }

    load_bar.set_fraction(0.09);

    logger.make_record("Work with fastboot");

    logger.make_record("Flash abl_a");
    term.run_process(fastboot + " flash abl_a \"" + rom_en.get_text() + "/abl.img\"");

    load_bar.set_fraction(0.13);

    logger.make_record("Flash abl_b");
    term.run_process(fastboot + " flash abl_b \"" + rom_en.get_text() + "/abl.img\"");

    load_bar.set_fraction(0.15);

    logger.make_record("Flash xbl_a");
    term.run_process(fastboot + " flash xbl_a \"" + rom_en.get_text() + "/xbl.img\"");

    load_bar.set_fraction(0.17);

    logger.make_record("Flash xbl_b");
    term.run_process(fastboot + " flash xbl_b \"" + rom_en.get_text() + "/xbl.img\"");

    load_bar.set_fraction(0.20);

    logger.make_record("Flash bluetooth_a");
    term.run_process(fastboot + " flash bluetooth_a \"" + rom_en.get_text() + "/bluetooth.img\"");

    load_bar.set_fraction(0.21);

    logger.make_record("Flash boot_a");
    term.run_process(fastboot + " flash boot_a \"" + rom_en.get_text() + "/boot.img\"");

    load_bar.set_fraction(0.22);

    logger.make_record("Flash cda_a");
    term.run_process(fastboot + " flash cda_a \"" + rom_en.get_text() + "/cda.img\"");

    load_bar.set_fraction(0.23);

    logger.make_record("Flash cmnlib_a");
    term.run_process(fastboot + " flash cmnlib_a \"" + rom_en.get_text() + "/cmnlib.img\"");

    load_bar.set_fraction(0.25);

    logger.make_record("Flash cmnlib64_a");
    term.run_process(fastboot + " flash cmnlib64_a \"" + rom_en.get_text() + "/cmnlib64.img\"");

    load_bar.set_fraction(0.26);

    logger.make_record("Flash devcfg_a");
    term.run_process(fastboot + " flash devcfg_a \"" + rom_en.get_text() + "/devcfg.img\"");

    load_bar.set_fraction(0.28);

    logger.make_record("Flash dsp_a");
    term.run_process(fastboot + " flash dsp_a \"" + rom_en.get_text() + "/dsp.img\"");

    load_bar.set_fraction(0.29);

    logger.make_record("Flash hidden_a");
    term.run_process(fastboot + " flash hidden_a \"" + rom_en.get_text() + "/hidden.img\"");

    load_bar.set_fraction(0.31);

    logger.make_record("Flash hyp_a");
    term.run_process(fastboot + " flash hyp_a \"" + rom_en.get_text() + "/hyp.img\"");

    load_bar.set_fraction(0.32);

    logger.make_record("Flash keymaster_a");
    term.run_process(fastboot + " flash keymaster_a \"" + rom_en.get_text() + "/keymaster.img\"");

    load_bar.set_fraction(0.35);

    logger.make_record("Flash mdtp_a");
    term.run_process(fastboot + " flash mdtp_a \"" + rom_en.get_text() + "/mdtp.img\"");

    load_bar.set_fraction(0.37);

    logger.make_record("Flash mdtpsecapp_a");
    term.run_process(fastboot + " flash mdtpsecapp_a \"" + rom_en.get_text() + "/mdtpsecapp.img\"");

    load_bar.set_fraction(0.40);

    logger.make_record("Flash modem_a");
    term.run_process(fastboot + " flash modem_a \"" + rom_en.get_text() + "/modem.img\"");

    load_bar.set_fraction(0.41);

    logger.make_record("Flash nvdef_a");
    term.run_process(fastboot + " flash nvdef_a \"" + rom_en.get_text() + "/nvdef.img\"");

    load_bar.set_fraction(0.43);

    logger.make_record("Flash pmic_a");
    term.run_process(fastboot + " flash pmic_a \"" + rom_en.get_text() + "/pmic.img\"");

    load_bar.set_fraction(0.46);

    logger.make_record("Flash rpm_a");
    term.run_process(fastboot + " flash rpm_a \"" + rom_en.get_text() + "/rpm.img\"");

    load_bar.set_fraction(0.48);

    logger.make_record("Flash splash_a");
    term.run_process(fastboot + " flash splash_a \"" + rom_en.get_text() + "/splash.img\"");

    load_bar.set_fraction(0.50);

    logger.make_record("Flash system_a");
    term.run_process(fastboot + " flash system_a \"" + rom_en.get_text() + "/system.img\"");

    load_bar.set_fraction(0.70);

    logger.make_record("Flash systeminfo_a");
    term.run_process(fastboot + " flash systeminfo_a \"" + rom_en.get_text() + "/systeminfo.img\"");

    load_bar.set_fraction(0.73);

    logger.make_record("Flash tz_a");
    term.run_process(fastboot + " flash tz_a \"" + rom_en.get_text() + "/tz.img\"");

    load_bar.set_fraction(0.75);

    logger.make_record("Flash vendor_a");
    term.run_process(fastboot + " flash vendor_a \"" + rom_en.get_text() + "/vendor.img\"");

    load_bar.set_fraction(0.80);

    logger.make_record("Erase ssd");
    term.run_process(fastboot + " erase ssd ");

    logger.make_record("Erase misc");
    term.run_process(fastboot + " erase misc ");

    load_bar.set_fraction(0.83);

    logger.make_record("Erase sti");
    term.run_process(fastboot + " erase sti ");

    load_bar.set_fraction(0.85);

    logger.make_record("Erase ddr");
    term.run_process(fastboot + " erase ddr ");

    logger.make_record("Erase securefs");
    term.run_process(fastboot + " erase securefs ");

    logger.make_record("Erase box");
    term.run_process(fastboot + " erase box ");

    load_bar.set_fraction(0.87);

    logger.make_record("Erase boot_b");
    term.run_process(fastboot + " erase boot_b ");

    load_bar.set_fraction(0.90);

    logger.make_record("Set \'A\' as active slot");
    term.run_process(fastboot + " --set-active=a");

    load_bar.set_fraction(0.95);

    logger.make_record("Factory reset");
    term.run_process(fastboot + " -w");

    load_bar.set_fraction(0.99);

    logger.make_record("Reboot");
    term.run_process(fastboot + " reboot");

    logger.make_record("Flash finished");

    load_bar.set_fraction(1.f);
}

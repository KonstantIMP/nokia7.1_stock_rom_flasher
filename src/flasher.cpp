#include "../include/flasher.hpp"

Flasher::Flasher(TerminalView * t, std::ofstream * l, Gtk::TextView * lt) : term(t), log(l), log_text(lt), fraction(0), mtx() {}

double Flasher::get_fraction() {
    mtx.lock();

    double res = fraction;

    mtx.unlock();

    return res;
}

void Flasher::do_work(const Glib::ustring & adb_en, const Glib::ustring & rom_en) {
    Glib::ustring fastboot = "", adb = "";

    std::ifstream checker;

    fraction = 0.f;

    *log << "[LOG] Flash started\r\n";
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash started\r\n");

    if(prf == "[ LINUX ]") {
        fastboot = "sudo fastboot";
        adb = "adb";
    }
    else {
        fastboot = adb_en + "/fastboot.exe";
        adb = adb_en + "/adb.exe";

        if(adb_en == "") {
            adb = "adb.exe";
            fastboot = "fastboot.exe";
        }

        checker.open(adb);
        if(!checker.is_open()) {
            *log << "[LOG] [ERROR] can\'t find ADB\r\n";
            log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] [ERROR] can\'t find ADB\r\n");

            return;
        }
        checker.close();

        checker.open(fastboot);
        if(!checker.is_open()) {
            *log << "[LOG] [ERROR] can\'t find FASTBOOT\r\n";
            log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] [ERROR] can\'t find FASTBOOT\r\n");

            checker.close();

            return;
        }
        checker.close();
    }

    fraction = 0.01;

    std::array<Glib::ustring, 23> images {"abl.img", "xbl.img", "bluetooth.img",
                                         "boot.img", "cda.img", "cmnlib.img",
                                         "cmnlib64.img", "devcfg.img", "dsp.img",
                                         "hidden.img", "hyp.img", "keymaster.img",
                                         "mdtp.img", "mdtpsecapp.img", "modem.img",
                                         "nvdef.img", "pmic.img", "rpm.img",
                                         "splash.img", "system.img", "systeminfo.img",
                                         "tz.img", "vendor.img"};

    for(std::size_t i{0}; i < images.size(); i++) {
        checker.open(rom_en + "/" + images[i]);

        if(!checker.is_open()) {
            *log << "[LOG] [ERROR] checking " << i + 1 << '/' + images.size() << ' ' << images[i] << " - not founded\r\n";
            log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] [ERROR] checking " + std::to_string(i + 1) + '/' + std::to_string(images.size()) + ' ' + images[i] + " - not founded\r\n");

            checker.close();

            return;
        }

        *log << "[LOG] checking " << i + 1 << '/' + images.size() << ' ' << images[i] << " - founded\r\n";
        log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] checking " + std::to_string(i + 1) + '/' + std::to_string(images.size()) + ' ' + images[i] + " - founded\r\n");

        checker.close();
    }

    fraction = 0.09;

    *log << "[LOG] Work with fastboot\r\n";
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Work with fastboot\r\n");

    *log << "[LOG] Flash abl_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash abl_a\r\n");
    term.run_process(fastboot + " flash abl_a \"" + rom_en.get_text() + "/abl.img\"");

    load_bar.set_fraction(0.13);

    *log << "[LOG] Flash abl_b\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash abl_b\r\n");
    term.run_process(fastboot + " flash abl_b \"" + rom_en.get_text() + "/abl.img\"");

    load_bar.set_fraction(0.15);

    *log << "[LOG] Flash xbl_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash xbl_a\r\n");
    term.run_process(fastboot + " flash xbl_a \"" + rom_en.get_text() + "/xbl.img\"");

    load_bar.set_fraction(0.17);

    *log << "[LOG] Flash xbl_b\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash xbl_b\r\n");
    term.run_process(fastboot + " flash xbl_b \"" + rom_en.get_text() + "/xbl.img\"");

    load_bar.set_fraction(0.20);

    *log << "[LOG] Flash bluetooth_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash bluetooth_a\r\n");
    term.run_process(fastboot + " flash bluetooth_a \"" + rom_en.get_text() + "/bluetooth.img\"");

    load_bar.set_fraction(0.21);

    *log << "[LOG] Flash boot_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash boot_a\r\n");
    term.run_process(fastboot + " flash boot_a \"" + rom_en.get_text() + "/boot.img\"");

    load_bar.set_fraction(0.22);

    *log << "[LOG] Flash cda_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash cda_a\r\n");
    term.run_process(fastboot + " flash cda_a \"" + rom_en.get_text() + "/cda.img\"");

    load_bar.set_fraction(0.23);

    *log << "[LOG] Flash cmnlib_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash cmnlib_a\r\n");
    term.run_process(fastboot + " flash cmnlib_a \"" + rom_en.get_text() + "/cmnlib.img\"");

    load_bar.set_fraction(0.25);

    *log << "[LOG] Flash cmnlib64_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash cmnlib64_a\r\n");
    term.run_process(fastboot + " flash cmnlib64_a \"" + rom_en.get_text() + "/cmnlib64.img\"");

    load_bar.set_fraction(0.26);

    *log << "[LOG] Flash devcfg_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash devcfg_a\r\n");
    term.run_process(fastboot + " flash devcfg_a \"" + rom_en.get_text() + "/devcfg.img\"");

    load_bar.set_fraction(0.28);

    *log << "[LOG] Flash dsp_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash dsp_a\r\n");
    term.run_process(fastboot + " flash dsp_a \"" + rom_en.get_text() + "/dsp.img\"");

    load_bar.set_fraction(0.29);

    *log << "[LOG] Flash hidden_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash hidden_a\r\n");
    term.run_process(fastboot + " flash hidden_a \"" + rom_en.get_text() + "/hidden.img\"");

    load_bar.set_fraction(0.31);

    *log << "[LOG] Flash hyp_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash hyp_a\r\n");
    term.run_process(fastboot + " flash hyp_a \"" + rom_en.get_text() + "/hyp.img\"");

    load_bar.set_fraction(0.32);

    *log << "[LOG] Flash keymaster_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash keymaster_a\r\n");
    term.run_process(fastboot + " flash keymaster_a \"" + rom_en.get_text() + "/keymaster.img\"");

    load_bar.set_fraction(0.35);

    *log << "[LOG] Flash mdtp_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash mdtp_a\r\n");
    term.run_process(fastboot + " flash mdtp_a \"" + rom_en.get_text() + "/mdtp.img\"");

    load_bar.set_fraction(0.37);

    *log << "[LOG] Flash mdtpsecapp_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash mdtpsecapp_a\r\n");
    term.run_process(fastboot + " flash mdtpsecapp_a \"" + rom_en.get_text() + "/mdtpsecapp.img\"");

    load_bar.set_fraction(0.40);

    *log << "[LOG] Flash modem_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash modem_a\r\n");
    term.run_process(fastboot + " flash modem_a \"" + rom_en.get_text() + "/modem.img\"");

    load_bar.set_fraction(0.41);

    *log << "[LOG] Flash nvdef_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash nvdef_a\r\n");
    term.run_process(fastboot + " flash nvdef_a \"" + rom_en.get_text() + "/nvdef.img\"");

    load_bar.set_fraction(0.43);

    *log << "[LOG] Flash pmic_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash pmic_a\r\n");
    term.run_process(fastboot + " flash pmic_a \"" + rom_en.get_text() + "/pmic.img\"");

    load_bar.set_fraction(0.46);

    *log << "[LOG] Flash rpm_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash rpm_a\r\n");
    term.run_process(fastboot + " flash rpm_a \"" + rom_en.get_text() + "/rpm.img\"");

    load_bar.set_fraction(0.48);

    *log << "[LOG] Flash splash_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash splash_a\r\n");
    term.run_process(fastboot + " flash splash_a \"" + rom_en.get_text() + "/splash.img\"");

    load_bar.set_fraction(0.50);

    *log << "[LOG] Flash system_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash system_a\r\n");
    term.run_process(fastboot + " flash system_a \"" + rom_en.get_text() + "/system.img\"");

    load_bar.set_fraction(0.70);

    *log << "[LOG] Flash systeminfo_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash systeminfo_a\r\n");
    term.run_process(fastboot + " flash systeminfo_a \"" + rom_en.get_text() + "/systeminfo.img\"");

    load_bar.set_fraction(0.73);

    *log << "[LOG] Flash tz_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash tz_a\r\n");
    term.run_process(fastboot + " flash tz_a \"" + rom_en.get_text() + "/tz.img\"");

    load_bar.set_fraction(0.75);

    *log << "[LOG] Flash vendor_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash vendor_a\r\n");
    term.run_process(fastboot + " flash vendor_a \"" + rom_en.get_text() + "/vendor.img\"");

    load_bar.set_fraction(0.80);

    *log << "[LOG] Erase ssd\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase ssd\r\n");
    term.run_process(fastboot + " erase ssd ");

    *log << "[LOG] Erase misc\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase misc\r\n");
    term.run_process(fastboot + " erase misc ");

    load_bar.set_fraction(0.83);

    *log << "[LOG] Erase sti\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase sti\r\n");
    term.run_process(fastboot + " erase sti ");

    load_bar.set_fraction(0.85);

    *log << "[LOG] Erase ddr\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase ddr\r\n");
    term.run_process(fastboot + " erase ddr ");

    *log << "[LOG] Erase securefs\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase securefs\r\n");
    term.run_process(fastboot + " erase securefs ");

    *log << "[LOG] Erase box\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase box\r\n");
    term.run_process(fastboot + " erase box ");

    load_bar.set_fraction(0.87);

    *log << "[LOG] Erase boot_b\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase boot_b\r\n");
    term.run_process(fastboot + " erase boot_b ");

    load_bar.set_fraction(0.90);

    *log << "[LOG] Set \'A\' as active slot\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Set \'A\' as active slot\r\n");
    term.run_process(fastboot + " --set-active=a");

    load_bar.set_fraction(0.95);

    *log << "[LOG] Factory reset\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Factory reset\r\n");
    term.run_process(fastboot + " -w");

    load_bar.set_fraction(0.99);

    *log << "[LOG] Reboot\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Reboot\r\n");
    term.run_process(fastboot + " reboot");

    *log << "[LOG] Flash finished\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash finished\r\n");

    load_bar.set_fraction(1.f);
}

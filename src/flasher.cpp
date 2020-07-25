#include "../include/flasher.hpp"

#include <iostream>

Flasher::Flasher(TerminalView * t, std::ofstream * l, Gtk::TextView * lt) : term(t), log(l), log_text(lt), fraction(0), mtx() {}

double Flasher::get_fraction() {
    mtx.lock();

    double res = fraction;

    mtx.unlock();

    return res;
}

void Flasher::do_work(const Glib::ustring & adb_en, const Glib::ustring & rom_en, Glib::Dispatcher * d) {
    std::cout << "Ok";

    Glib::ustring fastboot = "", adb = "";

    std::ifstream checker;

    mtx.lock();

    fraction = 0.f;

    mtx.unlock();

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

            d->emit();

            return;
        }
        checker.close();

        checker.open(fastboot);
        if(!checker.is_open()) {
            *log << "[LOG] [ERROR] can\'t find FASTBOOT\r\n";
            log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] [ERROR] can\'t find FASTBOOT\r\n");

            checker.close();

            d->emit();

            return;
        }
        checker.close();
    }

    mtx.lock();

    fraction = 0.01;

    mtx.unlock();

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

            d->emit();

            return;
        }

        *log << "[LOG] checking " << i + 1 << '/' + images.size() << ' ' << images[i] << " - founded\r\n";
        log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] checking " + std::to_string(i + 1) + '/' + std::to_string(images.size()) + ' ' + images[i] + " - founded\r\n");

        checker.close();
    }

    mtx.lock();

    fraction = 0.09;

    mtx.unlock();

    *log << "[LOG] Work with fastboot\r\n";
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Work with fastboot\r\n");

    *log << "[LOG] Flash abl_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash abl_a\r\n");
    term->run_process(fastboot + " flash abl_a \"" + rom_en + "/abl.img\"");

    mtx.lock();

    fraction = 0.13;

    mtx.unlock();

    *log << "[LOG] Flash abl_b\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash abl_b\r\n");
    term->run_process(fastboot + " flash abl_b \"" + rom_en + "/abl.img\"");

    mtx.lock();

    fraction = 0.15;

    mtx.unlock();

    *log << "[LOG] Flash xbl_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash xbl_a\r\n");
    term->run_process(fastboot + " flash xbl_a \"" + rom_en + "/xbl.img\"");

    mtx.lock();

    fraction = 0.17;

    mtx.unlock();

    *log << "[LOG] Flash xbl_b\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash xbl_b\r\n");
    term->run_process(fastboot + " flash xbl_b \"" + rom_en + "/xbl.img\"");

    mtx.lock();

    fraction = 0.20;

    mtx.unlock();

    *log << "[LOG] Flash bluetooth_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash bluetooth_a\r\n");
    term->run_process(fastboot + " flash bluetooth_a \"" + rom_en + "/bluetooth.img\"");

    mtx.lock();

    fraction = 0.21;

    mtx.unlock();

    *log << "[LOG] Flash boot_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash boot_a\r\n");
    term->run_process(fastboot + " flash boot_a \"" + rom_en + "/boot.img\"");

    mtx.lock();

    fraction = 0.22;

    mtx.unlock();

    *log << "[LOG] Flash cda_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash cda_a\r\n");
    term->run_process(fastboot + " flash cda_a \"" + rom_en + "/cda.img\"");

    mtx.lock();

    fraction = 0.23;

    mtx.unlock();

    *log << "[LOG] Flash cmnlib_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash cmnlib_a\r\n");
    term->run_process(fastboot + " flash cmnlib_a \"" + rom_en + "/cmnlib.img\"");

    mtx.lock();

    fraction = 0.25;

    mtx.unlock();

    *log << "[LOG] Flash cmnlib64_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash cmnlib64_a\r\n");
    term->run_process(fastboot + " flash cmnlib64_a \"" + rom_en + "/cmnlib64.img\"");

    mtx.lock();

    fraction = 0.26;

    mtx.unlock();

    *log << "[LOG] Flash devcfg_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash devcfg_a\r\n");
    term->run_process(fastboot + " flash devcfg_a \"" + rom_en + "/devcfg.img\"");

    mtx.lock();

    fraction = (0.28);

    mtx.unlock();

    *log << "[LOG] Flash dsp_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash dsp_a\r\n");
    term->run_process(fastboot + " flash dsp_a \"" + rom_en + "/dsp.img\"");

    mtx.lock();

    fraction = (0.29);

    mtx.unlock();

    *log << "[LOG] Flash hidden_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash hidden_a\r\n");
    term->run_process(fastboot + " flash hidden_a \"" + rom_en + "/hidden.img\"");

    mtx.lock();

    fraction = (0.31);

    mtx.unlock();

    *log << "[LOG] Flash hyp_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash hyp_a\r\n");
    term->run_process(fastboot + " flash hyp_a \"" + rom_en + "/hyp.img\"");

    mtx.lock();

    fraction = (0.32);

    mtx.unlock();

    *log << "[LOG] Flash keymaster_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash keymaster_a\r\n");
    term->run_process(fastboot + " flash keymaster_a \"" + rom_en + "/keymaster.img\"");

    mtx.lock();

    fraction = (0.35);

    mtx.unlock();

    *log << "[LOG] Flash mdtp_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash mdtp_a\r\n");
    term->run_process(fastboot + " flash mdtp_a \"" + rom_en + "/mdtp.img\"");

    mtx.lock();

    fraction = (0.37);

    mtx.unlock();

    *log << "[LOG] Flash mdtpsecapp_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash mdtpsecapp_a\r\n");
    term->run_process(fastboot + " flash mdtpsecapp_a \"" + rom_en + "/mdtpsecapp.img\"");

    mtx.lock();

    fraction = (0.40);

    mtx.unlock();

    *log << "[LOG] Flash modem_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash modem_a\r\n");
    term->run_process(fastboot + " flash modem_a \"" + rom_en + "/modem.img\"");

    mtx.lock();

    fraction = (0.41);

    mtx.unlock();

    *log << "[LOG] Flash nvdef_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash nvdef_a\r\n");
    term->run_process(fastboot + " flash nvdef_a \"" + rom_en + "/nvdef.img\"");

    mtx.lock();

    fraction = (0.43);

    mtx.unlock();

    *log << "[LOG] Flash pmic_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash pmic_a\r\n");
    term->run_process(fastboot + " flash pmic_a \"" + rom_en + "/pmic.img\"");

    mtx.lock();

    fraction = (0.46);

    mtx.unlock();

    *log << "[LOG] Flash rpm_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash rpm_a\r\n");
    term->run_process(fastboot + " flash rpm_a \"" + rom_en + "/rpm.img\"");

    mtx.lock();

    fraction = (0.48);

    mtx.unlock();

    *log << "[LOG] Flash splash_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash splash_a\r\n");
    term->run_process(fastboot + " flash splash_a \"" + rom_en + "/splash.img\"");

    mtx.lock();

    fraction = (0.50);

    mtx.unlock();

    *log << "[LOG] Flash system_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash system_a\r\n");
    term->run_process(fastboot + " flash system_a \"" + rom_en + "/system.img\"");

    mtx.lock();

    fraction = (0.70);

    mtx.unlock();

    *log << "[LOG] Flash systeminfo_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash systeminfo_a\r\n");
    term->run_process(fastboot + " flash systeminfo_a \"" + rom_en + "/systeminfo.img\"");

    mtx.lock();

    fraction = (0.73);

    mtx.unlock();

    *log << "[LOG] Flash tz_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash tz_a\r\n");
    term->run_process(fastboot + " flash tz_a \"" + rom_en + "/tz.img\"");

    mtx.lock();

    fraction = (0.75);

    mtx.unlock();

    *log << "[LOG] Flash vendor_a\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash vendor_a\r\n");
    term->run_process(fastboot + " flash vendor_a \"" + rom_en + "/vendor.img\"");

    mtx.lock();

    fraction = (0.80);

    mtx.unlock();

    *log << "[LOG] Erase ssd\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase ssd\r\n");
    term->run_process(fastboot + " erase ssd ");

    *log << "[LOG] Erase misc\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase misc\r\n");
    term->run_process(fastboot + " erase misc ");

    mtx.lock();

    fraction = (0.83);

    mtx.unlock();

    *log << "[LOG] Erase sti\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase sti\r\n");
    term->run_process(fastboot + " erase sti ");

    mtx.lock();

    fraction = (0.85);

    mtx.unlock();

    *log << "[LOG] Erase ddr\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase ddr\r\n");
    term->run_process(fastboot + " erase ddr ");

    *log << "[LOG] Erase securefs\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase securefs\r\n");
    term->run_process(fastboot + " erase securefs ");

    *log << "[LOG] Erase box\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase box\r\n");
    term->run_process(fastboot + " erase box ");

    mtx.lock();

    fraction = (0.87);

    mtx.unlock();

    *log << "[LOG] Erase boot_b\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Erase boot_b\r\n");
    term->run_process(fastboot + " erase boot_b ");

    mtx.lock();

    fraction = (0.90);

    mtx.unlock();

    *log << "[LOG] Set \'A\' as active slot\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Set \'A\' as active slot\r\n");
    term->run_process(fastboot + " --set-active=a");

    mtx.lock();

    fraction = (0.95);

    mtx.unlock();

    *log << "[LOG] Factory reset\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Factory reset\r\n");
    term->run_process(fastboot + " -w");

    mtx.lock();

    fraction = (0.99);

    mtx.unlock();

    *log << "[LOG] Reboot\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Reboot\r\n");
    term->run_process(fastboot + " reboot");

    *log << "[LOG] Flash finished\r\n" << std::flush;
    log_text->get_buffer()->set_text(log_text->get_buffer()->get_text() + "[LOG] Flash finished\r\n");

    mtx.lock();

    fraction = (1.f);

    mtx.unlock();

    d->emit();
}

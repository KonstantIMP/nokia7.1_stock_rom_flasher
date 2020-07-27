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
}

void MainWindow::connect_signals()
{

}

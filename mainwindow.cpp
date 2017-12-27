#include <QFile>
#include <QTextStream>
#include <QProcess>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Parse from file
    QFile inputFile("/etc/version-adv");
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen())
        return;

    QTextStream stream(&inputFile);
    //Get bootloader version
    if (!stream.atEnd())
    {
        QString uboot = stream.readLine();
        uboot.prepend("Bootloader: ");
        ui->uboot->setText(uboot);
    }

    //Get rootfs version
    if (!stream.atEnd())
    {
        QString rootfs = stream.readLine();
        rootfs.prepend("Rootfs: ");
        ui->rootfs->setText(rootfs);
    }

    inputFile.close();

    //Get kernel version
    QProcess process; process.start("uname -r");
    process.waitForFinished(-1); // will wait forever until finished
    QString kernel = process.readAllStandardOutput();
    kernel.prepend("Kernel: ");
    ui->kernel->setText(kernel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

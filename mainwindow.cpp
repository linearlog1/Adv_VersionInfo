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
    QString uboot;
    QString version_a_digit;
    if (!stream.atEnd())
    {
        uboot = stream.readLine();
        version_a_digit = uboot;
        uboot.prepend("Bootloader: ");
        ui->uboot->setText(uboot);
    }

    //Get rootfs version (A/B/C/D)
    QString rootfs = "Rootfs: ";
    //Version Digit A (Bootloader Version)
    if (!version_a_digit.compare(QString("1Gram")))
    {
        //1Gram Bootloader
        rootfs.append("2");
    }
    else
    {
        //512Mram Bootloader
        rootfs.append("1");
    }
    rootfs.append("_");

    //Version Digit B (Build Date)
    if (!stream.atEnd())
    {
        QString version_b_digit = stream.readLine();
        rootfs.append(version_b_digit);
    }
    rootfs.append("_");

    //Version Digit C and D
    if (!stream.atEnd())
    {
        QString version_c_digit = stream.readLine();
        rootfs.append(version_c_digit);
    }
    if (!stream.atEnd())
    {
        QString version_d_digit = stream.readLine();
        rootfs.append(version_d_digit);
    }

    ui->rootfs->setText(rootfs);

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

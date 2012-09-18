#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <QTimer>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/version.h>
#include <linux/input.h>



static int ring_bell(int val)
{
        ssize_t s;
        struct input_event ev;
        int fd = open("/dev/input/beeper", O_WRONLY);
/*	ev.time = ??; TODO */
        ev.type = EV_SND;
        ev.code = SND_TONE;
        ev.value = val;	/* enable (ring) the bell */

        s = write(fd, &ev, sizeof(ev));
        if (s == -1) {
                perror("Writing bell event");
                return -1;
        }

        usleep(500 * 1000);	/* 100 ms */

        ev.value = 0;	/* stop bell from ringing */

        s = write(fd, &ev, sizeof(ev));
        if (s == -1) {
                perror("Writing bell event");
                return -1;
        }
        close(fd);
        return 1;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FILE *h = fopen("/sys/class/leds/led2/trigger", "w");
    fprintf(h, "timer\n");
    fclose(h);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_pressed()
{
    QMessageBox msgBox;
    msgBox.setText("Hello Here");
    msgBox.exec();

    ring_bell(5000);

}

void MainWindow::update()
{
    char str[5];

    FILE *adc = fopen("/sys/devices/platform/s3c24xx-adc/s3c-hwmon/in0_input","r");
    fscanf(adc,"%s",str);
    ui->label->setText(str);
    fclose(adc);

}

void MainWindow::on_radioButton_toggled(bool checked)
{
    FILE *h = fopen("/sys/class/leds/led1/brightness", "w");

    if(checked == TRUE)
        fprintf(h, "1\n");
    else
        fprintf(h, "0\n");

    fclose(h);

}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{

    QString str1;
    str1.setNum(position*10);

    FILE *on = fopen("/sys/class/leds/led2/delay_on", "w");
    fprintf(on, qPrintable(str1));

    FILE *off = fopen("/sys/class/leds/led2/delay_off", "w");
    fprintf(off, qPrintable(str1));

    fclose(off);
    fclose(on);
}



void MainWindow::on_dial_sliderMoved(int position)
{
    ring_bell(position);
}

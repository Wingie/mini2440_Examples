#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    system("stty -F /dev/ttyUSB0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts  -hupcl");
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}

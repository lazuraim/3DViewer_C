
#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  //  w.setFixedSize(1250, 1000); // ограниченные размер окна
  w.show();
  //  w.showMaximized(); // фул скрин
  return a.exec();
}

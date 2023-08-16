#include "mainwindow.h"
#include <cstdio>

#include <QApplication>

int main(int argc, char **argv) {
  printf("%s, v%s\n", PROJECT_NAME, PROJECT_VERSION);

  QApplication a(argc, argv);

  MainWindow m;

  m.show();

  return a.exec();
}
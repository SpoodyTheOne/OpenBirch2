#include <cstdio>
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char** argv) {
  printf("%s, v%s", PROJECT_NAME, PROJECT_VERSION);
  return 0;
}
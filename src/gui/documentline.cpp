#include "documentline.h"
#include "ui_documentline.h"

DocumentLine::DocumentLine(QWidget *parent) : QWidget(parent), ui(new Ui::DocumentLine) {
  ui->setupUi(this);

  printf("Added line :3\n");
}

DocumentLine::~DocumentLine() { printf("Deleted line\n"); }
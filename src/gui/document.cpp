#include "document.h"
#include "ui_document.h"

Document::Document(QWidget *parent) : QWidget(parent), ui(new Ui::Document) { 
 ui->setupUi(this);
}

Document::~Document() {};
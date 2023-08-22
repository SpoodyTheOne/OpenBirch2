#include "mainwindow.h"
#include "document.h"
#include "ui_mainwindow.h"

#include <QTabWidget>
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);

  QTabWidget *tabs = ui->tabWidget;
  QMenuBar *menuBar = this->menuBar();

  connect(tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::tabClose);
  connect(menuBar, &QMenuBar::triggered, this, &MainWindow::onActionTriggered);
}

MainWindow::~MainWindow() {
  // DIE >:3
}

void MainWindow::tabClose(int tab) {
  printf("Closed tab %d\n", tab);

  ui->tabWidget->removeTab(tab);
}

void MainWindow::onActionTriggered(QAction *action) {

  printf("Action triggered: %s \"%s\"\n",
         action->parent()->objectName().toStdString().c_str(),
         action->objectName().toStdString().c_str());
}

void MainWindow::newTab() {
  printf("New tab\n");
  ui->tabWidget->addTab(new Document(), "New Document*");
}

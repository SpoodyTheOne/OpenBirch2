#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTabWidget>

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
  printf("Action triggered: \"%s\"\n", action->text().toStdString().c_str());
}
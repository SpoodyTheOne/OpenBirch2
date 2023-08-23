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

void MainWindow::tabCloseRequested(int index) {
  printf("fuck uck ufunfiun;\n");
}

/**
 * @brief Creates a new tab and focuses it
 * @param #name: The name of the new tab
 */
void MainWindow::newTab(QString name, QWidget *widget) {
  printf("New tab\n");
  int idx = ui->tabWidget->addTab(widget, name);
  // Focus new tab
  ui->tabWidget->setCurrentIndex(idx);
}

/**
 * @brief Creates a new document in a tab
 */
void MainWindow::newDocument() {
  Document *newDocument = new Document();

  this->newTab(newDocument->getName(), newDocument);
}

/**
 * @brief Closes the currently selected tab
 */
void MainWindow::closeCurrentTab() {
  QWidget *currentWidget = ui->tabWidget->currentWidget();
  bool success = currentWidget->close();

  if (success) {
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    delete currentWidget;
  }
}

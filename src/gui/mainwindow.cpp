#include "mainwindow.h"
#include "document.h"
#include "ui_mainwindow.h"

#include <QTabWidget>
#include <qevent.h>
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);

  QTabWidget *tabs = ui->tabWidget;
  QMenuBar *menuBar = this->menuBar();

  connect(tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::tabClose);
  connect(menuBar, &QMenuBar::triggered, this, &MainWindow::onActionTriggered);

  newDocument();
}

MainWindow::~MainWindow() {
  // DIE >:3
}

void MainWindow::tabClose(int tab) {
  QWidget *currentWidget = ui->tabWidget->widget(tab);

  if (currentWidget == nullptr) {
    printf("Tried to close invalid tab %d\n", tab);
    return;
  }

  bool success = currentWidget->close();

  if (success) {
    ui->tabWidget->removeTab(tab);
    delete currentWidget;
  }
}

void MainWindow::onActionTriggered(QAction *action) {

  printf("Action triggered: %s \"%s\"\n",
         action->parent()->objectName().toStdString().c_str(),
         action->objectName().toStdString().c_str());
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
void MainWindow::closeCurrentTab() { tabClose(ui->tabWidget->currentIndex()); }

void MainWindow::closeEvent(QCloseEvent *event) {

  for (;;) {
    Document *tab = (Document *)ui->tabWidget->widget(0);

    if (tab == nullptr)
      break;

    if (tab->closeDocument() == false) {
      event->ignore();
      break;
    } else {
      tabClose(0);
    }
  }

  event->accept();
}

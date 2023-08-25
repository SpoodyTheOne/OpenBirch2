#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT;

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void tabClose(int tab);
  void onActionTriggered(QAction *action);

  void closeEvent(QCloseEvent *event) override;

public slots:
  void newTab(QString name = "New Tab", QWidget *widget = nullptr);
  void newDocument();
  void closeCurrentTab();

private:
  Ui::MainWindow *ui{};
  // BirchCas
};

#endif
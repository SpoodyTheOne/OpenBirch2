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

private:
  Ui::MainWindow *ui{};
};

#endif
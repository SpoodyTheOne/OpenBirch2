#ifndef OBTABWIDGET_H
#define OBTABWIDGET_H

#include <QTabWidget>
#include <QWidget>

namespace Ui {
class OBTabWidget;
}

class OBTabWidget : public QTabWidget {
  Q_OBJECT;

public:
  explicit OBTabWidget(QWidget *parent = nullptr);
  ~OBTabWidget();

private:
  Ui::OBTabWidget *ui{};
};

#endif
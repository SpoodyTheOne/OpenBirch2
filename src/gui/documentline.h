#ifndef DOCUMENTLINE_H
#define DOCUMENTLINE_H

#include <QWidget>
#include <QObject>

namespace Ui {
class DocumentLine;
}

class DocumentLine : public QWidget {
  Q_OBJECT;

public:
  explicit DocumentLine(QWidget *parent = nullptr);
  ~DocumentLine();

private:
  Ui::DocumentLine *ui{};
};

#endif
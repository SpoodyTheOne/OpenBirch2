#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QWidget>

namespace Ui {
class Document;
}

class Document : public QWidget {
  Q_OBJECT;

public:
  explicit Document(QWidget *parent = nullptr);
  ~Document();

private:
  Ui::Document *ui{};
  // BirchCas
};

#endif
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Document;
}

class Document : public QWidget {
  Q_OBJECT;

public:
  explicit Document(QWidget *parent = nullptr);
  ~Document();

  void closeEvent(QCloseEvent *event) override;
  bool unsavedChanges();

  bool closeDocument();
  bool save();

  QString getName();

private:
  Ui::Document *ui{};
  QString m_DocumentName = "Untitled Document";
  bool m_UnsavedChanged = true;
  // BirchCas
};

#endif
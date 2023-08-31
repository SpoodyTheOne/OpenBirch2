#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "documentsegment.h"
#include <QWidget>
#include <QMessageBox>

class DocumentLine;

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

  void addLine(SegmentType type, int index = -1);
  void addLine(DocumentLine* line, int index = -1);
  
private:
  Ui::Document *ui{};
  QString m_DocumentName = "Untitled Document";
  bool m_UnsavedChanged = true;
  // BirchCas
};

#endif
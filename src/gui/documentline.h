#ifndef DOCUMENTLINE_H
#define DOCUMENTLINE_H

#include "documentsegment.h"
#include <QWidget>
#include <QObject>

namespace Ui {
class DocumentLine;
}

class DocumentLine : public QWidget {
  Q_OBJECT;

public:
  explicit DocumentLine(QWidget *parent = nullptr, SegmentType type = SegmentType::MATH);
  ~DocumentLine();

  bool canEvaluate();
  
private:
  Ui::DocumentLine *ui{};

  std::vector<DocumentSegment> m_Segments;
};

#endif
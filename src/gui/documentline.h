#ifndef DOCUMENTLINE_H
#define DOCUMENTLINE_H

#include "documentsegment.h"
#include <QObject>
#include <QWidget>

namespace Ui {
class DocumentLine;
}

class DocumentLine : public QWidget {
  Q_OBJECT;

public:
  explicit DocumentLine(QWidget *parent = nullptr,
                        SegmentType type = SegmentType::MATH);
  ~DocumentLine();

  void addSegment(SegmentType type, int index = -1);
  void addSegment(DocumentSegment* segment, int index = -1);
  
  bool canEvaluate();

  void enterPressed();
  
  QString getText();
  
private:
  void testCanEvaluate();
  
  Ui::DocumentLine *ui{};
  bool m_CanEvaluate = false;
  std::vector<DocumentSegment *> m_Segments;
};

#endif
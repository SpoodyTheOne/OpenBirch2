#ifndef MATHSEGMENT_H
#define MATHSEGMENT_H

#include "documentsegment.h"
#include "mathitem.h"
#include <QWidget>

namespace Ui {
class MathSegment;
}

class MathSegment : public QWidget, public DocumentSegment {
  Q_OBJECT;

public:
  explicit MathSegment(QWidget *parent = nullptr);

  QString getText() override;
  SegmentType getType() override;
  QWidget *getWidget() override;

  QSize sizeHint() const override;

  QPainter createPainter() ;
  
private:
  Ui::MathSegment *ui{};

  std::vector<MathItem *> m_Items;

protected:
  void paintEvent(QPaintEvent *event) override;
};

#endif
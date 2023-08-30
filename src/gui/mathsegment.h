#ifndef MATHSEGMENT_H
#define MATHSEGMENT_H

#include "documentsegment.h"
#include <QWidget>
#include <qlineedit.h>

namespace Ui {
class MathSegment;
}

class MathSegment : public QLineEdit, public DocumentSegment {
  Q_OBJECT;

public:
  explicit MathSegment(QWidget *parent = nullptr);

  QString getText() override;
  SegmentType getType() override;
  QWidget *getWidget() override;

private:
  Ui::MathSegment *ui{};
};

#endif
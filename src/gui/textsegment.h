#ifndef TEXTSEGMENT_H
#define TEXTSEGMENT_H

#include "documentsegment.h"
#include <QWidget>
#include <qlineedit.h>

namespace Ui {
class TextSegment;
}

class TextSegment : public QLineEdit, public DocumentSegment {
  Q_OBJECT;

public:
  explicit TextSegment(QWidget *parent = nullptr);

  QString getText() override;
  SegmentType getType() override;
  QWidget *getWidget() override;

private:
  Ui::TextSegment *ui{};
};

#endif
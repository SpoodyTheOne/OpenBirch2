#ifndef OUTPUTSEGMENT_H
#define OUTPUTSEGMENT_H

#include "documentsegment.h"
#include <QWidget>
#include <qlabel.h>
#include <qlineedit.h>

namespace Ui {
class OutputSegment;
}

class OutputSegment : public QLabel, public DocumentSegment {
  Q_OBJECT;

public:
  explicit OutputSegment(QWidget *parent = nullptr);

  QString getText() override;
  SegmentType getType() override;
  QWidget *getWidget() override;

private:
  Ui::OutputSegment *ui{};
};

#endif
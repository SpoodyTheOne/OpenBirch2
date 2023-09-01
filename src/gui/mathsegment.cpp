#include "mathsegment.h"
#include "documentsegment.h"
#include <qapplication.h>
#include <qnamespace.h>
#include <qpainter.h>

MathSegment::MathSegment(QWidget *parent) : QWidget(parent) {
  setFocusPolicy(Qt::StrongFocus);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  m_Items.push_back(new StringMathItem("2x test"));
};

QString MathSegment::getText() {
  QString output = "";

  for (MathItem *item : m_Items) {
    output += item->getText();
  }

  return output;
}

SegmentType MathSegment::getType() { return SegmentType::TEXT; }

QWidget *MathSegment::getWidget() { return this; }

QSize MathSegment::sizeHint() const {
  QSize test(100, 100);

  return test;
}

void MathSegment::paintEvent(QPaintEvent *event) {
  QPainter p(this);

  QPalette palette = QApplication::palette();

  p.setRenderHint(QPainter::Antialiasing);
  p.setPen(palette.Text);
  p.setBrush(palette.text());

  // printf("Text palette: %s\n", palette.text().color().toRgb().name().toStdString().c_str());
  
  p.setBackground(palette.base());

  QPoint currentPos = QPoint(2, 2);

  for (MathItem *item : m_Items) {
    currentPos = item->draw(currentPos, p);
  }
}
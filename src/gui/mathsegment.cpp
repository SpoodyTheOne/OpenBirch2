#include "mathsegment.h"
#include "documentsegment.h"
#include <QFile>
#include <QFontDatabase>
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
  int height = 0;
  int width = 0;

  /// \todo fix bad cvr (it wont run until fixed)
  QPainter painter = createPainter();

  QPoint currentPos = QPoint(0, 0);

  for (MathItem *item : m_Items) {
    QRect size = item->getSize(painter, currentPos);

    if (height < size.height())
      height = size.height();

    width += size.width();

    currentPos = size.topLeft();
  }

  printf("i calculated %d size width\n", width);

  return QSize(width, height + 8);
}

void MathSegment::paintEvent(QPaintEvent *event) {
  QPainter painter = createPainter();

  QPoint currentPos = QPoint(0, 0);

  for (MathItem *item : m_Items) {
    currentPos = item->draw(currentPos, painter);
  }

  updateGeometry();
}

QPainter MathSegment::createPainter() {
  QPainter painter;
  painter.begin(this);

  QPalette palette = QApplication::palette();

  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(palette.text().color());
  painter.setBrush(palette.text());

  QFile fontFile(":/res/fonts/XITSMath-Regular.otf");

  if (fontFile.open(QIODevice::ReadOnly) == false) {
    printf("Cant open file\n");
    abort();
  } else {
    int fontID = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
    if (fontID == -1) {
      printf("Error adding font to database");
      abort();
    } else {
      QFont font = QFontDatabase::applicationFontFamilies(fontID).first();
      font.setItalic(true);
      font.setPointSize(14);
      painter.setFont(font);
    }
  }

  printf("font in use: %s\n",
         painter.fontInfo().family().toStdString().c_str());

  // printf("Text palette: %s\n",
  // palette.text().color().toRgb().name().toStdString().c_str());

  painter.setBackground(palette.base().color());
}
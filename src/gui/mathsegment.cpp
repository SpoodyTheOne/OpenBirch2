#include "mathsegment.h"
#include "documentsegment.h"
#include "mathitem.h"
#include "nrootitem.h"
#include <QFile>
#include <QFontDatabase>
#include <qapplication.h>
#include <qnamespace.h>
#include <qpainter.h>

MathSegment::MathSegment(QWidget *parent) : QWidget(parent) {
  setFocusPolicy(Qt::StrongFocus);
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  m_Items.push_back(new StringMathItem("2x test"));

  auto top = new StringMathItem("2x");
  auto bottom = new StringMathItem("IT FUCKING WORKS");
  auto fraction = new FractionMathItem(top, bottom);
  m_Items.push_back(fraction);

  auto top2 = new FractionMathItem(new StringMathItem("pee pee"),
                                   new StringMathItem("62 fb"));
  auto bottom2 = new StringMathItem("69x+420y");

  // m_Items.push_back(new FractionMathItem(new FractionMathItem(bottom2, top2),
  //                                        new StringMathItem("penis")));

  auto root =
      new NRootMathItem(new StringMathItem("3"), new StringMathItem("64"));
  m_Items.push_back(root);
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

  /// TODO: fix bad cvr (it wont run until fixed)
  QPoint currentPos = QPoint(0, 0);

  for (MathItem *item : m_Items) {
    QRect size = item->getSize(getFont(), currentPos);

    if (height < size.height())
      height = size.height();

    width += size.width();

    currentPos = size.topLeft();
  }

  // printf("i calculated %d size width\n", width);

  return QSize(width, height + 8);
}

void MathSegment::paintEvent(QPaintEvent *event) {
  QPainter *painter = createPainter();

  QPoint currentPos = QPoint(0, 0);

  QSize size = sizeHint();

  // Debug, uncomment to see bounding boxes of draw calls
  // painter->setBackgroundMode(Qt::BGMode::OpaqueMode);
  // painter->setBackground(Qt::green);

  for (MathItem *item : m_Items) {
    QRect itemSize = item->getSize(getFont());

    if (itemSize.height() < size.height()) {
      // Offset Y position by height/2 - half of item height
      int offset = size.height() / 2 - itemSize.height() / 2;
      currentPos.setY(offset);
    }

    currentPos = item->draw(currentPos, *painter);
  }

  delete painter;
  updateGeometry();
}

QPainter *MathSegment::createPainter() {
  QPainter *painter = new QPainter();
  painter->begin(this);
  painter->setRenderHints(QPainter::Antialiasing);

  QPalette palette = QApplication::palette();

  // painter->setRenderHint(QPainter::Antialiasing);
  painter->setPen(palette.text().color());
  painter->setBrush(palette.text());

  painter->setFont(getFont());

  // printf("font in use: %s\n",
  //        painter->fontInfo().family().toStdString().c_str());

  // printf("Text palette: %s\n",
  // palette.text().color().toRgb().name().toStdString().c_str());

  // painter->setBackground(Qt::green);
  // painter->setBackgroundMode(Qt::BGMode::OpaqueMode);

  // painter->fillRect(0, 0, 1000, 1000, Qt::darkGreen);

  return painter;
}

QFont MathSegment::getFont() {
  if (MathSegment::MathFontID == -1) {
    QFile fontFile(":/res/fonts/XITSMath-Regular.otf");

    if (fontFile.open(QIODevice::ReadOnly) == false) {
      printf("Failed to open math font file\n");
      abort();
    }

    MathSegment::MathFontID =
        QFontDatabase::addApplicationFontFromData(fontFile.readAll());

    if (MathSegment::MathFontID == -1) {
      printf("Error adding font to database");
      abort();
    }
  }

  QFont font =
      QFontDatabase::applicationFontFamilies(MathSegment::MathFontID).first();
  font.setItalic(true);
  font.setPointSize(12);
  return font;
}

void MathSegment::mousePressEvent(QMouseEvent *event) {
  QWidget::mousePressEvent(event);
}

QFont MathSegment::getSubscriptFont() {
  QFont font = getFont();

  font.setPointSize(10);

  return font;
}

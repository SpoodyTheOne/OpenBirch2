#ifndef NROOTITEM_H
#define NROOTITEM_H

#include "mathitem.h"
#include "mathsegment.h"

class NRootMathItem : public MathItem {
private:
  MathItem *m_Root;
  MathItem *m_Value;
#define VALUE_PADDING 2
#define WHITE_PADDING 6
#define LEFT_PAD 10
#define LEFT_MARGIN 4
#define FOOT_HEIGHT 12

public:
  explicit NRootMathItem(MathItem *root, MathItem *value) {
    m_Root = root;
    m_Value = value;
  }

  QRect getSize(QFont font, const QPoint topleft) const override {
    QRect valueSize = m_Value->getSize(font);
    QRect rootSize = m_Root->getSize(MathSegment::getSubscriptFont());

    int height = valueSize.height(); // rootSize.height();
    int width = valueSize.width() + rootSize.width() + VALUE_PADDING +
                LEFT_PAD + WHITE_PADDING + LEFT_MARGIN;

    QRect boundingBox(topleft.x(), topleft.y(), width, height);
    return boundingBox;
  }

  QString getText() const override {
    // TODO: figure out how function calls should be formatted
    return "nroot(" + m_Value->getText() + ";" + m_Root->getText() + ')';
  }

  QPoint draw(const QPoint &pos, QPainter &painter) const override {

    QPoint newPos = pos + QPoint(LEFT_MARGIN, 0);

    QFont rootFont = MathSegment::getSubscriptFont();
    QFont font = painter.font();

    QRect rootSize = m_Root->getSize(rootFont, newPos);
    QRect valueSize = m_Value->getSize(font, newPos);
    QRect boundingBox = getSize(font, newPos);

    QPoint diagonalBarIntersection =
        newPos + QPoint(rootSize.width() + LEFT_PAD, 0);
    QPoint bottomCorner = newPos + QPoint(LEFT_PAD, boundingBox.height());
    QPoint footIntersection = bottomCorner - QPoint(LEFT_PAD, FOOT_HEIGHT);

    int barWidth = valueSize.width() + VALUE_PADDING + WHITE_PADDING;

    QPoint rootDrawPos =
        newPos + QPoint(0, boundingBox.height() - rootSize.height() - 8);

    // Top line
    painter.drawLine(diagonalBarIntersection,
                     diagonalBarIntersection + QPoint(barWidth, 0));

    // Rightmost Diagonal line
    painter.drawLine(bottomCorner, diagonalBarIntersection);

    QPoint rootPoint =
        rootDrawPos + QPoint(rootSize.width(), rootSize.height());

    // Leftmost Diagonal line
    painter.drawLine(rootPoint, bottomCorner);

    // Line under root
    painter.drawLine(rootPoint + QPoint(-rootSize.width(), 3), rootPoint);

    m_Value->draw(diagonalBarIntersection + QPoint(VALUE_PADDING, 0), painter);

    if (m_Root->getText() != "2") {
      painter.setFont(rootFont);
      m_Root->draw(rootDrawPos, painter);
      painter.setFont(font);
    }

    return boundingBox.topRight();
  }
};

#endif
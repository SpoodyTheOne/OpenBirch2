#ifndef MATHITEM_H
#define MATHITEM_H

#include <QPainter>
#include <QString>
#include <qpoint.h>
#include <qsize.h>
#include <qwindowdefs.h>
#include <vector>

class MathItem {
public:
  /** Called when the item is drawn
  @param pos: the top left corner of the widget
  @param painter: the painter used for drawing
  @returns QPoint: the top right corner, used for the next widget to draw with
  */
  virtual QPoint draw(const QPoint &pos, QPainter &painter) const = 0;

  /// returns the parser parsable text contained in this item
  virtual QString getText() const = 0;

  /** Returns the bounding box of this item
  @param font: The font used to render this widget
  @param topleft: the top left corner of the item, aka where the previous item
  ended
  @returns QRect: the bounding box of this item
  */
  virtual QRect getSize(QFont font, const QPoint topleft = {0, 0}) const = 0;
  // virtual QPoint nextDrawPos(const QPoint &pos, QPainter &painter) const = 0;
};

class StringMathItem : public MathItem {
public:
  explicit StringMathItem(QString value) : m_Value(value) {}

  QPoint draw(const QPoint &pos, QPainter &painter) const override {
    QRect size = getSize(painter.font(), pos);
    painter.drawText(size.bottomLeft(), m_Value);
    return size.topRight();
  }

  QRect getSize(QFont font, const QPoint topleft) const override {
    QFontMetrics metrics(font);

    int width = metrics.horizontalAdvance(m_Value);
    int height = metrics.height();

    return QRect(topleft.x(), topleft.y(), width, height);
  }

  QString getText() const override { return m_Value; }

private:
  QString m_Value = "";
};

class FractionMathItem : public MathItem {
public:
  explicit FractionMathItem(MathItem *top, MathItem *bottom) {
    m_Top = top;
    m_Bottom = bottom;
  }

  QRect getSize(QFont font, const QPoint topleft) const override {
    QRect topSize = m_Top->getSize(font);
    QRect bottomSize = m_Bottom->getSize(font);
    int width = std::max(topSize.width(), bottomSize.width());

    auto bottomHeight = bottomSize.height();
    auto topHeight = topSize.height() + 2;

    int height = bottomHeight + topHeight;

    auto r = QRect(topleft.x() + 4, topleft.y(), width + 8, height);

    printf("size: %d, %d\n", r.width(), r.height());
    return r;
  }

  QString getText() const override {
    return '(' + m_Top->getText() + '/' + m_Bottom->getText() + ')';
  }

  QPoint draw(const QPoint &pos, QPainter &painter) const override {
    QRect size = getSize(painter.font(), pos);
    int middle = size.width() / 2;
    int yMiddle = pos.y() + m_Top->getSize(painter.font()).height() + 2;

    // Draw top
    m_Top->draw(
        QPoint(pos.x() + middle - m_Top->getSize(painter.font()).width() / 2,
               pos.y()),
        painter);

    painter.drawLine(pos.x() + 1, yMiddle, pos.x() + size.width(), yMiddle);

    m_Bottom->draw(
        QPoint(pos.x() + middle - m_Bottom->getSize(painter.font()).width() / 2,
               yMiddle),

        painter);

    return size.topRight();
  }

private:
  MathItem *m_Top;
  MathItem *m_Bottom;
};

#endif
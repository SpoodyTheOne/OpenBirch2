#ifndef MATHITEM_H
#define MATHITEM_H

#include <QMouseEvent>
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

  void clickEvent(QMouseEvent event){};
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

    painter.drawLine(pos.x() + 4, yMiddle, pos.x() + size.width() - 4, yMiddle);

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

class NRootMathItem : public MathItem {
private:
    MathItem *m_Root;
    MathItem *m_Value;
    static inline int VALUE_PADDING = 2;
    static inline int WHITE_PADDING = 10;
    static inline int LEFT_PAD = 10;
    static inline int FOOT_HEIGHT = 12;

public:
    explicit NRootMathItem(MathItem* root, MathItem* value)
    {
        m_Root= root;
        m_Value = value;
    }

    QRect getSize(QFont font, const QPoint topleft) const override {
        QRect valueSize = m_Value->getSize(font);
        QRect rootSize = m_Root->getSize(font);

        int height = valueSize.height() + rootSize.height();
        int width = valueSize.width() + rootSize.width() + VALUE_PADDING + LEFT_PAD + WHITE_PADDING;

        QRect boundingBox(topleft.x(), topleft.y(), width, height);
        return boundingBox;
    }

    QString getText() const override {
        // TODO: figure out how function calls should be formatted
        return "nroot(" + m_Value->getText() + ";" + m_Root->getText() + ')';
    }

    QPoint draw(const QPoint& pos, QPainter& painter) const override {
        QRect rootSize = m_Root->getSize(painter.font(), pos);
        QRect valueSize = m_Value->getSize(painter.font(), pos);
        QRect boundingBox = getSize(painter.font(), pos);

        QPoint diagonalBarIntersection = pos + QPoint(rootSize.width() + LEFT_PAD, rootSize.height());
        QPoint bottomCorner = pos + QPoint(LEFT_PAD, boundingBox.height());
        QPoint footIntersection = bottomCorner - QPoint(LEFT_PAD, FOOT_HEIGHT);

        int barWidth = valueSize.width() + VALUE_PADDING + WHITE_PADDING;

        painter.drawLine(diagonalBarIntersection, diagonalBarIntersection + QPoint(barWidth, 0));
        painter.drawLine(bottomCorner, diagonalBarIntersection);
        painter.drawLine(footIntersection, bottomCorner);

        m_Value->draw(diagonalBarIntersection + QPoint(VALUE_PADDING, 0), painter);
        m_Root->draw(pos + QPoint(0, 5), painter);

        return boundingBox.topRight();
    }
};

#endif

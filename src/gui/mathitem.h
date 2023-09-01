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
  virtual QPoint draw(const QPoint &pos, QPainter &painter) const = 0;
  virtual QString getText() const = 0;
  virtual QRect getSize(QPainter &painter,
                        const QPoint topleft = {0, 0}) const = 0;
  // virtual QPoint nextDrawPos(const QPoint &pos, QPainter &painter) const = 0;

private:
  std::vector<MathItem *> m_Children;
};

class StringMathItem : public MathItem {
public:
  explicit StringMathItem(QString value) : m_Value(value) {}

  QPoint draw(const QPoint &pos, QPainter &painter) const override {
    QRect size = getSize(painter, pos);
    painter.drawText(size.bottomLeft(), m_Value);
    return size.topRight();
  }

  QRect getSize(QPainter &painter, const QPoint topleft) const override {
    int width = painter.fontMetrics().horizontalAdvance(m_Value);
    int height = painter.fontMetrics().height();

    return QRect(topleft.x(), topleft.y(), width, height);
  }

  QString getText() const override { return m_Value; }

private:
  QString m_Value = "";
};

#endif
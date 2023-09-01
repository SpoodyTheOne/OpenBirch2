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
  virtual QRect getSize(QFont font, const QPoint topleft = {0, 0}) const = 0;
  // virtual QPoint nextDrawPos(const QPoint &pos, QPainter &painter) const = 0;

private:
  std::vector<MathItem *> m_Children;
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

    return QRect(topleft.x(), topleft.y() + 1,  width, height);
  }

  QString getText() const override { return m_Value; }

private:
  QString m_Value = "";
};

#endif
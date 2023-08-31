#ifndef MATHITEM_H
#define MATHITEM_H

#include <QString>
#include <qpoint.h>
#include <qwindowdefs.h>
#include <vector>

class MathItem {
public:
  explicit MathItem(QString value = "");

  QPoint draw(const QPoint &pos, QPainter &painter) const;
  virtual QString getText() const;

private:
  std::vector<MathItem *> m_Children;
  QString m_Value = "";
};

#endif
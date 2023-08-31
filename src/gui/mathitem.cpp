#include <mathitem.h>

MathItem::MathItem(QString value) : m_Value(value) {}

QString MathItem::getText() const {
  if (m_Children.empty())
    return m_Value;

  QString output = "";

  for (MathItem *item : m_Children) {
    output += item->getText();
  }

  return output;
}
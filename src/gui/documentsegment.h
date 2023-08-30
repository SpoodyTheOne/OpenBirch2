#ifndef DOCUMENTSEGMENT_H
#define DOCUMENTSEGMENT_H

#include <QString>
#include <qobject.h>
#include <qobjectdefs.h>
#include <vector>

enum SegmentType { TEXT, MATH, INVALID };

class DocumentSegment {
public:
  const std::vector<DocumentSegment *> &getChildren() {
    return this->m_Children;
  };

  void insertChild(int index, DocumentSegment *segment) {
    m_Children.insert(m_Children.begin() + index, segment);
  };

  void destroy() {
    for (DocumentSegment *c : m_Children) {
      c->destroy();
    }

    std::vector<DocumentSegment *>().swap(m_Children);
  };

  virtual QString getText() {
    QString out = "";

    for (DocumentSegment *c : m_Children)
      out += c->getText();

    return out;
  }

  virtual SegmentType getType() = 0;
  virtual QWidget* getWidget() = 0;

  static DocumentSegment *newFromType(SegmentType type);

private:
  std::vector<DocumentSegment *> m_Children = {};
};

#endif
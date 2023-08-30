#ifndef DOCUMENTSEGMENT_H
#define DOCUMENTSEGMENT_H

#include <QString>
#include <qobject.h>
#include <qobjectdefs.h>
#include <vector>

enum SegmentType {
  /// Indicates a segment for typing plain/rich text into
  TEXT,
  /// A segment that can be evaluated by the parser
  MATH,
  /// A segment that is invalid and isnt meant to be used
  INVALID
};

class DocumentSegment {
public:
  const std::vector<DocumentSegment *> &getChildren() {
    return this->m_Children;
  };

  /** Inserts a child at index.
   * \todo: Check if this is actually useful
   * @param index: index to insert at
   * @param segment: the child to insert
   */
  void insertChild(int index, DocumentSegment *segment) {
    m_Children.insert(m_Children.begin() + index, segment);
  };

  /** Recursively deletes this segment and all its children
   * @brief Call before removing
   */
  void destroy() {
    for (DocumentSegment *c : m_Children) {
      c->destroy();
    }

    std::vector<DocumentSegment *>().swap(m_Children);
  };

  /** Returns the text of this segment, and/or the combined text of all its
   * children
   * @brief The value of this segment as text
   * @returns QString: The text that was within this segment
   */
  virtual QString getText() {
    QString out = "";

    for (DocumentSegment *c : m_Children)
      out += c->getText();

    return out;
  }

  /** The type of segment this is
   * @returns #SegmentType: either #TEXT, #MATH or #INVALID
   */
  virtual SegmentType getType() = 0;
  /** The QWidget that implements this segment
   * @returns QWidget: the widget of the segment
   */
  virtual QWidget *getWidget() = 0;

  static DocumentSegment *newFromType(SegmentType type);

private:
  std::vector<DocumentSegment *> m_Children = {};
};

#endif
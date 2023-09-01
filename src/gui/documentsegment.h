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
  /** Returns the text of this segment, and/or the combined text of all its
   * children
   * @brief The value of this segment as text
   * @returns QString: The text that was within this segment
   */
  virtual QString getText() = 0;

  /** The type of segment this is
   * @returns #SegmentType: either #TEXT, #MATH or #INVALID
   */
  virtual SegmentType getType() = 0;
  /** The QWidget that implements this segment
   * @returns QWidget: the widget of the segment
   */
  virtual QWidget *getWidget() = 0;

  static DocumentSegment *newFromType(SegmentType type);
};

#endif
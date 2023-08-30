#include "documentsegment.h"
#include "mathsegment.h"
#include "textsegment.h"

DocumentSegment *DocumentSegment::newFromType(SegmentType type) {
  switch (type) {
  case SegmentType::TEXT:
    return new TextSegment();
    break;
  case MATH:
    return new MathSegment();
    break;
  case INVALID:
  default:
    return nullptr;
    break;
  }
}
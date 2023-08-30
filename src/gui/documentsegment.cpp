#include "documentsegment.h"
#include "textsegment.h"

DocumentSegment *DocumentSegment::newFromType(SegmentType type) {
  switch (type) {
  case SegmentType::TEXT:
    return new TextSegment();
    break;
  case MATH:
  case INVALID:
    return nullptr;
    break;
  }

  return nullptr;
}
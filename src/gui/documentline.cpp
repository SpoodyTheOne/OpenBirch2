#include "documentline.h"
#include "documentsegment.h"
#include "ui_documentline.h"
#include <algorithm>
#include <math.h>

DocumentLine::DocumentLine(QWidget *parent, SegmentType type)
    : QWidget(parent), ui(new Ui::DocumentLine) {
  ui->setupUi(this);

  addSegment(SegmentType::TEXT);
  addSegment(SegmentType::MATH);

  printf("Added line :3\nType: %d", type);
}

DocumentLine::~DocumentLine() { printf("Deleted line\n"); }

/** Adds a #DocumentSegment of a #SegmentType type at index
 * @brief Adds a new #DocumentSegment
 * @param type: #SegmentType the type of segment to add
 * @param index: the index to insert at. Negative numbers go from the end
 */
void DocumentLine::addSegment(SegmentType type, int index) {
  DocumentSegment *segment = DocumentSegment::newFromType(type);
  addSegment(segment, index);
}

/** Adds a #DocumentSegment at index
 * @brief Adds a new #DocumentSegment
 * @param segment: The segment to add
 * @param index: The index to insert at. Negative numbers go from the end
 */

void DocumentLine::addSegment(DocumentSegment *segment, int index) {
  // If the index is negative we go backwards
  size_t idx = index;
  if (m_Segments.size() == 0)
    idx = 0;
  else {
    if (idx < 0)
      idx = m_Segments.size() + idx;
    // clamp value so its not outside range
    idx = std::min(idx, m_Segments.size() - 1);
  }

  // insert segment at position
  m_Segments.insert(m_Segments.begin() + idx, segment);

  ui->horizontalLayout->insertWidget(idx, segment->getWidget());

  // Update can evaluate state
  testCanEvaluate();
}

/** Whether or not this line can be evaluated as an expression by the parser
 * @brief Whether or not this line is math
 * @returns bool: true if this line contains exactly 1 Math segment, otherwise
 * returns false
 */
bool DocumentLine::canEvaluate() { return m_CanEvaluate; }

/** Called whenever a segment is added/removed/changed to update the
 * m_CanEvaluate flag
 * @brief Call whenever changing segments
 */
void DocumentLine::testCanEvaluate() {
  for (DocumentSegment *segment : m_Segments) {
    if (segment->getType() != SegmentType::MATH)
      m_CanEvaluate = false;
    return;
  }

  m_CanEvaluate = true;
}

/// Called by line segments when enter is pressed
void DocumentLine::enterPressed() {
  if (canEvaluate()) {
    // Evaluate text
    // Show output of evaluation on new line
    // Create new documentline with a math segment underneath output and focus
    // it
  } else {
    // Create new text line underneath
  }
}
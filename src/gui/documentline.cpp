#include "documentline.h"
#include "documentsegment.h"
#include "ui_documentline.h"

DocumentLine::DocumentLine(QWidget *parent, SegmentType type)
    : QWidget(parent), ui(new Ui::DocumentLine) {
  ui->setupUi(this);

  DocumentSegment *segment = DocumentSegment::newFromType(type);

  if (segment == nullptr) {
    printf("Segment returned nullptr. Aborting\n");
    abort();
  }

  ui->horizontalLayout->insertWidget(0, segment->getWidget());

  printf("Added line :3\nType: %d", type);
}

DocumentLine::~DocumentLine() { printf("Deleted line\n"); }

/** Whether or not this line can be evaluated as an expression by the parser
 * @brief Whether or not this line is math
 * @returns bool: true if this line contains exactly 1 Math segment, otherwise
 * returns false
 */
bool DocumentLine::canEvaluate() {
  if (m_Segments.size() == 1)
    return m_Segments.begin()->getType() == SegmentType::MATH;

  return false;
}
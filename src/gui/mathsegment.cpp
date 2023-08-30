#include "mathsegment.h"
#include "documentsegment.h"

MathSegment::MathSegment(QWidget *parent) : QLineEdit(parent) {
  setPlaceholderText("MathSegment");

  setStyleSheet("MathSegment {"
                "  background-color: transparent;"
                "}");
};

QString MathSegment::getText() { return this->text(); }

SegmentType MathSegment::getType() { return SegmentType::TEXT; }

QWidget *MathSegment::getWidget() { return this; }
#include "textsegment.h"
#include "documentsegment.h"

TextSegment::TextSegment(QWidget *parent) : QLineEdit(parent){};

QString TextSegment::getText() { return this->text(); }

SegmentType TextSegment::getType() {
 return SegmentType::TEXT;
}

QWidget* TextSegment::getWidget() {
 return this;
}
#include "textsegment.h"
#include "documentsegment.h"

#include <QStyle>

TextSegment::TextSegment(QWidget *parent) : QLineEdit(parent) {
  setPlaceholderText("TextSegment");
  setFrame(false);

  setStyleSheet("TextSegment {"
                "  background-color: transparent;"
                "}");
};

QString TextSegment::getText() { return this->text(); }

SegmentType TextSegment::getType() { return SegmentType::TEXT; }

QWidget *TextSegment::getWidget() { return this; }
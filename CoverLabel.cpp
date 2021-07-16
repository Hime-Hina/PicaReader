#include "CoverLabel.h"

CoverLabel::CoverLabel(QWidget *parent)
  : QLabel(parent) {
}

void CoverLabel::mouseReleaseEvent(QMouseEvent* e) {
  emit clicked();
}

void CoverLabel::resizeEvent(QResizeEvent* e) {
  if (ppixmap_) {
    setPixmap(ppixmap_->scaled(size(), Qt::KeepAspectRatio));
  }
}


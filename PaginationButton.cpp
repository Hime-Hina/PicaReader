#include "PaginationButton.h"

PaginationButton::PaginationButton(qint32 id, QWidget* parent)
  : QPushButton(parent), _id(id) {
  setMinimumHeight(50);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  setCheckable(true);
  setFocusPolicy(Qt::NoFocus);
  connect(this, &PaginationButton::clicked, this, &PaginationButton::SendPageNum);
  connect(this, &PaginationButton::toggled, [this](bool checked) {
    if (!checked) setText("");
    else setText(QString::number(_id));
  });
}

void PaginationButton::SendPageNum() {
  emit Clicked(_id);
}

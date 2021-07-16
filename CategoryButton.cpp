#include "CategoryButton.h"

CategoryButton::CategoryButton(QWidget *parent)
    : QToolButton(parent) {
  setAttribute(Qt::WA_StyledBackground);
  setFocusPolicy(Qt::NoFocus);
  setCheckable(true);
}

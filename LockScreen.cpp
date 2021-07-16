#include "LockScreen.h"
#include "ui_LockScreen.h"

LockScreen::LockScreen(QWidget *parent)
    : QWidget(parent), ui(new Ui::LockScreen) {
  ui->setupUi(this);
  setAutoFillBackground(true);
  setPalette(QPalette(QPalette::Background, QColor(0, 0, 0, 180)));
}

LockScreen::~LockScreen() {
  delete ui;
}

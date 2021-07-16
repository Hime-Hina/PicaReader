#include "CoverWidget.h"
#include <QThread>

CoverWidget::CoverWidget(QWidget *parent)
  : QWidget(parent), ui(new Ui::CoverWidget) {
  setAttribute(Qt::WA_StyledBackground, true);

  ui->setupUi(this);

  connect(ui->cover_label, &CoverLabel::clicked,
          this, &CoverWidget::SendCoverLabelClicked);
  connect(ui->title_label, &CoverLabel::clicked,
          this, &CoverWidget::SendCoverLabelClicked);
  SetShowTitle(false);
}

CoverWidget::~CoverWidget() {
  delete ui;
}

void CoverWidget::SendCoverLabelClicked() {
  if (pfile_info_ != nullptr) emit CoverLabelClicked(*pfile_info_);
}

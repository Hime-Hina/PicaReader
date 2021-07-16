#include "ReadingCompletePage.h"

ReadingCompletePage::ReadingCompletePage(QWidget *parent)
    : AbstractPage(parent), ui(new Ui::ReadingCompletePage) {
  ui->setupUi(this);
  ui->right_widget->setAttribute(Qt::WA_StyledBackground);
  ui->similar_book_box->SetCoverWidgets(3, 3);
  pic_.load(":/images/good");

  connect(ui->nxt_book_btn, &QToolButton::clicked,
          this, &ReadingCompletePage::NxtBook);
  connect(ui->favorite_btn, &QToolButton::toggled, [this](bool checked) {
    if (!checked) emit RemoveFromFavorites();
    else emit AddToFavorites();
  });
  connect(ui->rewatch_btn, &QToolButton::clicked,
          this, &ReadingCompletePage::Rewatch);
  connect(ui->return_btn, &QToolButton::clicked,
          this, &ReadingCompletePage::Return);
  connect(ui->similar_book_box, &PicBookCoverBox::CoverWidgetClicked,
          this, &ReadingCompletePage::CoverBoxSignal);
}

ReadingCompletePage::~ReadingCompletePage() {
  delete ui;
}

void ReadingCompletePage::SetContents(const QDir& books_dir) {
  ui->similar_book_box->SetContentsByDir(books_dir, 3, 3);
}

void ReadingCompletePage::SetFavoriteBtn(bool on) {
  qDebug("Set favorite btn to %d", on);
  ui->favorite_btn->setChecked(on);
}

void ReadingCompletePage::resizeEvent(QResizeEvent* e) {
  ui->picture_label->setPixmap(
        pic_.scaled(ui->picture_label->size(), Qt::KeepAspectRatio)
  );
}

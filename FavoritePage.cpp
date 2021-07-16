#include "FavoritePage.h"

FavoritePage::FavoritePage(QWidget *parent)
    : AbstractPage(parent), ui(new Ui::FavoritePage) {
  ui->setupUi(this);
  connect(ui->favorite_page_cover_box, &PicBookCoverBox::CoverWidgetClicked,
          this, &FavoritePage::CoverBoxSignal);
}

FavoritePage::~FavoritePage() {
  delete ui;
}

void FavoritePage::SetContents(const QJsonArray& raw_book_paths) {
  ui->favorite_page_cover_box->SetContentsByStringList(
        ConvertJArrToStringList(raw_book_paths)
  );
}

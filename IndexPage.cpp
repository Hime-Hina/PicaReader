#include "IndexPage.h"

IndexPage::IndexPage(QWidget *parent)
    : AbstractPage(parent), ui(new Ui::IndexPage) {
  setAttribute(Qt::WA_StyledBackground);

  ui->setupUi(this);
  ui->recent_books_box->SetShowTitle(false);
  ui->recent_books_box->SetShowPagiBtns(false);

  connect(ui->settings_btn, &QToolButton::clicked, [this]() {
    ui->index_pages->setCurrentWidget(ui->settings_page);
    if (curr_owner_ != ui->username_line_edit->text())
      ui->username_line_edit->setText(curr_owner_);
    if (curr_equip_name_ != ui->equip_name_line_edit->text())
      ui->equip_name_line_edit->setText(curr_equip_name_);
  });
  connect(ui->score_btn, &QToolButton::clicked, [this]() {
    ui->index_pages->setCurrentWidget(ui->score_page);
  });
  connect(ui->settings_page_return_btn, &QToolButton::clicked, [this]() {
    if (curr_owner_ != ui->username_line_edit->text()) { // 如果昵称改变了
      SetOwner(ui->username_line_edit->text());
      emit OwnerChanged(curr_owner_);
    }
    if (curr_equip_name_ != ui->equip_name_line_edit->text()) { // 同上
      SetEquipName(ui->equip_name_line_edit->text());
      emit EquipNameChanged(curr_equip_name_);
    }
    ui->index_pages->setCurrentWidget(ui->main_page);
  });
  connect(ui->score_page_return_btn, &QToolButton::clicked, [this]() {
    ui->index_pages->setCurrentWidget(ui->main_page);
  });
  connect(ui->recent_books_box, &PicBookCoverBox::CoverWidgetClicked,
          this,                 &IndexPage::CoverBoxSignal);
  connect(ui->choose_book_dir_btn, &QPushButton::clicked, [this]() {
    QString book_path =
        QFileDialog::getExistingDirectory(this,
                                          QString::fromLocal8Bit("选择绘本路径"),
                                          "",
                                          QFileDialog::ShowDirsOnly
                                          | QFileDialog::DontResolveSymlinks);
    if (!book_path.isEmpty()) {
      qDebug() << book_path;
      emit BookDirChanged(QDir(book_path));
    }
  });
}

IndexPage::~IndexPage() {
  delete ui;
}

void IndexPage::SetContents(const QJsonArray& jarr) {
  ui->recent_books_box->SetContentsByStringList(ConvertJArrToStringList(jarr));
}

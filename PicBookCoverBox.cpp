#include "PicBookCoverBox.h"
#include "ui_PicBookCoverBox.h"

PicBookCoverBox::PicBookCoverBox(QWidget* parent)
    : QWidget(parent),
      img_loader_(new ImgLoader), img_loading_thd_(new QThread(this)),
      pagi_btns_group_(new QButtonGroup(this)),
      ui(new Ui::PicBookCoverBox) {
  qRegisterMetaType<QFileInfoList>("QFileInfoList");
  qRegisterMetaType<CoverInfo>("CoverInfo");
  setAttribute(Qt::WA_StyledBackground);

  ui->setupUi(this);

  category_dir_.setFilter(
        // 文件    | 非 '.' 或 '..' 目录   | 非符号链接
        QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks
  );
  category_dir_.setSorting(QDir::Name);

  img_loader_->moveToThread(img_loading_thd_);
  connect(this, &PicBookCoverBox::ImgLoadingRequired,
          img_loader_, &ImgLoader::Load);
  connect(img_loader_, &ImgLoader::ImgLoaded,
          this, &PicBookCoverBox::ReceiveCoverInfo);
  connect(img_loader_, &ImgLoader::AddingPagiBtnRequired,
          this, &PicBookCoverBox::AddPagiBtn);

  img_loading_thd_->start();
}

PicBookCoverBox::PicBookCoverBox(const QDir &category_dir, QWidget* parent)
    : PicBookCoverBox(parent) {
  SetContentsByDir(category_dir);
}

PicBookCoverBox::PicBookCoverBox(const QStringList& book_paths, QWidget* parent)
    : PicBookCoverBox(parent) {
  SetContentsByStringList(book_paths);
}

PicBookCoverBox::~PicBookCoverBox() {
  img_loader_->deleteLater();
  img_loading_thd_->requestInterruption();
  img_loading_thd_->quit();
  img_loading_thd_->wait();
  delete ui;
}

void PicBookCoverBox::SetContentsByDir(const QDir &category_dir,
                                       qint32 rows, qint32 cols) {
  if (category_dir_.absolutePath() == category_dir.absolutePath()) return;
  Clear();
  SetCoverWidgets(rows, cols);
  // 读取该分类下的所有书籍
  category_dir_.setPath(category_dir.absolutePath());
  qDebug() << "Enter into " << category_dir_.path();
  LoadImg(category_dir_.entryInfoList());
}

void PicBookCoverBox::SetContentsByStringList(const QStringList& book_paths,
                                              qint32 rows, qint32 cols) {
  QFileInfo book_dir_info;
  QFileInfoList book_dir_infos;
  QString cover_path;

  qDebug() << "Find favorites...";
  for (auto path = book_paths.cbegin();
       path != book_paths.cend(); ++path) {
    book_dir_info.setFile(*path);
    cover_path = *path + "/cover";
    if (book_dir_info.exists()) {
      qDebug() << "  Accepted: " << *path;
      book_dir_infos.append(book_dir_info);
    } else {
      qDebug() << "  Ignored: " << *path << ", which doesn't exist!";
    }
  }

  Clear();
  SetCoverWidgets(rows, cols);
  LoadImg(book_dir_infos);
}

void PicBookCoverBox::Clear() {
  curr_page_ = 0;
  for (auto iter = cover_widgets_.begin();
       iter != cover_widgets_.end(); ++iter) {
    delete *iter;
  }
  for (auto iter = pagi_btns_.begin();
       iter != pagi_btns_.end(); ++iter) {
    delete *iter;
  }
  cover_widgets_.clear();
  pagi_btns_.clear();
  cover_infos_.clear();
}

// 设置第page_num页的封面
void PicBookCoverBox::SetCoversAtPage(qint32 page_num) {
  if (curr_page_ == page_num) return;
  curr_page_ = page_num;
  // start_idx是第page_num页需要显示的第1个封面在cover_infos_中的下标.
  int cnt, start_idx = (page_num - 1) * cover_widgets_.size();
  CoverWidget *tmp_wg;
  for (cnt = 0;
       cnt < cover_widgets_.size() && start_idx + cnt < cover_infos_.size();
       ++cnt) {
    tmp_wg = cover_widgets_[cnt];
    tmp_wg->SetPFileInfo(&cover_infos_[start_idx + cnt].first);
    tmp_wg->SetCover(&cover_infos_[start_idx + cnt].second);
    tmp_wg->SetTitle(cover_infos_[start_idx + cnt].first.fileName());
    tmp_wg->ShowCover();
  }
  // 清空不显示封面和标题的CoverWidget
  for (cnt = cover_infos_.size() - start_idx;
       cnt < cover_widgets_.size();
       ++cnt) {
    cover_widgets_[cnt]->Clear();
  }
}

void PicBookCoverBox::ReceiveCoverInfo(qint32 idx, CoverInfo cover_info) {
  qDebug("Receiving...");
  if (!show_pagi_btns_ && idx >= rows_ * cols_) {
    qDebug("Ignored.");
    return;
  } else cover_infos_.append(cover_info);
  qDebug("Received.");
  if (idx < rows_ * cols_) {
    cover_widgets_[idx]->SetPFileInfo(&cover_infos_.last().first);
    cover_widgets_[idx]->SetCover(&cover_infos_.last().second);
    if (show_title_) cover_widgets_[idx]->SetTitle(cover_infos_.last().first.fileName());
    cover_widgets_[idx]->ShowCover();
  }
}

void PicBookCoverBox::AddPagiBtn(qint32 btn_id) {
  if (!show_pagi_btns_) return ;
  pagi_btns_.append(new PaginationButton(btn_id, this));
  connect(pagi_btns_.last(), &PaginationButton::Clicked,
            this, &PicBookCoverBox::SetCoversAtPage);
  pagi_btns_group_->addButton(pagi_btns_.last());
  if (btn_id == 1) pagi_btns_.last()->toggle();
  ui->pagi_btns_layout->insertWidget(btn_id, pagi_btns_.last());
  qDebug() << "Pagi btn" << btn_id << "added.";
}

void PicBookCoverBox::LoadImg(const QFileInfoList& book_file_info) {
  emit ImgLoadingRequired(rows_, cols_, book_file_info);
}

void PicBookCoverBox::SetCoverWidgets(qint32 rows, qint32 cols) {
  qDebug("PicBookCoverBox::SetCoverWidgets(%d, %d)", rows, cols);
  if (cover_widgets_.size() > 0) {
    qDebug("  Clear cover_widgets...");
    for (auto iter = cover_widgets_.begin();
         iter != cover_widgets_.end();
         ++iter) {
      delete *iter;
    }
    cover_widgets_.clear();
    qDebug("  cover_widgets was cleared.");
  }
  qDebug("  Setting cover_widgets...");
  rows_ = qMax(rows, 1), cols_ = qMax(cols, 1);
  int r, c;
  CoverWidget *tmp_cw;
  for (r = 0; r < rows_; ++r) {
    for (c = 0; c < cols_; ++c) {
      tmp_cw = new CoverWidget(this);
      connect(tmp_cw, &CoverWidget::CoverLabelClicked,
              this, &PicBookCoverBox::CoverWidgetClicked);
      cover_widgets_.append(tmp_cw);
      ui->covers_layout->addWidget(cover_widgets_.last(), r, c, 1, 1);
    }
  }
  qDebug("  cover_widgets was set.");
}

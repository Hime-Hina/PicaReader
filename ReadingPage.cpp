#include "ReadingPage.h"

ReadingPage::ReadingPage(QWidget *parent)
    : AbstractPage(parent), timer_(new QTimer(this)), ui(new Ui::ReadingPage) {
  ui->setupUi(this);
  ui->progress_bar->setMaximum(interval_ / tick_);

  connect(timer_, &QTimer::timeout,
          this, &ReadingPage::IncreaseProgressBarValue);
  connect(this, &ReadingPage::TimeOut, []() {
    qDebug() << "TimeOut";
  });
  connect(this, &ReadingPage::TimeOut,
          this, &ReadingPage::TurnToNxtPage);
  connect(ui->prev_btn, &QToolButton::clicked,
          this, &ReadingPage::OnPrevBtnClicked);
  connect(ui->ctrl_btn, &QToolButton::clicked,
          this, &ReadingPage::OnCtrlBtnClicked);
  connect(ui->nxt_btn, &QToolButton::clicked,
          this, &ReadingPage::OnNxtBtnClicked);
  connect(ui->return_btn, &QToolButton::clicked, [this]() {
    emit Return();
  });
}

ReadingPage::~ReadingPage() {
  delete ui;
}

void ReadingPage::SetContents(const QDir& book_dir) {
  Reset();
  pic_file_infos_ = book_dir.entryInfoList();
  // 把"cover.jpg"移动到列表头.
  pic_file_infos_.push_front(pic_file_infos_.last());
  pic_file_infos_.removeLast();
  qDebug() << "Found pictures:";
  for (const QFileInfo &file_info : pic_file_infos_) {
    qDebug() << "  " << file_info.filePath();
  }
  DisplayPicOfPage(0);
}

void ReadingPage::OnPrevBtnClicked() {
  if (pic_page_num_ > 0) {
    --pic_page_num_;
    StopTimer();
    DisplayPicOfPage(pic_page_num_);
  }
}

void ReadingPage::OnCtrlBtnClicked() {
  if (is_stopped_) {
    qDebug() << "Continue";
    StartTimer();
  } else {
    qDebug() << "Stop";
    StopTimer();
  }
}

void ReadingPage::OnNxtBtnClicked() {
  StopTimer();
  if (pic_page_num_ < pic_file_infos_.size()) {
    ++pic_page_num_;
  }
  if (pic_page_num_ == pic_file_infos_.size()) {
    --pic_page_num_;
    emit CompleteReading();
    return;
  }
  DisplayPicOfPage(pic_page_num_);
}

void ReadingPage::TurnToNxtPage() {
  if (pic_page_num_ < pic_file_infos_.size()) {
    ++pic_page_num_;
  }
  if (pic_page_num_ == pic_file_infos_.size()) {
    --pic_page_num_;
    StopTimer();
    emit CompleteReading();
    return;
  }
  DisplayPicOfPage(pic_page_num_);
}

void ReadingPage::resizeEvent(QResizeEvent*) {
  ui->display_label->setPixmap(
        display_pmap_.scaled(ui->display_label->size(), Qt::KeepAspectRatio)
  );
}

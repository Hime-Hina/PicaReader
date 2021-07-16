#ifndef READINGPAGE_H
#define READINGPAGE_H

#include "AbstractPage.h"
#include "ui_ReadingPage.h"

#include <QWidget>
#include <QDir>
#include <QDebug>
#include <QtMath>
#include <QTimer>

class ReadingPage : public AbstractPage {
  Q_OBJECT

public:
  explicit ReadingPage(QWidget *parent = nullptr);
  ~ReadingPage();

  void SetContents(const QDir &book_dir);
  inline void Reset();
  inline void StartTimer();
  inline void StopTimer();
  inline QToolButton *GetReturnBtn();

protected:
  const qint64 interval_ = 3000; // unit: millisec.
  const qint64 tick_     = 10;   // unit: millisec.
  bool is_stopped_ = false;
  qint32 pic_page_num_ = 0;
  qint64 progress_num_ = 0;
  QPixmap display_pmap_;
  QFileInfoList pic_file_infos_;
  QTimer *timer_;

  inline void DisplayPicOfPage(qint32 page_num);

  void IncreaseProgressBarValue() {
    if (progress_num_ >= ui->progress_bar->maximum()) {
      progress_num_ = 0;
      emit TimeOut();
      return;
    }
    ++progress_num_;
    ui->progress_bar->setValue(progress_num_);
  }
  void OnPrevBtnClicked();
  void OnCtrlBtnClicked();
  void OnNxtBtnClicked();
  void TurnToNxtPage();

  void resizeEvent(QResizeEvent *e) override;

signals:
  void CompleteReading();
  void TimeOut();
private:
  Ui::ReadingPage *ui;
};

void ReadingPage::Reset() {
  pic_page_num_ = 0;
  ui->progress_bar->setValue(0);
  ui->display_label->clear();
  pic_file_infos_.clear();
  StopTimer();
}

void ReadingPage::StartTimer() {
  is_stopped_ = false;
  timer_->setInterval(tick_);
  timer_->start();
  ui->ctrl_btn->setChecked(true);
}

void ReadingPage::StopTimer() {
  is_stopped_ = true;
  timer_->stop();
  progress_num_ = 0;
  ui->progress_bar->setValue(0);
  ui->ctrl_btn->setChecked(false);
}

QToolButton* ReadingPage::GetReturnBtn() {
  return ui->return_btn;
}

void ReadingPage::DisplayPicOfPage(qint32 page_num) {
  if (!(0 <= page_num && page_num < pic_file_infos_.size())) {
    qDebug() << "Page number " << page_num << " is out of index!";
    return ;
  }
  if (display_pmap_.load(pic_file_infos_[page_num].filePath())) {
    qDebug() << QString(
                  "Picture %1 was loaded!"
    ).arg(pic_file_infos_[page_num].fileName());
    ui->display_label->setPixmap(
          display_pmap_.scaled(ui->display_label->size(), Qt::KeepAspectRatio)
    );
  } else {
    qDebug() << QString(
                  "Error: Can not load Picture %1!"
    ).arg(pic_file_infos_[page_num].filePath());
  }
}

#endif // READINGPAGE_H

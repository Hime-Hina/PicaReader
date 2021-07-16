#ifndef COVERWIDGET_H
#define COVERWIDGET_H

#include "ui_CoverWidget.h"

#include <QResizeEvent>
#include <QString>
#include <QWidget>
#include <QFileInfo>
#include <QtDebug>

class CoverWidget : public QWidget {
  Q_OBJECT
public:
  explicit CoverWidget(QWidget *parent = nullptr);
  ~CoverWidget();

  inline void SetCover(QPixmap *ppixmap_);
  inline void ShowCover();
  inline void Clear();
  inline void SetTitle(const QString &title);
  inline void SetPFileInfo(QFileInfo *pfile_info_);
  inline void SetShowTitle(bool flag);

  void SendCoverLabelClicked();

protected:
  bool show_title_       = false;
  QFileInfo *pfile_info_ = nullptr;

private:
  Ui::CoverWidget *ui;

signals:
  void CoverLabelClicked(const QFileInfo &book_file_info);
};

void CoverWidget::SetCover(QPixmap *ppixmap) {
  ui->cover_label->SetCover(ppixmap);
  ui->cover_label->setCursor(Qt::PointingHandCursor);
}

void CoverWidget::ShowCover() {
  ui->cover_label->ShowCover();
}

void CoverWidget::Clear() {
  pfile_info_ = nullptr;
  ui->cover_label->Clear();
  ui->title_label->clear();
  ui->title_label->setCursor(Qt::ArrowCursor);
}

void CoverWidget::SetTitle(const QString &title) {
  SetShowTitle(true);
  if (!show_title_) return;
  ui->title_label->setText(title);
  ui->title_label->setCursor(Qt::PointingHandCursor);
}

void CoverWidget::SetPFileInfo(QFileInfo* pfile_info) {
  pfile_info_ = pfile_info;
}

void CoverWidget::SetShowTitle(bool flag) {
  show_title_ = flag;
  ui->title_label->setEnabled(show_title_);
}


#endif // COVERLABEL_H

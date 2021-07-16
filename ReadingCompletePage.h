#ifndef READINGCOMPLETEPAGE_H
#define READINGCOMPLETEPAGE_H

#include "ui_ReadingCompletePage.h"
#include "AbstractPage.h"

#include <QWidget>

class ReadingCompletePage : public AbstractPage {
  Q_OBJECT

public:
  explicit ReadingCompletePage(QWidget *parent = nullptr);
  ~ReadingCompletePage();

  void SetContents(const QDir &books_dir) override;
  void SetFavoriteBtn(bool on);
  inline QToolButton *GetReturnBtn();

protected:
  QPixmap pic_;
  void resizeEvent(QResizeEvent *e) override;
private:
  Ui::ReadingCompletePage *ui;
signals:
  void NxtBook();
  void Rewatch();
  void AddToFavorites();
  void RemoveFromFavorites();
};

QToolButton *ReadingCompletePage::GetReturnBtn() {
  return ui->return_btn;
}

#endif // READINGCOMPLETEPAGE_H

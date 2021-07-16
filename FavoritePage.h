#ifndef FAVORITEWIDGET_H
#define FAVORITEWIDGET_H

#include "AbstractPage.h"
#include "ui_FavoritePage.h"

#include <QWidget>

class FavoritePage : public AbstractPage {
  Q_OBJECT

public:
  explicit FavoritePage(QWidget *parent = nullptr);
  ~FavoritePage();

  void SetContents(const QJsonArray &raw_book_paths) override;

private:
  Ui::FavoritePage *ui;
};

#endif // FAVORITEWIDGET_H

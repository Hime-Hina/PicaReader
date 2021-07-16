#ifndef INDEXPAGE_H
#define INDEXPAGE_H

#include "AbstractPage.h"
#include "ui_IndexPage.h"

#include <QWidget>
#include <QFileDialog>

namespace Ui {
  class IndexPage;
}

class IndexPage : public AbstractPage {
  Q_OBJECT

public:
  explicit IndexPage(QWidget *parent = nullptr);
  ~IndexPage();

  void SetContents(const QJsonArray &jarr) override;
  inline void SetPFavorites(QJsonArray *f);
  inline void SetOwner(const QString &owner);
  inline void SetEquipName(const QString &equip);
  inline void SetScore(qint32 score);

protected:
  QString curr_owner_;
  QString curr_equip_name_;

private:
  Ui::IndexPage *ui;
signals:
  void BookDirChanged(QDir book_dir);
  void OwnerChanged(QString name);
  void EquipNameChanged(QString name);
};

void IndexPage::SetOwner(const QString& owner) {
  curr_owner_ = owner;
  ui->owner_label->setText(owner);
}

void IndexPage::SetEquipName(const QString& equip) {
  curr_equip_name_ = equip;
  ui->equip_label->setText(equip);
}

void IndexPage::SetScore(qint32 score) {
  ui->score_label->setText(QString::fromLocal8Bit(
        "<br><br><br><br><font size=10>%1</font><br><font size=5>积分</font>"
                             ).arg(score)
  );
  ui->score_btn->setText(QString::fromLocal8Bit("积分: ") + QString::number(score));
}

#endif // INDEXPAGE_H

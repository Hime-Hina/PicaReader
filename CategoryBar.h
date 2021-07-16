#ifndef CATEGORYBAR_H
#define CATEGORYBAR_H

#include "CategoryButton.h"

#include <QButtonGroup>
#include <QWidget>
#include <QFrame>
#include <QToolButton>
#include <QDir>
#include <QList>
#include <QSizePolicy>

namespace Ui {
  class CategoryBar;
}

class CategoryBar : public QWidget {
  Q_OBJECT

  using CategoryBtns = QList<CategoryButton *>;
  using CategoryBtnsIter = QList<CategoryButton *>::Iterator;
  using CategoryBtnsConstIter = QList<CategoryButton *>::ConstIterator;
public:
  explicit CategoryBar(QWidget *parent = nullptr);
  CategoryBar(QDir &books_dir, QWidget *parent = nullptr);
  ~CategoryBar();

  void AddBtnsByDir(const QDir &books_dir);
  void Clear();

  inline int CountBtns() const {
    return tool_btns_.size();
  }
  inline CategoryButton* operator[](int id) const {
    return  tool_btns_[id];
  }
  inline CategoryBtnsConstIter cbegin() const {
    return tool_btns_.cbegin();
  }
  inline CategoryBtnsConstIter cend() const {
    return tool_btns_.cend();
  }
  inline CategoryBtnsIter begin() {
    return tool_btns_.begin();
  }
  inline CategoryBtnsIter end() {
    return tool_btns_.end();
  }

protected:
  CategoryBtns tool_btns_;
  QButtonGroup *category_btns_grp_;

private:
  Ui::CategoryBar *ui;
};

#endif // CATEGORYBAR_H

#ifndef CATEGORYBUTTON_H
#define CATEGORYBUTTON_H

#include "PicBookCoverBox.h"

#include <QToolButton>

class CategoryButton : public QToolButton {
  Q_OBJECT
public:
  CategoryButton(QWidget *parent = nullptr);

  inline void SetFileInfo(QFileInfo info) {
    cover_box_file_info_ = info;
  }
  inline QFileInfo GetFileInfo() const {
    return cover_box_file_info_;
  }
  inline void SetCoverBox(PicBookCoverBox *cover_box) {
    cover_box_ = cover_box;
  }
  inline PicBookCoverBox *GetCoverBox() const {
    return cover_box_;
  }

protected:
  QFileInfo cover_box_file_info_;
  PicBookCoverBox *cover_box_ = nullptr;
private:
};

#endif // CATEGORYBUTTON_H

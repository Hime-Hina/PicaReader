#ifndef STORYPAGE_H
#define STORYPAGE_H

#include "AbstractPage.h"
#include "PicBookCoverBox.h"

#include <QWidget>

namespace Ui {
  class StoryPage;
}

class StoryPage : public AbstractPage {
  Q_OBJECT

public:
  explicit StoryPage(QWidget *parent = nullptr);
  ~StoryPage();

  void SetContents(const QDir &books_dir);
  void Clear();

private:
  Ui::StoryPage *ui;
};

#endif // STORYPAGE_H

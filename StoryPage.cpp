#include "ui_StoryPage.h"
#include "StoryPage.h"

StoryPage::StoryPage(QWidget *parent)
    : AbstractPage(parent), ui(new Ui::StoryPage) {
  ui->setupUi(this);
}

StoryPage::~StoryPage() {
}

void StoryPage::SetContents(const QDir& books_dir) {
  ui->category_bar->AddBtnsByDir(books_dir);
  if (ui->category_bar->begin() != ui->category_bar->end()) {
    (*ui->category_bar->begin())->toggle();
  }

  PicBookCoverBox *story_page_cover_box;
  QDir category_dir;
  for (auto ibtn = ui->category_bar->cbegin();
       ibtn != ui->category_bar->cend();
       ++ibtn) {
    category_dir.setPath((*ibtn)->GetFileInfo().absoluteFilePath());
    story_page_cover_box = new PicBookCoverBox(category_dir);
    (*ibtn)->SetCoverBox(story_page_cover_box);

    ui->story_page_cover_boxes->addWidget(story_page_cover_box);
    connect(*ibtn, &CategoryButton::clicked, [this, story_page_cover_box]() {
      ui->story_page_cover_boxes->setCurrentWidget(story_page_cover_box);
    });
    connect(story_page_cover_box, &PicBookCoverBox::CoverWidgetClicked,
            this, &StoryPage::CoverBoxSignal);
  }
}

void StoryPage::Clear() {
  ui->category_bar->Clear();
  qDeleteAll(findChildren<PicBookCoverBox *>());
}

#include "CategoryBar.h"
#include "ui_CategoryBar.h"

CategoryBar::CategoryBar(QWidget *parent)
    : QWidget(parent),
      category_btns_grp_(new QButtonGroup(this)),
      ui(new Ui::CategoryBar) {
  ui->setupUi(this);

  setAttribute(Qt::WA_StyledBackground, true);
}

CategoryBar::CategoryBar(QDir& books_dir, QWidget* parent)
    : CategoryBar(parent) {
  AddBtnsByDir(books_dir);
}

CategoryBar::~CategoryBar() {
  delete ui;
}

void CategoryBar::AddBtnsByDir(const QDir& books_dir) {
  QFileInfoList file_infos = books_dir.entryInfoList();

  CategoryButton *cbtn;
  for (int cnt = 0; cnt < file_infos.size(); ++cnt) {
    cbtn = new CategoryButton(this);
    cbtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    cbtn->setText(file_infos[cnt].fileName());
    cbtn->SetFileInfo(file_infos[cnt]);
    tool_btns_.append(cbtn);
    category_btns_grp_->addButton(cbtn);
    ui->category_labels_layout->insertWidget(cnt + 1, cbtn);
  }
}

void CategoryBar::Clear() {
  for (auto iter = tool_btns_.begin();
       iter != tool_btns_.end();
       ++iter) {
    delete *iter;
  }
  tool_btns_.clear();
}

#include "Sidebar.h"

Sidebar::Sidebar(QWidget *parent)
    : QWidget(parent), btn_group(new QButtonGroup(this)), ui(new Ui::Sidebar) {
  setAttribute(Qt::WA_StyledBackground);
  ui->setupUi(this);
  ui->index_btn->SetIcon(":/images/index");
  ui->story_btn->SetIcon(":/images/story");
  ui->music_btn->SetIcon(":/images/music");
  ui->guoxue_btn->SetIcon(":/images/guoxue");
  ui->favorites_btn->SetIcon(":/images/favorite");
  btn_group->addButton(ui->index_btn);
  btn_group->addButton(ui->story_btn);
  btn_group->addButton(ui->music_btn);
  btn_group->addButton(ui->guoxue_btn);
  btn_group->addButton(ui->favorites_btn);
  ui->index_btn->click();
}

Sidebar::~Sidebar() {
  delete ui;
}

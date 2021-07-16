#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "ui_Sidebar.h"

#include <QWidget>

namespace Ui {
  class Sidebar;
}

class Sidebar : public QWidget {
  Q_OBJECT

public:
  explicit Sidebar(QWidget *parent = nullptr);
  ~Sidebar();

  inline SidebarButton *IndexBtn() {
    return ui->index_btn;
  }
  inline SidebarButton *StoryBtn() {
    return ui->story_btn;
  }
  inline SidebarButton *MusicBtn() {
    return ui->music_btn;
  }
  inline SidebarButton *GuoxueBtn() {
    return ui->guoxue_btn;
  }
  inline SidebarButton *FavoritesBtn() {
    return ui->favorites_btn;
  }

protected:
  QButtonGroup *btn_group = nullptr;
private:
  Ui::Sidebar *ui;
};

#endif // SIDEBAR_H

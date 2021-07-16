#include "SidebarButton.h"

SidebarButton::SidebarButton(QWidget* parent,
                             const QString& icon_path)
    : QToolButton(parent), icon_path_(icon_path) {
  setFocusPolicy(Qt::NoFocus);
  connect(this, &SidebarButton::clicked, [this]() {
    emit Checked(this);
  });
}

void SidebarButton::SetIcon(const QString& icon_path) {
  icon_path_ = icon_path;
  QIcon icon;
  if (icon_.load(icon_path_)) {
    qDebug() << QString("Image %1 as a icon was loaded.").arg(icon_path_);
    icon.addPixmap(icon_);
    setIcon(icon);
  }
}

void SidebarButton::resizeEvent(QResizeEvent* e) {
  if (!icon_path_.isEmpty()) {
    setMask(QRegion(0, 0, this->width(), this->height(), QRegion::Ellipse));
    setIconSize(size() / 2);
  } else QToolButton::resizeEvent(e);
}

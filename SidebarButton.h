#ifndef SIDEBUTTON_H
#define SIDEBUTTON_H

#include <QtGui>
#include <QtWidgets>

class SidebarButton: public QToolButton {
  Q_OBJECT
public:
  SidebarButton(QWidget *parent = nullptr,
                const QString &icon_path = QString());
  void SetIcon(const QString &icon_path);
protected:
  QString icon_path_;
  QPixmap icon_;

  void resizeEvent(QResizeEvent *e) override;
signals:
  void Checked(SidebarButton *self);
};

#endif // SIDEBUTTON_H

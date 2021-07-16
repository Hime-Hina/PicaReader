#ifndef COVERLABEL_H
#define COVERLABEL_H

#include <QLabel>

class CoverLabel : public QLabel {
  Q_OBJECT
public:
  explicit CoverLabel(QWidget *parent = nullptr);

  inline void Clear();
  inline void SetCover(QPixmap *ppixmap);
  inline void ShowCover();

protected:
  QPixmap *ppixmap_ = nullptr;

  void mouseReleaseEvent(QMouseEvent *e) override;
  void resizeEvent(QResizeEvent *e) override;
signals:
  void clicked();
};

void CoverLabel::Clear() {
  ppixmap_ = nullptr;
  clear();
  setCursor(Qt::ArrowCursor);
}

void CoverLabel::SetCover(QPixmap* ppixmap) {
  ppixmap_ = ppixmap;
  setCursor(Qt::PointingHandCursor);
}

void CoverLabel::ShowCover() {
  if (ppixmap_) {
    setPixmap(ppixmap_->scaled(size(), Qt::KeepAspectRatio));
  }
}

#endif // COVERLABEL_H

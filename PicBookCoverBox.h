#ifndef PICBOOKCOVERBOX_H
#define PICBOOKCOVERBOX_H

#include "ImgLoader.h"
#include "CoverWidget.h"
#include "PaginationButton.h"

#include <QButtonGroup>
#include <QMetaType>
#include <QWidget>
#include <QJsonArray>
#include <QtMath>
#include <QDir>
#include <QResizeEvent>
#include <QJsonDocument>
#include <QMap>
#include <QFileInfo>
#include <QThread>
#include <QDebug>

namespace Ui {
  class PicBookCoverBox;
}

class PicBookCoverBox : public QWidget {
  Q_OBJECT
  using PCoverWidgets = QList<CoverWidget *>;
  using PPagiBtns     = QList<PaginationButton *>;
public:
  explicit PicBookCoverBox(QWidget *parent = nullptr);
  PicBookCoverBox(const QDir &category_dir, QWidget *parent = nullptr); // Common page.
  PicBookCoverBox(const QStringList &book_paths, QWidget *parent = nullptr); // Favorite page.
  ~PicBookCoverBox();

  inline void SetShowTitle(bool flag);
  inline void SetShowPagiBtns(bool flag);

  void Clear();
  void SetContentsByDir(const QDir &category_dir,
                        qint32 rows = 2, qint32 cols = 4);
  void SetContentsByStringList(const QStringList &book_paths,
                               qint32 rows = 2, qint32 cols = 4);
  void SetCoverWidgets(qint32 rows, qint32 cols);
  void SetCoversAtPage(qint32 page_num = 1);

protected:
  qint32        rows_             = 0;
  qint32        cols_             = 0;
  qint32        curr_page_        = 0; // 当前的显示页数
  qint32        cover_cnt_        = 0; // 统计已显示的CoverWidget
  bool          show_pagi_btns_   = true;
  bool          show_title_       = true;
  QDir          category_dir_;
  ImgLoader     *img_loader_      = nullptr;
  QThread       *img_loading_thd_ = nullptr;
  CoverInfos    cover_infos_;
  PCoverWidgets cover_widgets_;
  PPagiBtns     pagi_btns_;
  QButtonGroup  *pagi_btns_group_;

  void ReceiveCoverInfo(qint32 idx, CoverInfo cover_info);
  void AddPagiBtn(qint32 id);
  void LoadImg(const QFileInfoList &book_file_info);

signals:
  void CoverWidgetClicked(const QFileInfo &book_file_info);
  void ImgLoadingRequired(qint32 rows, qint32 cols,
                         const QFileInfoList &book_dir_infos);

private:
  Ui::PicBookCoverBox *ui;
};

void PicBookCoverBox::SetShowTitle(bool flag) {
  show_title_ = flag;
}

void PicBookCoverBox::SetShowPagiBtns(bool flag) {
  show_pagi_btns_= flag;
}

#endif // PICBOOKCOVERBOX_H

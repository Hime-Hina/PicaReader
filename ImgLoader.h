#ifndef IMGLOADER_H
#define IMGLOADER_H

#include <QObject>
#include <QMap>
#include <QFileInfo>
#include <QPixmap>
#include <QImageReader>
#include <QDir>
#include <QDebug>

using CoverInfo     = QPair<QFileInfo, QPixmap>;
using CoverInfos    = QList<CoverInfo>;

class ImgLoader : public QObject {
  Q_OBJECT
public:
  ImgLoader(QObject *parent = nullptr);

  void Load(qint32 rows, qint32 cols, const QFileInfoList &book_dir_infos);
protected:
  QMap<QString, QImage> img_pool_;
  QImage img_;
signals:
  void ImgLoaded(qint32 idx, CoverInfo cover_info);
  void AddingPagiBtnRequired(qint32 btn_id);
  void AllDone(qint32 page = 1);
};

#endif // IMGLOADER_H

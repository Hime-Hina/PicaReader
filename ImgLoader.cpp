#include "ImgLoader.h"

ImgLoader::ImgLoader(QObject* parent)
  : QObject(parent) {
}

void ImgLoader::Load(qint32 rows, qint32 cols,
                     const QFileInfoList& book_dir_infos) {
  const qint32 covers_per_page = rows * cols;
  qint32 cnt = 0;
  QPixmap pmap;
  QString cover_path;

  for (auto iinfo = book_dir_infos.cbegin();
       iinfo != book_dir_infos.cend(); ++iinfo) {
    qDebug() << QString("  Book %1 was found.").arg(iinfo->absoluteFilePath());
    cover_path = iinfo->absoluteFilePath() + "/cover";
    if (pmap.load(cover_path)) {
      if (cnt % covers_per_page == 0) {
        emit AddingPagiBtnRequired(cnt / covers_per_page + 1);
        qDebug() << "  Adding pagi btn" << cnt / covers_per_page + 1 << " required.";
      }
      emit ImgLoaded(cnt, QPair<QFileInfo, QPixmap>(*iinfo, pmap));
      qDebug() << QString("  Book cover %1 was loaded.").arg(cover_path);
      ++cnt;
    }
  }
  emit AllDone();
}

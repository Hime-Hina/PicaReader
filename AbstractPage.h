#ifndef ABSTRACTPAGE_H
#define ABSTRACTPAGE_H

#include <QWidget>
#include <QFileInfo>
#include <QDebug>
#include <QJsonArray>

class AbstractPage : public QWidget {
  Q_OBJECT
public:
  explicit AbstractPage(QWidget *parent = nullptr);
  virtual ~AbstractPage();
  virtual void SetContents(const QDir &dir);
  virtual void SetContents(const QJsonArray &jarr);
protected:
  QStringList ConvertJArrToStringList(const QJsonArray &jarr);
signals:
  void Return();
  void CoverBoxSignal(const QFileInfo &book_file_info);
};

#endif // ABSTRACTPAGE_H

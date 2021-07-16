#include "AbstractPage.h"

AbstractPage::AbstractPage(QWidget *parent)
  : QWidget(parent) {
}

AbstractPage::~AbstractPage() {
}

void AbstractPage::SetContents(const QDir&) {
  qDebug("Don't call AbstractPage::SetContents(const QDir &) directly!");
}

void AbstractPage::SetContents(const QJsonArray&) {
  qDebug("Don't call AbstractPage::SetContents(const QJsonArray &) directly!");
}

QStringList AbstractPage::ConvertJArrToStringList(const QJsonArray& jarr) {
  QStringList str_list;
  QString qstr_path;

  for (auto iter = jarr.cbegin();
       iter != jarr.cend();
       ++iter) {
    if (iter->isString()) {
      qstr_path = iter->toString();
      str_list.append(qstr_path);
      qDebug() << "  Accepted: " << qstr_path;
    } else {
      qDebug() << "  Ignored: " << *iter << ", which isn't a string!";
    }
  }
  return str_list;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "AbstractPage.h"
#include "SidebarButton.h"

#include <QtGui>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow: public QWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr, const QString &styl_path = QString());
  ~MainWindow();

protected:
  static const QString books_path_;
  static const QString data_file_path_;
  QDir curr_book_dir_;
  QDir curr_category_dir_;
  QDir books_dir_;
  QFile data_file_;
  QJsonDocument data_;
  qint32 score_;
  QString owner_, equip_;
  bool favorites_changed = true;
  QJsonArray favorite_book_path_jarr_;

  void ReadDataFile();
  void WriteDataFile();
  void EnterReadingMode(const QFileInfo &book_file_info);
  void ReturnToMainPage();
  void SetOwner(QString owner);
  void SetEquipName(QString name);
  void SetBookDir(QDir books_dir);
  void ShowFavorites();

  inline void BtnBindWithPage(SidebarButton *btn, AbstractPage* page);
  inline void PageBindWithReadingPage(AbstractPage *page);

  static qint32  FindItemInJArr(const QJsonArray &jarr, const QJsonValue &item);
  static QString ReadStyleSheet(const QString &styl_path);
  static inline bool DoesExistFile(const QString& file_path); // 判断是否存在文件
  static inline QJsonObject GetDefaultData();

private:
  Ui::MainWindow *ui;
};

void MainWindow::BtnBindWithPage(SidebarButton *btn, AbstractPage *page) {
  connect(btn, &SidebarButton::clicked, [this, page]() {
    ui->right_pages->setCurrentWidget(page);
  });
}

void MainWindow::PageBindWithReadingPage(AbstractPage* page) {
  connect(page, &AbstractPage::CoverBoxSignal,
          this, &MainWindow::EnterReadingMode);
}

#endif // MAINWINDOW_H

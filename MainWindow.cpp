#include "MainWindow.h"

const QString MainWindow::books_path_ = "C:/Users/HIMEHINA/Desktop/book";
const QString MainWindow::data_file_path_ = "data.json";

MainWindow::MainWindow(QWidget *parent, const QString &styl_path)
    : QWidget(parent),
      ui(new Ui::MainWindow) {
  setAttribute(Qt::WA_StyledBackground, true);
  setStyleSheet(ReadStyleSheet(styl_path));
  ReadDataFile();

  ui->setupUi(this);

  books_dir_.setSorting(QDir::Name);
  books_dir_.setFilter(
       QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks
  );
  curr_book_dir_.setSorting(QDir::Name);
  curr_book_dir_.setFilter(
        QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks
  );
  curr_book_dir_.setNameFilters({"*.jpg", "*.jpeg", "*.png"});
  curr_category_dir_.setSorting(QDir::Name);
  curr_category_dir_.setFilter(
        QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks
  );

  ui->index_page->SetScore(score_);
  ui->index_page->SetOwner(owner_);
  ui->index_page->SetEquipName(equip_);
  ui->index_page->SetContents(favorite_book_path_jarr_);
  ui->story_page->SetContents(books_dir_);

  BtnBindWithPage(ui->sidebar->IndexBtn(), ui->index_page);
  BtnBindWithPage(ui->sidebar->StoryBtn(), ui->story_page);
  BtnBindWithPage(ui->sidebar->MusicBtn(), ui->story_page);
  BtnBindWithPage(ui->sidebar->GuoxueBtn(), ui->story_page);
  BtnBindWithPage(ui->sidebar->FavoritesBtn(), ui->favorite_page);
  connect(ui->sidebar->FavoritesBtn(), &SidebarButton::clicked,
          this, &MainWindow::ShowFavorites);
  connect(ui->ending_page->GetReturnBtn(), &QToolButton::clicked,
          this, &MainWindow::ShowFavorites);
  connect(ui->reading_page->GetReturnBtn(), &QToolButton::clicked,
          this, &MainWindow::ShowFavorites);

  PageBindWithReadingPage(ui->index_page);
  PageBindWithReadingPage(ui->story_page);
  PageBindWithReadingPage(ui->favorite_page);
  PageBindWithReadingPage(ui->ending_page);
  connect(ui->index_page, &IndexPage::OwnerChanged,
          this, &MainWindow::SetOwner);
  connect(ui->index_page, &IndexPage::EquipNameChanged,
          this, &MainWindow::SetEquipName);
  connect(ui->index_page, &IndexPage::BookDirChanged,
          this,           &MainWindow::SetBookDir);
  connect(ui->reading_page, &ReadingPage::Return,
          this, &MainWindow::ReturnToMainPage);
  connect(ui->reading_page, &ReadingPage::CompleteReading, [this]() {
    score_ += 10;
    ui->index_page->SetScore(score_);
    ui->ending_page->SetFavoriteBtn(
          favorite_book_path_jarr_.contains(QJsonValue(curr_book_dir_.path()))
    );
    ui->ending_page->SetContents(curr_category_dir_);
    ui->main_pages->setCurrentWidget(ui->ending_page);
  });
  connect(ui->ending_page, &ReadingCompletePage::Return,
          this, &MainWindow::ReturnToMainPage);
  connect(ui->ending_page, &ReadingCompletePage::Rewatch, [this]() {
    ui->reading_page->Reset();
    ui->reading_page->SetContents(curr_book_dir_);
    ui->main_pages->setCurrentWidget(ui->reading_page);
  });
  connect(ui->ending_page, &ReadingCompletePage::AddToFavorites, [this]() {
    if (!favorite_book_path_jarr_.contains(QJsonValue(curr_book_dir_.path()))) {
      favorite_book_path_jarr_.append(curr_book_dir_.path());
      favorites_changed = true;
      qDebug() << "Add: " << favorite_book_path_jarr_.last();
    }
  });
  connect(ui->ending_page, &ReadingCompletePage::RemoveFromFavorites, [this]() {
    qint32 idx = FindItemInJArr(favorite_book_path_jarr_, QJsonValue(curr_book_dir_.path()));
    if (idx != -1) {
      qDebug() << "Remove: " << favorite_book_path_jarr_.at(idx);
      favorite_book_path_jarr_.removeAt(idx);
      favorites_changed = true;
    }
  });
}

MainWindow::~MainWindow() {
  WriteDataFile();
  delete ui;
}

void MainWindow::ReadDataFile() {
  data_file_.setFileName(data_file_path_);
  if (data_file_.open(QIODevice::ReadWrite)) {
    qDebug() << QString("Data file %1 was opened!").arg(data_file_.fileName());
    data_ = QJsonDocument::fromBinaryData(data_file_.readAll());
    qDebug() << "Data file was read!";
    // 设置图书路径
    books_dir_.setPath(data_["books_path"].toString(books_path_));
    score_ = data_["score"].toInt(0);
    owner_ = data_["username"].toString(QString::fromLocal8Bit("用户名"));
    equip_ = data_["equip_name"].toString(QString::fromLocal8Bit("设备名"));
    favorite_book_path_jarr_ = data_["favorite_books"].toArray(QJsonArray());
  } else {
    qDebug() << QString("Can not open Data file %1!").arg(data_file_.fileName());
  }
  data_file_.close();
}

void MainWindow::WriteDataFile() {
  QJsonObject new_data;
  new_data.insert("username", owner_);
  new_data.insert("equip_name", equip_);
  new_data.insert("books_path", books_dir_.absolutePath());
  new_data.insert("favorite_books", favorite_book_path_jarr_);
  new_data.insert("score", score_);

  data_.setObject(new_data);
  data_file_.setFileName(data_file_path_);
  if (data_file_.open(QFile::WriteOnly)) {
    qDebug("Data file was opened.");
    if (data_file_.write(data_.toBinaryData())) {
      qDebug() << "Data file was written.";
    }
  }
  data_file_.close();
}

void MainWindow::EnterReadingMode(const QFileInfo& book_file_info) {
  curr_book_dir_.setPath(book_file_info.filePath());
  curr_category_dir_.setPath(book_file_info.absoluteDir().absolutePath());
  ui->reading_page->SetContents(curr_book_dir_);
  ui->main_pages->setCurrentWidget(ui->reading_page);
}

void MainWindow::ReturnToMainPage() {
  ui->main_pages->setCurrentWidget(ui->main_page);
}

void MainWindow::SetOwner(QString owner) {
  owner_ = owner;
}

void MainWindow::SetEquipName(QString name) {
  equip_ = name;
}

void MainWindow::SetBookDir(QDir books_dir) {
  if (books_dir_ != books_dir) {
    books_dir_ = books_dir;
    books_dir_.setSorting(QDir::Name);
    books_dir_.setFilter(
         QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks
    );
    ui->story_page->Clear();
    ui->story_page->SetContents(books_dir_);
  }
}

void MainWindow::ShowFavorites() {
  if (favorites_changed) {
    ui->favorite_page->SetContents(favorite_book_path_jarr_);
    favorites_changed = false;
  }
}

qint32 MainWindow::FindItemInJArr(const QJsonArray& jarr, const QJsonValue& item) {
  qint32 cnt = 0;
  for (auto iter = jarr.cbegin(); iter != jarr.end(); ++iter) {
    if (*iter == item) {
      return cnt;
    }
    ++cnt;
  }
  return -1;
}

QString MainWindow::ReadStyleSheet(const QString &styl_path) {
  if (styl_path.isEmpty()) return QString(); // 路径为空,不读取

  QFile styl_file(styl_path);
  if (styl_file.open(QFile::ReadOnly)) {
    qDebug() << QString("Style sheet %1 was loaded.").arg(styl_path);
    // 转换成QString
    QString styl = QString::fromUtf8(styl_file.readAll());
    qDebug() << "Style sheet was read.";
    styl_file.close();
    return styl;
  }
  return QString();
}

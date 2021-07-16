#include "GlobalApplication.h"

GlobalApplication::GlobalApplication(int& argc, char** argv)
    : QApplication(argc, argv),
      timer_thd_(new QThread(this)), timer_controller_(new TimerController) {
  timer_controller_->moveToThread(timer_thd_);
  timer_controller_->SetInterval();
  connect(timer_thd_, &QThread::started, [this]() {
    timer_controller_->Start();
  });
  connect(timer_controller_, &TimerController::Timeout,
          this,   &GlobalApplication::LockWindow);
  connect(this, &GlobalApplication::StartTimer,
          timer_controller_, &TimerController::Start);
  connect(this, &GlobalApplication::StopTimer,
          timer_controller_, &TimerController::Stop);
}

GlobalApplication::~GlobalApplication() {
  timer_thd_->requestInterruption();
  timer_thd_->quit();
  timer_thd_->wait();
  if (outer_widget_) delete outer_widget_;
}

void GlobalApplication::Run() {
  QPixmap opening_pix(":/images/opening");
  QSplashScreen opening_scr(opening_pix);

  outer_widget_ = new QWidget;
  outer_widget_->resize(1448, 875);

  lck_scr_ = new LockScreen(outer_widget_);
  lock_layout_ = new QStackedLayout(outer_widget_);

  lock_layout_->setStackingMode(QStackedLayout::StackAll);
  lock_layout_->addWidget(lck_scr_);
  lck_scr_->hide();

  opening_scr.show();
  mw_ = new MainWindow(outer_widget_, ":/css/styl");

  lock_layout_->addWidget(mw_);

  opening_scr.finish(outer_widget_);
  outer_widget_->show();
  outer_widget_->move(
        (QApplication::desktop()->width() - outer_widget_->width()) / 2,
        (QApplication::desktop()->height() - outer_widget_->height()) / 2
  );

  timer_thd_->start();
}

void GlobalApplication::LockWindow() {
  if (is_locked) {
    qDebug("Ignored: LockWindow().");
  } else {
    qDebug("Accepted: LockWindow().");
    lck_scr_->show();
    is_locked = true;
  }
}

bool GlobalApplication::notify(QObject* obj, QEvent* e) {
  if (obj->objectName().right(6) == obj_filter_str_) {
    if (e->type() == QEvent::MouseButtonPress
        || e->type() == QEvent::KeyPress) {
      emit StopTimer();
      if (is_locked) return true;
    } else if (e->type() == QEvent::MouseButtonRelease
        || e->type() == QEvent::KeyRelease) {
      is_locked = false;
      emit StartTimer();
      lck_scr_->hide();
      if (is_locked) return true;
    } else if (e->type() == QEvent::MouseMove) {
      emit StartTimer();
      if (is_locked) return true;
    }
  }
  return QApplication::notify(obj, e);
}

TimerController::TimerController(QObject* parent)
  : QObject(parent) {
}

TimerController::~TimerController() {
}

void TimerController::Start() {
  if (timer_ == nullptr) {
    timer_ = new QTimer;
    timer_->setInterval(timeout_);
    connect(timer_, &QTimer::timeout,
            this,   &TimerController::Timeout);
  }
  timer_->start();
}

void TimerController::Stop() {
  if (timer_ != nullptr) {
    timer_->stop();
  }
}

void TimerController::SetInterval(qint32 timeout) {
  timeout_ = timeout;
}

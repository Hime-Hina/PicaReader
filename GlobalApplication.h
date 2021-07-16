#ifndef GLOBALAPPLICATION_H
#define GLOBALAPPLICATION_H

#include "LockScreen.h"
#include "MainWindow.h"

#include <QApplication>
#include <QWindow>
#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QTimer>

class TimerController : public QObject {
  Q_OBJECT
public:
  explicit TimerController(QObject *parent = nullptr);
  ~TimerController();

  void Start();
  void Stop();
  void SetInterval(qint32 timeout = 4000);
protected:
  qint32 timeout_;
  QTimer *timer_ = nullptr;
signals:
  void Timeout();
};

class GlobalApplication : public QApplication {
  Q_OBJECT
public:
  GlobalApplication(int &argc, char **argv);
  ~GlobalApplication();

  void Run();
protected:
  const QString obj_filter_str_ = "Window";
  bool is_locked  = false;
  QThread *timer_thd_;
  TimerController *timer_controller_;

  LockScreen *lck_scr_;
  QWidget *outer_widget_ = nullptr;
  MainWindow *mw_ = nullptr;
  QStackedLayout *lock_layout_;

  void LockWindow();

  bool notify(QObject *obj, QEvent *e) override;
signals:
  void StartTimer();
  void StopTimer();
};

#endif // GLOBALAPPLICATION_H

#include "GlobalApplication.h"

#include <QtGui>
#include <QtWidgets>
#include <QTimer>

int main(int argc, char *argv[]) {
  GlobalApplication a(argc, argv);
  a.Run();
  return a.exec();
}

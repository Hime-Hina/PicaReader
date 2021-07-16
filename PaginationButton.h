#ifndef PAGINATIONBUTTON_H
#define PAGINATIONBUTTON_H

#include <QPushButton>

class PaginationButton: public QPushButton {
  Q_OBJECT
public:
  explicit PaginationButton(qint32 id, QWidget *parent = nullptr);

protected:
  void SendPageNum();

private:
  int _id = 0;
signals:
  void Clicked(qint32 id);
};

#endif // PAGINATIONBUTTON_H

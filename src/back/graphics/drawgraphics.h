#ifndef DRAWGRAPHICS_H
#define DRAWGRAPHICS_H

#include <QDialog>
extern "C" {
#include "../polish/polish.h"
#include "../polish/stack.h"
#include "../polish/tokenize.h"
}

namespace Ui {
class DrawGraphics;
}

class DrawGraphics : public QDialog {
  Q_OBJECT

 public:
  explicit DrawGraphics(QWidget *parent = nullptr);
  ~DrawGraphics();

 private slots:
  void onDrawClicked();

 public slots:
  void getQuationString(QString text, QString x);

 private:
  Ui::DrawGraphics *ui;
  QString QuationString;
  QString xInput;
  QVector<double> x;
  QVector<double> y;
};

#endif  // DRAWGRAPHICS_H

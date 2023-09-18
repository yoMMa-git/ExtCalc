#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QDialog {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();
 private slots:
  void onCalculateClicked();

 private:
  Ui::CreditCalc *ui;
};

#endif  // CREDITCALC_H

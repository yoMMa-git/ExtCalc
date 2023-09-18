#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <QDate>
#include <QDialog>
#include <QLineEdit>
extern "C" {
#include "math.h"
}

namespace Ui {
class DepositCalc;
}

class DepositCalc : public QDialog {
  Q_OBJECT

 public:
  explicit DepositCalc(QWidget* parent = nullptr);
  ~DepositCalc();

 private slots:
  void onAddRefillClicked();
  void onAddPayoffClicked();
  void onCalculateClicked();
  QDate calculateFinalDate(int period_num);
  void extractPayoffInfo(QList<double>& partial_payoff_mass,
                         QList<QDate>& in_dates_del);
  void extractRefillInfo(QList<double>& partial_add_mass,
                         QList<QDate>& in_dates);
  QString calculateInterestAndTaxes(double deposit_num, double interest_num,
                                    double tax_num,
                                    QList<double>& partial_add_mass,
                                    QList<QDate>& in_dates,
                                    QList<double>& partial_payoff_mass,
                                    QList<QDate>& in_dates_del,
                                    const QDate& final_date);

 private:
  Ui::DepositCalc* ui;
};

#endif  // DEPOSITCALC_H

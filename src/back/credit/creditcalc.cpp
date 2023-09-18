#include "creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget* parent)
    : QDialog(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);

  ui->paysheet->setReadOnly(true);
  connect(ui->calculate, &QPushButton::clicked, this,
          &CreditCalc::onCalculateClicked);
  QDoubleValidator* validator_sum = new QDoubleValidator(0, 1000000000.0, 0);
  validator_sum->setNotation(QDoubleValidator::StandardNotation);
  ui->sumInput->setValidator(validator_sum);
  QDoubleValidator* validator_rate = new QDoubleValidator(0, 100.0, 2);
  validator_rate->setNotation(QDoubleValidator::StandardNotation);
  ui->rateInput->setValidator(validator_rate);
  QValidator* validator_time = new QIntValidator(0, 600.0, 0);
  ui->timeInput->setValidator(validator_time);
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::onCalculateClicked() {
  ui->paysheet->setText("");
  if (!ui->sumInput->text().isEmpty() && !ui->rateInput->text().isEmpty() &&
      !ui->timeInput->text().isEmpty() &&
      (ui->annuity->isChecked() || ui->differencial->isChecked())) {
    double sum = ui->sumInput->text().toDouble();
    double rate = ui->rateInput->text().toDouble();
    int time = ui->timeInput->text().toDouble();
    if (ui->annuity->isChecked()) {
      double rate_plus_one = 1.0 + rate / 1200.0;
      double month_pay = 0;
      month_pay = sum * (rate / 1200.0 +
                         (rate / 1200.0) / (pow(rate_plus_one, time) - 1.0));
      ui->monthPayOutput->setText(QString::number(month_pay, 'f', 2));
      ui->fullPayOutput->setText(QString::number(month_pay * time, 'f', 2));
      ui->overPayedOutput->setText(
          QString::number(month_pay * time - sum, 'f', 2));
      ui->paysheet->setText("№\tВыплата\tОстаток долга\n");
      double debt = sum;
      for (int i = 0; i < time; i++) {
        debt = debt * rate_plus_one - month_pay;
        if (debt < 0) debt = 0;
        ui->paysheet->setText(ui->paysheet->toPlainText() +
                              QString::number(i + 1) + "\t" +
                              QString::number(month_pay, 'f', 2) + "\t" +
                              QString::number(debt, 'f', 2) + "\n");
      }
    }

    if (ui->differencial->isChecked()) {
      double remain_sum = sum;
      double main_sum = sum / time;
      double monthly_payment = 0;
      double full_sum = 0;
      double min_payment = 0;
      double max_payment = 0;
      ui->paysheet->setText("№\tВыплата\tОстаток долга\n");
      for (int i = 0; i < time; ++i) {
        double persents = remain_sum * rate / 1200.0;
        remain_sum -= main_sum;
        monthly_payment = persents + main_sum;
        if (i == 0) max_payment = monthly_payment;
        full_sum += monthly_payment;
        ui->paysheet->setText(ui->paysheet->toPlainText() +
                              QString::number(i + 1) + "\t" +
                              QString::number(monthly_payment, 'f', 2) + "\t" +
                              QString::number(remain_sum, 'f', 2) + "\n");
      }
      min_payment = monthly_payment;
      ui->monthPayOutput->setText(QString::number(min_payment, 'f', 2) + " - " +
                                  QString::number(max_payment, 'f', 2));
      ui->fullPayOutput->setText(QString::number(full_sum, 'f', 2));
      ui->overPayedOutput->setText(QString::number(full_sum - sum, 'f', 2));
    }
  }
}

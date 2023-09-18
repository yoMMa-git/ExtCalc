#include "depositcalc.h"

#include "ui_depositcalc.h"

DepositCalc::DepositCalc(QWidget* parent)
    : QDialog(parent), ui(new Ui::DepositCalc) {
  ui->setupUi(this);
  connect(ui->addRefill, &QPushButton::clicked, this,
          &DepositCalc::onAddRefillClicked);
  connect(ui->addPayoff, &QPushButton::clicked, this,
          &DepositCalc::onAddPayoffClicked);
  connect(ui->calculate, &QPushButton::clicked, this,
          &DepositCalc::onCalculateClicked);
  ui->startDate->setDate(QDate::currentDate());
  ui->startDate->setMinimumDate(QDate::currentDate());

  QDoubleValidator* validator_sum =
      new QDoubleValidator(0, 10000000000000.0, 5);
  validator_sum->setNotation(QDoubleValidator::StandardNotation);
  ui->sum->setValidator(validator_sum);

  QDoubleValidator* validator_time = new QDoubleValidator(0, 1000, 0);
  validator_time->setNotation(QDoubleValidator::StandardNotation);
  ui->time->setValidator(validator_time);

  QDoubleValidator* validator_rate = new QDoubleValidator(0, 100, 0);
  validator_rate->setNotation(QDoubleValidator::StandardNotation);
  ui->interestRate->setValidator(validator_rate);
  ui->taxRate->setValidator(validator_rate);
}

DepositCalc::~DepositCalc() { delete ui; }

void DepositCalc::onAddRefillClicked() {
  // Создаем элементы интерфейса
  QLineEdit* line = new QLineEdit(this);

  QDoubleValidator* validator_sum =
      new QDoubleValidator(0, 10000000000000.0, 5);
  validator_sum->setNotation(QDoubleValidator::StandardNotation);
  line->setValidator(validator_sum);

  QDateEdit* date_edit = new QDateEdit(this);
  date_edit->setMinimumDate((QDate::currentDate()).addDays(1));
  QPushButton* delete_button = new QPushButton("Удалить", this);

  // Добавляем валидатор для ввода суммы

  // Создаем строку для компоновки элементов
  QHBoxLayout* h_layout = new QHBoxLayout;
  h_layout->addWidget(line);
  h_layout->addWidget(date_edit);
  h_layout->addWidget(delete_button);

  // Получаем текущий макет QFrame (ui->refillFrame) и устанавливаем в него
  // новый макет
  QVBoxLayout* v_layout = qobject_cast<QVBoxLayout*>(ui->refillFrame->layout());
  if (!v_layout) {
    v_layout = new QVBoxLayout(ui->refillFrame);
    ui->refillFrame->setLayout(v_layout);
  }

  // Добавляем строку в вертикальный макет
  v_layout->addLayout(h_layout);
  // Подключаем слот для удаления строки при нажатии на кнопку "Удалить"
  connect(delete_button, &QPushButton::clicked, this, [=]() {
    v_layout->removeItem(
        h_layout);  // Удаляем макет строки из вертикального макета
    delete line;    // Удаляем элементы строки
    delete date_edit;
    delete delete_button;
    delete h_layout;
  });
}

void DepositCalc::onAddPayoffClicked() {
  // Создаем элементы интерфейса и компоновку элементов (аналогично предыдущему
  // коду)
  QLineEdit* line = new QLineEdit(this);
  QDateEdit* date_edit = new QDateEdit(this);
  date_edit->setMinimumDate((QDate::currentDate()).addDays(1));

  QDoubleValidator* validator_sum =
      new QDoubleValidator(0, 10000000000000.0, 5);
  validator_sum->setNotation(QDoubleValidator::StandardNotation);
  line->setValidator(validator_sum);

  QPushButton* delete_button = new QPushButton("Удалить", this);
  QHBoxLayout* h_layout = new QHBoxLayout;
  h_layout->addWidget(line);
  h_layout->addWidget(date_edit);
  h_layout->addWidget(delete_button);

  // Получаем текущий макет QFrame и устанавливаем в него новый макет
  QVBoxLayout* v_layout = qobject_cast<QVBoxLayout*>(ui->payoffFrame->layout());
  if (!v_layout) {
    v_layout = new QVBoxLayout(ui->payoffFrame);
    ui->payoffFrame->setLayout(v_layout);
  }

  // Добавляем строку в вертикальный макет
  v_layout->addLayout(h_layout);

  // Подключаем слот для удаления строки погашения при нажатии на кнопку
  // "Удалить"
  connect(delete_button, &QPushButton::clicked, this, [=]() {
    v_layout->removeItem(
        h_layout);  // Удаляем макет строки из вертикального макета
    delete line;    // Удаляем элементы строки
    delete date_edit;
    delete delete_button;
    delete h_layout;
  });
}

void DepositCalc::onCalculateClicked() {
  double deposit_num = ui->sum->text().toDouble();
  int period_num = ui->time->text().toInt();
  double interest_num = ui->interestRate->text().toDouble();
  double tax_num = ui->taxRate->text().toDouble();

  QList<double> partial_add_mass;
  QList<QDate> in_dates;
  extractRefillInfo(partial_add_mass, in_dates);

  QList<double> partial_payoff_mass;
  QList<QDate> in_dates_del;
  extractPayoffInfo(partial_payoff_mass, in_dates_del);

  QDate final_date = calculateFinalDate(period_num);

  QString result = calculateInterestAndTaxes(
      deposit_num, interest_num, tax_num, partial_add_mass, in_dates,
      partial_payoff_mass, in_dates_del, final_date);

  ui->result->setText(result);
}

void DepositCalc::extractRefillInfo(QList<double>& partial_add_mass,
                                    QList<QDate>& in_dates) {
  QList<QLineEdit*> lines = ui->refillFrame->findChildren<QLineEdit*>();
  for (int i = 0; i < lines.count(); i += 2) {
    partial_add_mass.append(lines[i]->text().toDouble());
    in_dates.append(QDate::fromString(lines[i + 1]->text(), "dd.MM.yyyy"));
  }
}

void DepositCalc::extractPayoffInfo(QList<double>& partial_payoff_mass,
                                    QList<QDate>& in_dates_del) {
  QList<QLineEdit*> lines_del = ui->payoffFrame->findChildren<QLineEdit*>();
  for (int i = 0; i < lines_del.count(); i += 2) {
    partial_payoff_mass.append(lines_del[i]->text().toDouble());
    in_dates_del.append(
        QDate::fromString(lines_del[i + 1]->text(), "dd.MM.yyyy"));
  }
}

QDate DepositCalc::calculateFinalDate(int period_num) {
  QDate current_date = QDate::currentDate();
  QString timeType = ui->timeType->currentText();
  if (timeType == "день") {
    return current_date.addDays(period_num);
  } else if (timeType == "месяц") {
    return current_date.addMonths(period_num);
  } else {
    return current_date.addYears(period_num);
  }
}

QString DepositCalc::calculateInterestAndTaxes(
    double deposit_num, double interest_num, double tax_num,
    QList<double>& partial_add_mass, QList<QDate>& in_dates,
    QList<double>& partial_payoff_mass, QList<QDate>& in_dates_del,
    const QDate& final_date) {
  QDate current_date = QDate::currentDate().addDays(1);
  QDate started_date = current_date;

  QString result = "";
  double earned = 0;
  double overal = 0;
  double taxed = 0;
  double taxed_overal = 0;

  while (current_date <= final_date) {
    for (int i = 0; i < in_dates.count(); i++) {
      if (in_dates[i] == current_date) {
        deposit_num += partial_add_mass[i];
      }
    }
    for (int i = 0; i < in_dates_del.count(); i++) {
      if (in_dates_del[i] == current_date) {
        deposit_num -= partial_payoff_mass[i];
      }
    }

    if (deposit_num < 0) {
      break;
    }

    if (QString::compare(ui->payTime->currentText(), "день") == 0) {
      earned += (deposit_num * interest_num) / 36500;
      taxed += earned * tax_num / 100;
      taxed_overal += taxed;
      overal += deposit_num * interest_num / 36500;
      if (ui->capitalisation->isChecked()) {
        deposit_num += earned;
      }
      result = result + current_date.toString("dd.MM.yyyy") + "->" +
               QString::number(earned, 'f', 2) + "\n";
      earned = 0;
      taxed = 0;
    } else if (QString::compare(ui->payTime->currentText(), "месяц") == 0) {
      if (current_date == started_date.addMonths(1) ||
          current_date == final_date) {
        started_date = current_date;
        earned += (deposit_num * interest_num) / 1200;
        taxed += earned * tax_num / 100;
        taxed_overal += taxed;
        overal += deposit_num * interest_num / 1200;
        if (ui->capitalisation->isChecked()) {
          deposit_num += earned;
        }
        result = result + current_date.toString("dd.MM.yyyy") + "->" +
                 QString::number(earned, 'f', 2) + "\n";
        earned = 0;
        taxed = 0;
      }
    } else {
      if (current_date == started_date.addYears(1) ||
          current_date == final_date) {
        started_date = current_date;
        earned += (deposit_num * interest_num) / 100;
        taxed += earned * tax_num / 100;
        taxed_overal += taxed;
        overal += deposit_num * interest_num / 100;
        if (ui->capitalisation->isChecked()) {
          deposit_num += earned;
        }
        result = result + current_date.toString("dd.MM.yyyy") + "->" +
                 QString::number(earned, 'f', 2) + "\n";
        earned = 0;
        taxed = 0;
      }
    }

    current_date = current_date.addDays(1);
  }

  result = result +
           "Баланс на конец срока:" + QString::number(deposit_num, 'f', 2) +
           "\nПроценты:" + QString::number(overal, 'f', 2);
  result = result + "\nНалог:" + QString::number(taxed_overal, 'f', 2);
  return result;
}

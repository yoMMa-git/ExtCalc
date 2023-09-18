#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  isInputStarted = false;

  connect(ui->numbs,
          QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this,
          &MainWindow::handleButtonClicked);
  connect(ui->functions,
          QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this,
          &MainWindow::handleButtonClicked);
  connect(ui->operands,
          QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this,
          &MainWindow::handleButtonClicked);
  connect(ui->brackets,
          QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this,
          &MainWindow::handleButtonClicked);
  connect(ui->equal, &QPushButton::clicked, this, &MainWindow::onEqualClicked);

  connect(ui->floatDot, &QPushButton::clicked, this,
          [this](bool) { handleDotClicked(ui->floatDot); });
  connect(ui->AC, &QPushButton::clicked, this, &MainWindow::handleACClicked);

  connect(ui->drow, &QPushButton::clicked, this, &MainWindow::onDrawClicked);
  connect(ui->credit, &QPushButton::clicked, this,
          &MainWindow::onCreditClicked);
  connect(ui->deposit, &QPushButton::clicked, this,
          &MainWindow::onDepositClicked);

  for (QAbstractButton *groupButton : ui->operands->buttons())
    groupButton->setEnabled(false);
  ui->plus->setEnabled(true);
  ui->minus->setEnabled(true);
  ui->floatDot->setEnabled(false);
  ui->rbracket->setEnabled(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::handleACClicked() {
  ui->floatDot->setEnabled(true);
  for (QAbstractButton *groupButton : ui->operands->buttons())
    groupButton->setEnabled(true);
  for (QAbstractButton *groupButton : ui->functions->buttons())
    groupButton->setEnabled(true);
  for (QAbstractButton *groupButton : ui->numbs->buttons())
    groupButton->setEnabled(true);
  ui->lbracket->setEnabled(true);
  ui->rbracket->setEnabled(false);
  for (QAbstractButton *groupButton : ui->operands->buttons())
    groupButton->setEnabled(false);
  ui->plus->setEnabled(true);
  ui->minus->setEnabled(true);
  ui->floatDot->setEnabled(false);
  countLeftBrackets = 0;
  countRightBrackets = 0;
  isInputStarted = 0;
  intFlag = 0;
  floatFlag = 0;
  operandFlag = 0;
  functionFlag = 0;
  dotFlag = 0;
  ui->result->setText("0");
}

void MainWindow::handleButtonClicked(QAbstractButton *button) {
  startApp();
  updateDisplay(button);
  updateFlags(button);
  disableButtons(button);
  enableButtons(button);
}

void MainWindow::startApp() {
  if (!isInputStarted) {
    isInputStarted = true;
    ui->result->clear();
  }
}

void MainWindow::handleDotClicked(QPushButton *button) {
  if (!isInputStarted) {
    isInputStarted = true;
    intFlag = 1;
  }
  startApp();
  updateDisplay(button);
  updateFlags(button);
  disableButtons(button);
  enableButtons(button);
}

void MainWindow::onDrawClicked() {
  DrawGraphics window;
  window.setModal(true);
  connect(this, &MainWindow::sendQuationString, &window,
          &DrawGraphics::getQuationString);
  emit sendQuationString(ui->result->text(), ui->xInput->text());
  window.exec();
}

void MainWindow::onCreditClicked() {
  CreditCalc window;
  window.setModal(true);
  window.exec();
}

void MainWindow::onDepositClicked() {
  DepositCalc window;
  window.setModal(true);
  window.exec();
}

void MainWindow::updateDisplay(QAbstractButton *button) {
  //Печать числ
  if (ui->numbs->buttons().contains(button)) {
    ui->result->setText(ui->result->text() + button->text());
  }
  //Печать функции
  else if (ui->functions->buttons().contains(button)) {
    ui->result->setText(ui->result->text() + button->text() + '(');
    countLeftBrackets++;
  }
  //Печать операнда
  else if (ui->operands->buttons().contains(button)) {
    ui->result->setText(ui->result->text() + button->text());
  }
  //Печать скобки
  else if (ui->brackets->buttons().contains(button)) {
    if (button->text() == "(")
      countLeftBrackets++;
    else
      countRightBrackets++;
    ui->result->setText(ui->result->text() + button->text());
  } else if (ui->floatDot == button) {
    ui->result->setText(ui->result->text() + ".");
  }
}

void MainWindow::updateFlags(QAbstractButton *button) {
  //Флаги чисел
  if (ui->numbs->buttons().contains(button)) {
    intFlag = 1;
    if (dotFlag) {
      floatFlag = 1;
      dotFlag = 0;
    }
  }

  if (ui->floatDot == button) dotFlag = 1;

  if (ui->operands->buttons().contains(button)) {
    intFlag = 0;
    floatFlag = 0;
  }
}

void MainWindow::disableButtons(QAbstractButton *button) {
  if (ui->operands->buttons().contains(button)) {
    for (QAbstractButton *groupButton : ui->operands->buttons())
      groupButton->setEnabled(false);
    ui->pow->setEnabled(false);
    ui->rbracket->setEnabled(false);
  }

  if (ui->x == button) {
    for (QAbstractButton *groupButton : ui->numbs->buttons())
      groupButton->setEnabled(false);
  }

  if (ui->numbs->buttons().contains(button)) {
    for (QAbstractButton *groupButton : ui->functions->buttons())
      groupButton->setEnabled(false);
    for (QAbstractButton *groupButton : ui->brackets->buttons())
      groupButton->setEnabled(false);
    ui->x->setEnabled(false);
  }

  if (!(intFlag && !floatFlag)) ui->floatDot->setEnabled(false);

  if (countRightBrackets == countLeftBrackets) ui->rbracket->setEnabled(false);

  if (ui->floatDot == button) {
    for (QAbstractButton *groupButton : ui->operands->buttons())
      groupButton->setEnabled(false);
    for (QAbstractButton *groupButton : ui->functions->buttons())
      groupButton->setEnabled(false);
    for (QAbstractButton *groupButton : ui->brackets->buttons())
      groupButton->setEnabled(false);
    ui->floatDot->setEnabled(false);
  }
  if (ui->rbracket == button) {
    for (QAbstractButton *groupButton : ui->numbs->buttons())
      groupButton->setEnabled(false);
    ui->floatDot->setEnabled(false);
  }

  if (ui->functions->buttons().contains(button) || ui->lbracket == button) {
    ui->plus->setEnabled(false);
    ui->div->setEnabled(false);
    ui->mul->setEnabled(false);
    ui->rbracket->setEnabled(false);
  }

  if (ui->pow == button) {
    ui->pow->setEnabled(false);
  }
}

void MainWindow::enableButtons(QAbstractButton *button) {
  if (ui->numbs->buttons().contains(button)) {
    for (QAbstractButton *groupButton : ui->operands->buttons())
      groupButton->setEnabled(true);
    ui->pow->setEnabled(true);
  }

  if (ui->operands->buttons().contains(button) || ui->pow == button) {
    for (QAbstractButton *groupButton : ui->functions->buttons())
      groupButton->setEnabled(true);
    for (QAbstractButton *groupButton : ui->numbs->buttons())
      groupButton->setEnabled(true);
    ui->x->setEnabled(true);
    ui->lbracket->setEnabled(true);
  }

  if (intFlag && !floatFlag && !dotFlag && ui->rbracket != button) {
    ui->floatDot->setEnabled(true);
  }

  if (ui->functions->buttons().contains(button) || ui->lbracket == button ||
      ui->pow == button) {
    ui->minus->setEnabled(true);
    ui->plus->setEnabled(true);
  }

  if (countRightBrackets < countLeftBrackets && ui->lbracket != button &&
      !ui->functions->buttons().contains(button) &&
      !ui->operands->buttons().contains(button) && ui->floatDot != button)
    ui->rbracket->setEnabled(true);

  if (ui->pow == button) {
    ui->pow->setEnabled(false);
  }
}

void MainWindow::onEqualClicked() {
  QString expr = ui->result->text();  // Получаем текст из интерфейса
  QByteArray byteArray = expr.toLatin1();  // Преобразуем QString в QByteArray
  const char *exprCStr = byteArray.constData();  // Получаем C-style строку
  Token *tokens = tokenize(exprCStr);  // Теперь передаем C-style строку
  int flag = raise_error(tokens);

  int flag_calc = 0;
  if (flag == 0) {
    Token *res = convert_to_polish(tokens);
    double res_number = 0;
    if (ui->xInput->text().isEmpty() &&
        ui->result->text().contains(ui->x->text())) {
      QMessageBox::critical(this, "Ошибка", "Требуется указать значение х.");
    } else {
      res_number = calculate(res, ui->xInput->text().toDouble(), &flag_calc);
    }
    if (flag_calc == 0) {
      ui->result->setText(
          QString::number(res_number));  // Преобразование double в строку
    } else {
      QMessageBox::critical(this, "Ошибка", "Произошла ошибка.");
    }
    free_tokens(res);
  } else {
    QMessageBox::critical(this, "Ошибка", "Произошла ошибка.");
  }
  free_tokens(tokens);
  ui->floatDot->setEnabled(true);
  for (QAbstractButton *groupButton : ui->operands->buttons())
    groupButton->setEnabled(true);
  for (QAbstractButton *groupButton : ui->functions->buttons())
    groupButton->setEnabled(true);
  for (QAbstractButton *groupButton : ui->numbs->buttons())
    groupButton->setEnabled(true);
  ui->lbracket->setEnabled(true);
  ui->rbracket->setEnabled(false);
  for (QAbstractButton *groupButton : ui->operands->buttons())
    groupButton->setEnabled(false);
  ui->plus->setEnabled(true);
  ui->minus->setEnabled(true);
  ui->floatDot->setEnabled(false);
  countLeftBrackets = 0;
  countRightBrackets = 0;
  isInputStarted = 0;
  intFlag = 0;
  floatFlag = 0;
  operandFlag = 0;
  functionFlag = 0;
  dotFlag = 0;
}

bool MainWindow::isInputValid() {
  if (countLeftBrackets != countRightBrackets) return false;

  QString resultText = ui->result->text();
  QChar lastChar = resultText[resultText.size() - 1];
  if (lastChar == '+' || lastChar == '-' || lastChar == '*' ||
      lastChar == '/' || lastChar == '(' || lastChar == '.')
    return false;

  return true;
}

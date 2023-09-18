#include "drawgraphics.h"

#include "ui_drawgraphics.h"

DrawGraphics::DrawGraphics(QWidget *parent)
    : QDialog(parent), ui(new Ui::DrawGraphics) {
  ui->setupUi(this);
  QDoubleValidator *validator = new QDoubleValidator(-1000000.0, +1000000.0, 6);
  validator->setNotation(QDoubleValidator::StandardNotation);
  ui->x_min->setValidator(validator);
  ui->x_min->setValidator(validator);
  ui->x_max->setValidator(validator);
  ui->x_max->setValidator(validator);

  connect(ui->draw, &QPushButton::clicked, this, &DrawGraphics::onDrawClicked);
}

DrawGraphics::~DrawGraphics() { delete ui; }

void DrawGraphics::onDrawClicked() {
  double Xmin = ui->x_min->text().toDouble();
  double Xmax = ui->x_max->text().toDouble();
  double Ymin = ui->y_min->text().toDouble();
  double Ymax = ui->y_max->text().toDouble();
  if (!QuationString.isEmpty() && (Xmin < Xmax) && (Ymin < Ymax) &&
      (!ui->x_min->text().isEmpty()) && (!ui->x_max->text().isEmpty()) &&
      (!ui->y_min->text().isEmpty()) && (!ui->y_max->text().isEmpty())) {
    ui->widget->yAxis->setRange(Ymin, Ymax);
    ui->widget->xAxis->setRange(Xmin, Xmax);
    ui->widget->addGraph();
    ui->widget->replot();
    QByteArray byteArray =
        QuationString.toLatin1();  // Преобразуем QString в QByteArray
    const char *exprCStr = byteArray.constData();  // Получаем C-style строку
    Token *tokens = tokenize(exprCStr);  // Теперь передаем C-style строку
    int flag = raise_error(tokens);
    if (flag == 0) {
      Token *res = convert_to_polish(tokens);
      double X = Xmin;
      double h = (Xmax - Xmin) / 1000;
      for (int i = 0; i < 1000; i++) {
        int flag_calc = 0;
        double res_number = 0;
        if (xInput.isEmpty()) {
          res_number = calculate(res, X, &flag_calc);
        } else {
          res_number = calculate(res, xInput.toDouble(), &flag_calc);
        }
        if (flag_calc == 0 && !std::isnan(res_number) &&
            !std::isinf(res_number)) {
          x.push_back(X);
          y.push_back(res_number);
        } else {
          x.push_back(X);
          y.push_back(std::numeric_limits<double>::quiet_NaN());
        }
        X += h;
      }
      free_tokens(res);
    } else {
      QMessageBox::critical(this, "Ошибка", "Ошибка.");
    }
    free_tokens(tokens);

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeDrag);
    ui->widget->setInteraction(QCP::iRangeZoom);
  } else {
    QMessageBox::critical(this, "Ошибка", "Ошибка построения графика.");
  }
}

void DrawGraphics::getQuationString(QString text, QString x) {
  QuationString = text;
  xInput = x;
}

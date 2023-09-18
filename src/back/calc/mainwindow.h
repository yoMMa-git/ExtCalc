#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QButtonGroup>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>

#include "../credit/creditcalc.h"
#include "../deposit/depositcalc.h"
#include "../graphics/drawgraphics.h"

extern "C" {
#include "../polish/polish.h"
#include "../polish/stack.h"
#include "../polish/tokenize.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void handleButtonClicked(QAbstractButton *button);
  void handleDotClicked(QPushButton *button);
  void onDrawClicked();
  void onCreditClicked();
  void onDepositClicked();
  void handleACClicked();
  void onEqualClicked();

 signals:
  void sendQuationString(QString text, QString x);

 private:
  Ui::MainWindow *ui;
  QButtonGroup *buttonGroup;
  QLabel *label;
  void startApp();
  void updateDisplay(QAbstractButton *button);
  void disableButtons(QAbstractButton *button);
  void enableButtons(QAbstractButton *button);
  void updateFlags(QAbstractButton *button);
  bool isInputValid();

  int countLeftBrackets = 0;
  int countRightBrackets = 0;

  bool isInputStarted = 0;
  bool intFlag = 0;
  bool lbracketFlag = 0;
  bool rbracketFlag = 0;
  bool floatFlag = 0;
  bool operandFlag = 0;
  bool functionFlag = 0;
  bool dotFlag = 0;
};
#endif  // MAINWINDOW_H

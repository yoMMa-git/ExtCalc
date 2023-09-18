#include "calc/mainwindow.h"
#include "graphics/drawgraphics.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}

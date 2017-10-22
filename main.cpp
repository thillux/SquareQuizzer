#include "mainwindow.h"
#include <QApplication>
#include <memory>

int main(int argc, char *argv[]) {
  auto app = std::make_shared<QApplication>(argc, argv);
  auto mainWindow = std::make_shared<MainWindow>();
  mainWindow->show();

  return app->exec();
}

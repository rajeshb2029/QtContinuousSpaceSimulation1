/*
 * File:   main.cpp
 * Author: Rajesh
 *
 * Created on March 11, 2016, 2:25 AM
 */

#include <QApplication>
#include "QtMainWindow4.hpp"

int main(int argc, char *argv[]) {  

  QApplication app(argc, argv);

  QtMainWindow4 *window = new QtMainWindow4;
  window->show();

  return app.exec();
}

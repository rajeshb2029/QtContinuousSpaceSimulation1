/* 
 * File:   QMainWindow4.hpp
 * Author: Rajesh
 *
 * Created on March 10, 2016, 10:41 PM
 */

#ifndef QTMAINWINDOW4_HPP
#define QTMAINWINDOW4_HPP

#include <QPixmap>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QApplication>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include "GraphicsView1.hpp"
#include "Globals.hpp"

class QtMainWindow4 : public QMainWindow {
  Q_OBJECT

public:
  GraphicsView1 *view;
  QPushButton *pauseButton;
  SimulationWidget *simulationWidget;

  QtMainWindow4(QWidget* parent = 0) : QMainWindow(parent) {

    pauseButton = new QPushButton("Pause", this);
    QPushButton *resetButton = new QPushButton("Reset", this);
    QPushButton *resetZoomButton = new QPushButton("Reset Zoom", this);
    QPushButton *toggleGridButton = new QPushButton("Toggle Grid", this);
    QPushButton *quitButton = new QPushButton("Quit", this);
    QPushButton *saveButton = new QPushButton("Save", this);
    pauseButton->setFixedSize(75, 30);
    resetButton->setFixedSize(75, 30);
    resetZoomButton->setFixedSize(75, 30);
    quitButton->setFixedSize(75, 30);
    saveButton->setFixedSize(75, 30);
    toggleGridButton->setFixedSize(75, 30);

    QWidget *widget = new QWidget;

    simulationWidget = new SimulationWidget(this);
    view = new GraphicsView1(simulationWidget, this);

    QHBoxLayout *hboxlayout = new QHBoxLayout(this);
    QVBoxLayout *vboxlayout = new QVBoxLayout(this);
    vboxlayout->addWidget(pauseButton);
    vboxlayout->addWidget(resetButton);
    vboxlayout->addWidget(resetZoomButton);
    vboxlayout->addWidget(toggleGridButton);
    vboxlayout->addWidget(quitButton);
    vboxlayout->addWidget(saveButton);
    vboxlayout->addStretch(1);

    hboxlayout->addWidget(view);
    hboxlayout->addLayout(vboxlayout);
    widget->setLayout(hboxlayout);

    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(saveButton, SIGNAL(clicked()), view, SLOT(saveImage()));
    connect(resetButton, SIGNAL(clicked()), simulationWidget, SLOT(resetSystemSlot()));
    connect(resetButton, SIGNAL(clicked()), view, SLOT(redrawScene()));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(togglePauseButtonText()));
    connect(resetZoomButton, SIGNAL(clicked()), view, SLOT(resetZoomSlot()));
    connect(toggleGridButton, SIGNAL(clicked()), view, SLOT(toggleDrawGrid()));

    this->setCentralWidget(widget);
    this->resize(WINDOW_WIDTH + 100, WINDOW_HEIGHT + 5);
  }

public slots:

  void togglePauseButtonText() {
    if(DEBUG) {
      std::cout << "togglePauseButtonText() called" << std::endl;
    }
    simulationWidget->paused = !simulationWidget->paused;
    if (simulationWidget->paused) {
      pauseButton->setText("Resume");
    } else {
      pauseButton->setText("Pause");
    }
  }

};

#endif /* QTMAINWINDOW4_HPP */


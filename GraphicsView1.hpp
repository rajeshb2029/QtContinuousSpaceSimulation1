/* 
 * File:   GraphicsView1.hpp
 * Author: Rajesh
 *
 * Created on March 10, 2016, 10:39 PM
 */

#ifndef GRAPHICSVIEW1_HPP
#define GRAPHICSVIEW1_HPP

#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QPixmap>
#include "Globals.hpp"
#include "SimulationWidget.hpp"

class GraphicsView1 : public QGraphicsView {
  Q_OBJECT 
  
public:
  QPixmap *pixmap;
  QGraphicsScene *scene;
  SimulationWidget *simulationWidget;
  qreal fullViewScaleFactor;
  int drawIter;
  bool drawGridFlag;
    
  GraphicsView1(SimulationWidget *gridWidget, QWidget *parent = 0) : QGraphicsView(parent) {
    pixmap = new QPixmap(IMAGE_WIDTH, IMAGE_HEIGHT);
    pixmap->fill(Qt::white);

    QPainter qp(pixmap);        
//    pixmap->fill(Qt::black);
//    qp.setBrush(Qt::white);
//    qp.drawRect(10, 10, 100, 100);

//    gridWidget = new GridWidget(this);
    this->simulationWidget = gridWidget;
    
//    drawLines(&qp);    
//    drawParticles(&qp);

    scene = new QGraphicsScene;
    this->setScene(scene);
    this->setSceneRect(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setRenderHints(QPainter::Antialiasing);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);    
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    scene->addPixmap(*pixmap);    
    
    gridWidget->timerId = startTimer(TIMESTEP);
    fullViewScaleFactor = (float)WINDOW_WIDTH/IMAGE_WIDTH;
    resetZoom();

    drawGridFlag = true;
    
    drawSimulationSystem();       
    drawIter = 0;
  }

  void drawSimulationSystem() {
//    pixmap = new QPixmap(IMAGE_WIDTH, IMAGE_HEIGHT);        
    pixmap->fill(Qt::white);
    QPainter qp(pixmap);    
    if(drawGridFlag) {
      drawGrid(&qp);
    }
    drawParticles(&qp);    
    scene->clear();
    scene->addPixmap(*pixmap);    
  }

  void drawGrid(QPainter *qp) {
    QPen pen(Qt::black, 3, Qt::SolidLine);
    qp->setPen(pen);
    qp->drawLine(0, 0, IMAGE_WIDTH, 0);
    qp->drawLine(0, 0, 0, IMAGE_HEIGHT);
    qp->drawLine(0, IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);
    qp->drawLine(IMAGE_WIDTH, 0, IMAGE_WIDTH, IMAGE_HEIGHT);

    qp->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    for (int i = GRIDSIZE; i < IMAGE_WIDTH; i += GRIDSIZE) {
      qp->drawLine(0, i, IMAGE_WIDTH, i);
    }
    for (int i = GRIDSIZE; i < IMAGE_HEIGHT; i += GRIDSIZE) {
      qp->drawLine(i, 0, i, IMAGE_HEIGHT);
    }
  }

  void drawParticles(QPainter *qp) {
    qp->setBrush(QColor(20, 20, 150));
    for (int i = 0; i < N; i++) {
      simulationWidget->particles[i].drawShape(qp, new QColor("#d40000"));
    }
  }
  
  void timerEvent(QTimerEvent* event) override {
    Q_UNUSED(event);
    
    if(!simulationWidget->paused) {
      simulationWidget->updateSystem();      
      drawIter += 1;
      if(drawIter >= DRAW_ITER) {
        drawSimulationSystem();
        drawIter = 1;
      }
    }
  }
  
//  void wheelEvent(QWheelEvent* event) override {
//    qreal zoomInFactor = 1.25;
//    qreal zoomOutFactor = 1/zoomInFactor;
//    
//    if (event->delta() > 0) {
//      this->scale(zoomInFactor, zoomInFactor);
//    } else {
//      this->scale(zoomOutFactor, zoomOutFactor);
//    }
//  }
  
  void wheelEvent(QWheelEvent* event) override {
    if (event->delta() > 0) {
      zoomIn();
    } else {
      zoomOut();
    }
  }
  
  void resetZoom() {
    fullViewScaleFactor = (float)WINDOW_WIDTH/IMAGE_WIDTH;
    if(DEBUG) {
      std::cout << "resetZoom() called: " << fullViewScaleFactor << std::endl;
    }    
    this->resetMatrix();
    this->scale(fullViewScaleFactor, fullViewScaleFactor);    
  }

  void scaleView(qreal scaleFactor) {
    qreal factor = this->transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
      return;

    if(DEBUG) {
      std::cout << "scaleFactor: " << scaleFactor << std::endl;
    }
    this->scale(scaleFactor, scaleFactor);
  }

  void zoomIn() {
    scaleView(qreal(1.1));
  }

  void zoomOut() {
    scaleView(1 / qreal(1.1));
  }

  public slots:

  void saveImage() {
    if(DEBUG) {
      std::cout << "saveImage() called" << std::endl;
    }
    pixmap->save("Test.png", "PNG", -1);
  }
  
  void resetZoomSlot() {
    resetZoom();
  }
  
  void redrawScene() {
    drawSimulationSystem();
  }
  
  void toggleDrawGrid() {
    drawGridFlag = !drawGridFlag;
  }
  
};

#endif /* GRAPHICSVIEW1_HPP */


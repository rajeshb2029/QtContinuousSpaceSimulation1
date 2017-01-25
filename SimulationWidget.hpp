/* 
 * File:   MainWindow.hpp
 * Author: Rajesh
 *
 * Created on March 9, 2016, GRIDSIZE:22 PM
 */

#ifndef SIMULATIONWIDGET_HPP
#define SIMULATIONWIDGET_HPP

#include <iostream>
#include <time.h>
#include <cassert>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include "Globals.hpp"
#include "Particle.hpp"


class SimulationWidget : public QWidget {
  Q_OBJECT

public:
  Particle particles[N];
  bool paused;
  int timerId;

  SimulationWidget(QWidget *parent = 0) : QWidget(parent) {

    std::cout << "Grid size: " << nrows << " x " << ncols << std::endl;

    qsrand(time(NULL));
    
    initializeSystem();
//    setPositiveXVelocity();
    setRandomParticleVelocity();
    
    paused = false;
  }

  void initializeSystem() {
//    initializeSystemAtRandom();
    initializeAtCenter();
  }

  void resetSystem() {
    initializeSystem();
    setRandomParticleVelocity();
  }

  void initializeSystemAtRandom() {
    int x, y;
    for (int i = 0; i < N; i++) {
      x = getRandomInt(IMAGE_WIDTH);
      x = getRandomInt(IMAGE_HEIGHT);
      particles[i] = Particle(x, y);
    }
  }
  
  void setPositiveXVelocity() {
    for (int i = 0; i < N; i++) {
      particles[i].setVelocity(VELOCITY, 0); 
    }
  }
  
  void setRandomParticleVelocity() {
    for (int i = 0; i < N; i++) {
      particles[i].setVelocity((getRandomFloat()-0.5)*2*VELOCITY, (getRandomFloat()-0.5)*2*VELOCITY); 
    }
  }

  void initializeAtCenter() {
    int factor = 6;
    int x = IMAGE_WIDTH/2 - IMAGE_WIDTH/factor;
    int y = IMAGE_HEIGHT/2 - IMAGE_HEIGHT/factor;
    for (int i = 0; i < N; i++) {
      particles[i] = Particle(x, y);
      x += 2*RADIUS;
      if (x > (IMAGE_WIDTH / 2 + IMAGE_WIDTH / factor)) {
        x = IMAGE_WIDTH / 2 - IMAGE_WIDTH / factor;
        y += 2*RADIUS;
      }
      if (y > (IMAGE_HEIGHT / 2 + IMAGE_HEIGHT / factor)) {
        y = IMAGE_HEIGHT / 2 - IMAGE_HEIGHT / factor;
      }
    }
  }

  int getRandomInt(int range) {
    return (int) ((float) qrand() * range / RAND_MAX);
  }
  
  qreal getRandomFloat() {
    return (float) qrand() / RAND_MAX;
  }

  void updateSystem() {
    qreal tx = 0, ty = 0;
    
    for (int i = 0; i < N; i++) {      
      tx = particles[i].pos.x();
      ty = particles[i].pos.y();
      tx += particles[i].vel.x() * TIMESTEP/1000.0;             
      ty += particles[i].vel.y() * TIMESTEP/1000.0;
      if(tx > IMAGE_WIDTH) {
        tx -= IMAGE_WIDTH;
      } else if(tx < 0) {
        tx += IMAGE_WIDTH;
      }
      if(ty > IMAGE_HEIGHT) {
        ty -= IMAGE_HEIGHT;
      } else if (ty < 0) {
        ty += IMAGE_HEIGHT;
      }
//      tx = (int)(tx + IMAGE_WIDTH) % IMAGE_WIDTH;
//      ty = (int)(ty + IMAGE_HEIGHT) % IMAGE_HEIGHT;
//      std::cout << "Original position: " << particles[i].pos.x() << " " << 
//              particles[i].pos.y() << " New particle position: " << tx << 
//              " " << ty << " Particle velocity: " << particles[i].vel.x() << " "
//              << particles[i].vel.y() << std::endl;
      particles[i].pos = QPointF(tx, ty);      
    }
  }

public slots:

  void resetSystemSlot() {
    if (DEBUG) {
      std::cout << "resetSystem() called" << std::endl;
    }
    resetSystem();    
  }

  //  void toggleSimulation() {
  //    if(DEBUG) {
  //      std::cout << "toggleSimulation() called" << std::endl;
  //    }    
  //    if (paused) {
  //      killTimer(timerId);
  //      std::cout << "Timer killed" << std::endl;
  //    } else {
  //      timerId = startTimer(TIMESTEP);
  //      std::cout << "Timer started" << std::endl;
  //    }
  ////    std::cout << "called" << std::endl;
  //  }

};

#endif /* SIMULATIONWIDGET_HPP */


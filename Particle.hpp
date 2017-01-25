/* 
 * File:   Particle.hpp
 * Author: Rajesh
 *
 * Created on March 11, 2016, 2:32 AM
 */

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <QPainter>
#include <QColor>
#include <QPointF>

class Particle {
public:
  QPointF pos;
  QPointF vel;
  int radius;

  Particle(qreal x = 0, qreal y = 0, qreal radius = RADIUS) {
    pos = QPointF(x, y);
    vel = QPointF(0, 0);
    this->radius = radius;
  }

  void setVelocity(qreal x, qreal y) {
    vel = QPointF(x, y);
  }

  void drawShape(QPainter *qp, QColor *color = new QColor(Qt::black)) {
    qp->setPen(*color);
    qp->setBrush(QBrush(*color));
    qp->setOpacity(0.8);
    qp->drawEllipse(pos.x() - radius, pos.y() - radius, 2 * radius, 2 * radius);
  }
};

#endif /* PARTICLE_HPP */


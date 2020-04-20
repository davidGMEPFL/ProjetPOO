#include "Grip.hpp"

Grip::Grip(const Vec2d& position,const double& rayon):
    CircularBody(position,rayon)
{}


void Grip::move(const Vec2d& vec) {
   CircularBody::move(vec);
}


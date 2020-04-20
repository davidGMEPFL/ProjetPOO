#pragma once
#include "CircularBody.hpp"
#include "Utility/Vec2d.hpp"


class Grip : public CircularBody
{
public:
    Grip(const Vec2d& position,const double& rayon);
    void move(const Vec2d&);
};



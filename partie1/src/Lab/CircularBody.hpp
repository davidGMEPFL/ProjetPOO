#pragma once
#include "../Utility/Vec2d.hpp"
#include <iostream>
class CircularBody
{
public:
    CircularBody(const Vec2d&, const double&);
    CircularBody(const CircularBody&);


    double getRadius() const;
    Vec2d getPosition() const;
    void setPosition(const Vec2d&);
    void setRadius(const double&);
    CircularBody& operator=(const CircularBody&);
    void move(const Vec2d&);
    bool contains(const CircularBody&)const;

    bool isColliding(const CircularBody&)const;
    bool contains(const Vec2d&)const;
    bool operator>(const CircularBody&) const;
    bool operator&(const CircularBody&) const;
    bool operator>(const Vec2d&) const;
private:
    Vec2d pos;
    double rayon;
};

std::ostream& operator<<(std::ostream&,const CircularBody&);

//bool operator>(const Vec2d& ,const CircularBody&);

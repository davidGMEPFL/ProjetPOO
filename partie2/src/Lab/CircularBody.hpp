#pragma once
#include "Utility/Vec2d.hpp"
#include <iostream>

class CircularBody
{
public:
    double getRadius() const;
    Vec2d getPosition() const&;

    CircularBody& operator=(const CircularBody&);
    void move(const Vec2d&);
    bool contains(const CircularBody&)const;
    bool isColliding(const CircularBody&)const;
    bool contains(const Vec2d&)const;
    bool operator>(const CircularBody&) const;
    bool operator&(const CircularBody&) const;
    bool operator>(const Vec2d&) const;
protected:
    Vec2d position;
    double rayon;

    CircularBody(const Vec2d&, const double&); // Constructeur
    CircularBody(const CircularBody&);         // Constructeur de copie

    void setPosition(const Vec2d&);
    void setRadius(const double&);};

std::ostream& operator<<(std::ostream&,const CircularBody&);

//bool operator>(const Vec2d& ,const CircularBody&);

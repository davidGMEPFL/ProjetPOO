#pragma once
#include "Utility/Vec2d.hpp"
#include <iostream>

class CircularBody
{

protected:
    Vec2d position;
    double rayon;

public:
    CircularBody(const Vec2d&, const double&); // Constructeur
    CircularBody(const CircularBody&);         // Constructeur de copie
    CircularBody& operator=(const CircularBody&); //opérateur d'affectation

//Méthodes essentielles
    void move(const Vec2d&);
    bool contains(const CircularBody&)const;
    bool isColliding(const CircularBody&)const;
    bool contains(const Vec2d&)const;

// Opérateurs
    bool operator>(const CircularBody&) const;
    bool operator&(const CircularBody&) const;
    bool operator>(const Vec2d&) const;

// Getters et setters
    double getRadius() const;
    Vec2d getPosition() const;
    void setPosition(const Vec2d&);
    void setRadius(const double&);

};

std::ostream& operator<<(std::ostream&,const CircularBody&); //surchage externe

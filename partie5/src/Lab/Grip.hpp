#pragma once
#include "CircularBody.hpp"
#include "Utility/Vec2d.hpp"


class Grip : public CircularBody
{
public:
    Grip(const Vec2d& position,const double& rayon); //Constructeur
//    void move(const Vec2d&); Plutôt que lui ajouter une méthode en plus,
    //on utilise directement la méthode move des CircularBody
};



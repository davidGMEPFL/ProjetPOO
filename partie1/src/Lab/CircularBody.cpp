#include "CircularBody.hpp"
#include "../Utility/Vec2d.hpp"
#include "../Utility/Utility.hpp"
#include <cstdlib>
#include <iostream>


CircularBody::CircularBody(const Vec2d& pos,const double& rayon)
    :pos(pos),rayon(rayon)    {}
CircularBody::CircularBody(const CircularBody& cercle):
    pos(cercle.pos),rayon(cercle.rayon) {}


double CircularBody::getRadius()const
{
    return rayon;
}
Vec2d CircularBody::getPosition()const
{
    return pos;
}
void CircularBody::setPosition(const Vec2d& pos)
{
    this->pos=pos;
}
void CircularBody::setRadius(const double& rayon)
{
    this->rayon=rayon;
}
CircularBody& CircularBody::operator=(const CircularBody& cercle)
{
    pos=cercle.pos;
    rayon=cercle.rayon;
    return *this;
}
void CircularBody::move(const Vec2d& vec)
{
    pos+=vec;
}
bool CircularBody::contains(const CircularBody& other)const
{
    if (other.rayon<=rayon) {
        if (distance(pos, other.pos)<=abs(other.rayon-rayon)) return true;
        else return false;
    } else return false;
}
bool CircularBody::isColliding(const CircularBody& other)const
{
    if (distance(pos,other.pos)<=(rayon+other.rayon)) return true;
    else return false;
}
bool CircularBody::contains(const Vec2d& point)const
{
    if (distance(pos,point)<rayon) return true;
    else return false;
}
bool CircularBody::operator>(const CircularBody& other)const
{
    return contains(other);
}

bool CircularBody::operator&(const CircularBody& other)const
{
    return isColliding(other);
}
bool CircularBody::operator>(const Vec2d& point)const
{
    return contains(point);
}

std::ostream& operator<<(std::ostream& out,const CircularBody& cercle)
{
    out<<"CircularBody: position = "<<cercle.getPosition()<< " radius = "
       <<cercle.getRadius()<<std::endl;
    return out;
}

//bool operator>(const Vec2d& point,const CircularBody& cercle){
//    return !(cercle>point);
//}


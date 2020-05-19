#include "CircularBody.hpp"
#include "Utility/Utility.hpp"
#include <cstdlib>

CircularBody::CircularBody(const Vec2d& position,const double& rayon)
    :position(position),rayon(rayon)    {}

CircularBody::CircularBody(const CircularBody& cercle): //autorise copie
    position(cercle.position),rayon(cercle.rayon) {}



CircularBody& CircularBody::operator=(const CircularBody& cercle)
{
    position=cercle.position;
    rayon=cercle.rayon;
    return *this;
}
void CircularBody::move(const Vec2d& vec)
{
    position+=vec;
}
bool CircularBody::contains(const CircularBody& other)const
{
    if (other.rayon<=rayon) {
        return (distance(position, other.position)<=std::abs(other.rayon-rayon));
    } else return false;
}

bool CircularBody::isColliding(const CircularBody& other)const
{
   return (distance(position,other.position)<=(rayon+other.rayon));
}
bool CircularBody::contains(const Vec2d& point)const
{
    return (distance(position,point)<rayon);
}

// GETTERS ET SETTERS
double CircularBody::getRadius()const
{
    return rayon;
}
Vec2d CircularBody::getPosition()const
{
    return position;
}
void CircularBody::setPosition(const Vec2d& position_)
{
    position=position_;
}
void CircularBody::setRadius(const double& rayon)
{
    this->rayon=rayon;
}

//OPERATEURS
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


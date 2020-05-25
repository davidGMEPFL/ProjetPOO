#include "CircularBody.hpp"
#include "Utility/Utility.hpp"
#include <cstdlib>

CircularBody::CircularBody(const Vec2d& position,const double& rayon)
    :position(position),rayon(rayon)    {}
CircularBody::CircularBody(const CircularBody& cercle):
    position(cercle.position),rayon(cercle.rayon) {}


double CircularBody::getRadius()const
{
    return rayon;
}
Vec2d CircularBody::getPosition()const&
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
        if (distance(position, other.position)<=abs(other.rayon-rayon)) return true;
        else return false;
    } else return false;
}

bool CircularBody::isColliding(const CircularBody& other)const
{
    if (distance(position,other.position)<=(rayon+other.rayon)) return true;
    else return false;
}
bool CircularBody::contains(const Vec2d& point)const
{
    if (distance(position,point)<rayon) return true;
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


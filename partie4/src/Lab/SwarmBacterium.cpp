#include "SwarmBacterium.hpp"
#include "Random/Random.hpp"
#include "Application.hpp"


SwarmBacterium::SwarmBacterium(const Vec2d & position, Swarm* saTroupe):
    Bacterium(uniform(getConfig()["energy"]["min"].toDouble(),getConfig()["energy"]["max"].toDouble()),
                    position,  Vec2d::fromRandomAngle(),
                    uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()),
                    getConfig()["color"])
{
    addSwarmBacterium(this, saTroupe);
}



Vec2d SwarmBacterium::f(Vec2d position, Vec2d speed) const
{
    return Vec2d (0,0);
}


void SwarmBacterium::move(sf::Time dt)
{
//    DiffEqResult Result(stepDiffEq(position, getSpeedVector(), dt,  *this));
//    consumeEnergy((position-Result.position).length()*EnergieDepl());
//    position=Result.position;
}

Bacterium* SwarmBacterium::clone() const
{
    Bacterium* ptr=new SwarmBacterium(*this);
    ptr->mutate();
    getAppEnv().addBacterium(ptr, true);
    return ptr;
}

j::Value& SwarmBacterium::getConfig() const
{
    return getAppConfig()["swarm bacterium"];
}

void SwarmBacterium::drawOn(sf::RenderTarget& target) const{
    Bacterium::drawOn(target);
    if(isDebugOn() && estLeader){
        sf::Color couleur(sf::Color::Red);
        double epaisseur(5);
        auto border = buildAnnulus(position, rayon, couleur, epaisseur);
        target.draw(border);
    }
}


void SwarmBacterium::addSwarmBacterium(SwarmBacterium* Bact,Swarm* troupe){
    troupe->addSwarmBacterium(Bact);
}

#include "SwarmBacterium.hpp"
#include "Random/Random.hpp"
#include "Application.hpp"


SwarmBacterium::SwarmBacterium(const Vec2d& position, Swarm* saTroupe):
    Bacterium(uniform(getConfig()["energy"]["min"].toDouble(),getConfig()["energy"]["max"].toDouble()),
                    position,  Vec2d::fromRandomAngle(),
                    uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()),
                    saTroupe->getColor() /*getConfig()["color"]*/), SonSwarm(saTroupe)
{
    addSwarmBacterium(this, saTroupe);
}


void SwarmBacterium::addSwarmBacterium(SwarmBacterium *laBact, Swarm* saTroupe)const{
    saTroupe->addSwarmBacterium(laBact);
}


Vec2d SwarmBacterium::f(Vec2d position, Vec2d speed) const
{
    return SonSwarm->getConfig()["force factor"].toDouble()*(SonSwarm->getPosLeader() - position);
}

void SwarmBacterium::move(sf::Time dt){
    if(this==SonSwarm->getLeader()){
        Vec2d tempRand;
        for (int i(0); i<20; ++i) {
            tempRand=Vec2d::fromRandomAngle();
            if(getAppEnv().getPositionScore(position+tempRand)>
                    getAppEnv().getPositionScore(position+direction))
                direction=tempRand;
        }
        position+=direction*getConfig()["speed"]["initial"].toDouble()*dt.asSeconds();
        consumeEnergy(EnergieDepl()*getConfig()["speed"]["initial"].toDouble()*dt.asSeconds());
    }
    else{
        DiffEqResult Result(stepDiffEq(position, direction*getConfig()["speed"]["initial"].toDouble()*dt.asSeconds(), dt,  *this));
        consumeEnergy((position-Result.position).length()*EnergieDepl());
        position=Result.position; direction=Result.speed/getConfig()["speed"]["initial"].toDouble();
    }
}

Bacterium* SwarmBacterium::clone() const
{
    SwarmBacterium* ptr=new SwarmBacterium(*this);
    ptr->mutate();
    addSwarmBacterium(ptr, SonSwarm);
    getAppEnv().addBacterium(ptr, true);
    return ptr;
}

j::Value& SwarmBacterium::getConfig() const
{
    return getAppConfig()["swarm bacterium"];
}

void SwarmBacterium::drawOn(sf::RenderTarget& target) const{
    Bacterium::drawOn(target);
    if(isDebugOn() && this==SonSwarm->getLeader()){
        sf::Color couleur(sf::Color::Red);
        double epaisseur(5);
        auto border = buildAnnulus(position, rayon, couleur, epaisseur);
        target.draw(border);
    }
}




SwarmBacterium::~SwarmBacterium(){
    SonSwarm->popBact(this);
}

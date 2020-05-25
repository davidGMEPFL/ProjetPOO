#include "SwarmBacterium.hpp"
#include "Random/Random.hpp"
#include "Application.hpp"
#include <Lab/NutrimentA.hpp>
#include <Lab/NutrimentB.hpp>


SwarmBacterium::SwarmBacterium(const Vec2d& position, Swarm* saTroupe):
    Bacterium(uniform(getConfig()["energy"]["min"].toDouble(),getConfig()["energy"]["max"].toDouble()),
                    position,  Vec2d::fromRandomAngle(),
                    uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()),
                    saTroupe->getColor()), SonSwarm(saTroupe)
{
    saTroupe->addSwarmBacterium(this); // ajout du ptr au Swarm

    ++Data4Graphs[s::SWARM_BACTERIA];/* prise en compte de la nouvelle bactérie dans les statistiques */
    Data4Graphs[s::SPEED] += getConfig()["speed"]["initial"].toDouble();
}

j::Value& SwarmBacterium::getConfig() const
{
    return getAppConfig()["swarm bacterium"];
}

void SwarmBacterium::drawOn(sf::RenderTarget& target) const{

    Bacterium::drawOn(target); // Dessin corps bactéries

    //Dessin anneau autour du leader
    if(isDebugOn() && this==SonSwarm->getLeader()){ // Ce test fonctionne car les ptrs sont tous des copies
            //(par opposition à plusieurs ptrs différents pointant vers la même adresse)
        sf::Color couleur(sf::Color::Red);
        double epaisseur(5);
        auto border = buildAnnulus(position, rayon, couleur, epaisseur);
        target.draw(border);
    }
}
Bacterium* SwarmBacterium::clone() const
{
    SwarmBacterium* ptr=new SwarmBacterium(*this);
    ptr->mutate();
    getAppEnv().addBacterium(ptr, true); // ajout du clone au lab
    addSwarmBacterium(ptr, SonSwarm); // ajout du clone au Swarm

    /* prise en compte de la bactérie clonée dans les statistiques */
    ++Data4Graphs[s::SWARM_BACTERIA];
    Data4Graphs[s::SPEED] += ptr->getConfig()["speed"]["initial"].toDouble();

    return ptr;
}
void SwarmBacterium::addSwarmBacterium(SwarmBacterium *laBact, Swarm* saTroupe)const{
    saTroupe->addSwarmBacterium(laBact);
}


// DEPLACEMENT :
Vec2d SwarmBacterium::f(Vec2d position, Vec2d speed) const
{   // Les bactéries son attirées par leur leader
    return SonSwarm->getConfig()["force factor"].toDouble()*(SonSwarm->getPosLeader() - position);
}
void SwarmBacterium::move(sf::Time dt){
    // Pour les leaders, détermination de la meilleure direction parmi n aléatoires, à chaque itération
    if(this==SonSwarm->getLeader()){ // Ce test fonctionne car les ptrs sont tous des copies
                    //(par opposition à plusieurs ptrs différents pointant vers la même adresse)
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
    else{ // pour les non-leaders vitesse initiales reste constante pour qu'ils n'accélèrent pas trop
        // Les bactéries sont tout de même attitées par le leader avec impact sur leur vitesse instantannément
        DiffEqResult Result(stepDiffEq(position, direction*getConfig()["speed"]["initial"].toDouble(), dt, *this));
        consumeEnergy((position-Result.position).length()*EnergieDepl());
        position=Result.position;
        direction=Result.speed.normalised();
    }
}


Quantity SwarmBacterium::eatableQuantity(NutrimentA& nutriment){
    return nutriment.eatenBy(*this);
}
Quantity SwarmBacterium::eatableQuantity(NutrimentB& nutriment) {
    return nutriment.eatenBy(*this);
}


SwarmBacterium::~SwarmBacterium(){
    SonSwarm->popBact(this); //Permet de retirer la bactérie de son Swarm quand elle est détruite

    // prise en compte de la destruction de la bactérie dans les statistiques
    --Data4Graphs[s::SWARM_BACTERIA];
    Data4Graphs[s::SPEED] -= getConfig()["speed"]["initial"].toDouble();
}

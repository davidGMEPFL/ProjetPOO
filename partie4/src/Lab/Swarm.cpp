#include "Swarm.hpp"
#include <vector>
#include <string.h>
#include "Application.hpp"
#include "Utility/MutableColor.hpp"
#include "PetriDish.hpp"
#include "SwarmBacterium.hpp"

Swarm::Swarm(std::string const& id): id(id)
{
}

void Swarm::update(sf::Time dt) {
    double scoreLeader(getAppEnv().getPositionScore(leader->getPosition()));
    for(auto& bact : mesBacts){
//        getAppEnv().getPositionScore(bact);
        if(getAppEnv().getPositionScore(bact->getPosition())>scoreLeader){
            leader=bact;
            scoreLeader=(getAppEnv().getPositionScore(leader->getPosition()));
        }
    }
}

void Swarm::addSwarmBacterium(SwarmBacterium* Bact){
    mesBacts.push_back(Bact);
//    getAppEnv().getPositionScore(Bact->);
}

//void Swarm::PopBact(SwarmBacterium * Bact){
// // Rien
//}

Vec2d Swarm::getPosLeader(){
    return leader->getPosition();
}


sf::Color Swarm::getColor(){
    return MutableColor(getAppConfig()["swarms"][id]["color"]).get();
}


j::Value& Swarm::getConfig() const
{
    return getAppConfig()["swarms"][id];
}

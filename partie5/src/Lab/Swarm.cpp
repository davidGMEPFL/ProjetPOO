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
    findLeader();

}

void Swarm::findLeader(){
    if(!mesBacts.empty()){
        leader=mesBacts[0];
        for(auto& bact : mesBacts){
            if(getAppEnv().getPositionScore(bact->getPosition())>getAppEnv().getPositionScore(leader->getPosition()))
                leader=bact;
                    }
    }
}


void Swarm::addSwarmBacterium(SwarmBacterium* Bact){
    mesBacts.push_back(Bact);
}


void Swarm::popBact(SwarmBacterium* aDetruire){
    bool estLeader(leader==aDetruire);
    for(auto& Bact : mesBacts){
        if(Bact==aDetruire) Bact=nullptr;
    }
    mesBacts.erase(std::remove(mesBacts.begin(), mesBacts.end(), nullptr), mesBacts.end());
    if (estLeader) findLeader();
}




Vec2d Swarm::getPosLeader()const{
    return leader->getPosition();
}

SwarmBacterium *Swarm::getLeader() const{
    return leader;
}

MutableColor Swarm::getColor()const{
    return MutableColor(getAppConfig()["swarms"][id]["color"]);
}

std::string Swarm::getId() const{
    return id;
}


j::Value& Swarm::getConfig() const
{
    return getAppConfig()["swarms"][id];
}

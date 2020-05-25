#include "Swarm.hpp"
#include <vector>
#include <string.h>
#include "Application.hpp"
#include "SwarmBacterium.hpp"

Swarm::Swarm(std::string const& id): id(id)
{
}

void Swarm::update(sf::Time dt)
{
    findLeader(); // Encapsulation nécessaire pour chercher un leader en dehors
    //de la méthode update (e.g. quand on n'a pas accés au dt)

}

void Swarm::findLeader()
{
    if(!mesBacts.empty()) { // si le Swarm est vide, risque de SegFault en appelant les méthodes -> on ne fait rien
        leader=mesBacts[0]; // Choix nécessaire puisque la case 0 est toujours occupée (même si c'est la seule)
        for(auto& bact : mesBacts) {
            // Changement de leader si une autre bactérie du Swarm a un meilleur score
            if(getAppEnv().getPositionScore(bact->getPosition())>getAppEnv().getPositionScore(leader->getPosition()))
                leader=bact;
        }
    }
}


void Swarm::addSwarmBacterium(SwarmBacterium* Bact)
{
    mesBacts.push_back(Bact);
}


void Swarm::popBact(SwarmBacterium* aDetruire)
{
    bool estLeader(leader==aDetruire); // Permet de garder l'information même quand la bactérie est détruite
    for(auto& Bact : mesBacts) {
        if(Bact==aDetruire) Bact=nullptr; // Encore une fois, le test fonctionne parce qu'on utilise partout le même pointeur
    }
    mesBacts.erase(std::remove(mesBacts.begin(), mesBacts.end(), nullptr), mesBacts.end());
    if (estLeader) findLeader(); // Permet de toujours avoir un leader!
    // Necessaire pour que les autres bactéries puissent calculer la force
}




Vec2d Swarm::getPosLeader()const
{
    return leader->getPosition();
}

SwarmBacterium *Swarm::getLeader() const
{
    return leader;
}

MutableColor Swarm::getColor()const
{
    return MutableColor(getAppConfig()["swarms"][id]["color"]);
}
std::string Swarm::getId() const
{
    return id;
}
j::Value& Swarm::getConfig() const
{
    return getAppConfig()["swarms"][id];
}

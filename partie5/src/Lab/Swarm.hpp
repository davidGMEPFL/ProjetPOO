#pragma once
#include "Interface/Updatable.hpp"
#include "Utility/Vec2d.hpp"
#include "Utility/MutableColor.hpp"
#include "Bacterium.hpp"

class SwarmBacterium;


class Swarm: public Updatable
{
    std::string id;
    std::vector<SwarmBacterium*> mesBacts; // Le Swarm connait les bactéries qui lui appartiennent
    SwarmBacterium* leader;


    void findLeader();
public:
    Swarm(std::string const&);
    void update(sf::Time dt) override;


    j::Value& getConfig() const;
    void addSwarmBacterium(SwarmBacterium *); // Ajout des ptrs dans le Swarm
    void popBact(SwarmBacterium*); // Permet de retirer une bactérie du Swarm à sa destruction

// Getters utiles
    Vec2d getPosLeader() const; // Necessaire pour le calcul de la force
    SwarmBacterium *getLeader() const;
    std::string getId() const;
    MutableColor getColor() const;
};

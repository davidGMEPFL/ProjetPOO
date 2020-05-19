#include "NutrimentB.hpp"
#include "Application.hpp"
//#include<Lab/Bacterium.hpp>
//#include<Lab/TwitchingBacterium.hpp>
//#include<Lab/SwarmBacterium.hpp>
//#include<Lab/SimpleBacterium.hpp>

NutrimentB::NutrimentB(const Quantity& nbNutriments,const Vec2d& position):
    Nutriment(nbNutriments,position)
{}

j::Value  NutrimentB::getConfig() const
{
    return getAppConfig()["nutriments"]["B"];
}

// IMPACT DIFFERENCIE :

Quantity NutrimentB::eatenBy(Bacterium &bact) {     //polymorphisme sur nutriments
    return bact.eatableQuantity(*this);
}

// Qtité nutriment consommée selon type de bactérie :

Quantity NutrimentB::eatenBy(SimpleBacterium& bacterium)
{
    return takeQuantity(bacterium.mealMax()/getConfig()["resistance factor"].toDouble());
}   //difficilement consommable pour les Simple

Quantity NutrimentB::eatenBy(TwitchingBacterium& bacterium)
{
    double factor1(getConfig()["nutritive factor"].toDouble());
    return factor1 * takeQuantity(bacterium.mealMax());
}   //plus nutritifs pour les Twitching

Quantity NutrimentB::eatenBy(SwarmBacterium& bacterium)
{
    double factor2(getConfig()["poison factor"].toDouble());
    return -factor2 * takeQuantity(bacterium.mealMax());
}   //toxiques pour les Swarm


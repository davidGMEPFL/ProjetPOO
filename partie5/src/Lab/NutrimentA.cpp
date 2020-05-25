#include "NutrimentA.hpp"
#include "Application.hpp"
//#include<Lab/Bacterium.hpp>
//#include<Lab/TwitchingBacterium.hpp>
//#include<Lab/SwarmBacterium.hpp>
//#include<Lab/SimpleBacterium.hpp>

NutrimentA::NutrimentA(const Quantity& nbNutriments,const Vec2d& position):
    Nutriment(nbNutriments,position)
{}

j::Value NutrimentA::getConfig() const
{
    return getAppConfig()["nutriments"]["A"];
}

// IMPACT DIFFERENCIE :

Quantity NutrimentA::eatenBy(Bacterium &bact)    //polymorphisme sur bactéries
{
    return bact.eatableQuantity(*this);
}

//Qtité nutriment consommée : toujours qtité max consommable
Quantity NutrimentA::eatenBy(SimpleBacterium& bacterium)
{
    return takeQuantity(bacterium.mealMax());
}

Quantity NutrimentA::eatenBy(TwitchingBacterium& bacterium)
{
    return takeQuantity(bacterium.mealMax());
}

Quantity NutrimentA::eatenBy(SwarmBacterium& bacterium)
{
    return takeQuantity(bacterium.mealMax());
}

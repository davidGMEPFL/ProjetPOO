#include "NutrimentB.hpp"
#include "Application.hpp"

NutrimentB::NutrimentB(const Quantity& nbNutriments,const Vec2d& position):
    Nutriment(nbNutriments,position)
{}

j::Value const& NutrimentB::getConfig(){
    return getAppConfig()["nutriments"]["B"];
}

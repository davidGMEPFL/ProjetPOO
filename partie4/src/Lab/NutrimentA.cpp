#include "NutrimentA.hpp"
#include "Application.hpp"

NutrimentA::NutrimentA(const Quantity& nbNutriments,const Vec2d& position):
    Nutriment(nbNutriments,position)
{}

j::Value NutrimentA::getConfig() const{
    return getAppConfig()["nutriments"]["A"];
}

#include "NutrimentB.hpp"
#include "Application.hpp"

NutrimentB::NutrimentB(const Quantity& nbNutriments,const Vec2d& position):
    Nutriment(nbNutriments,position)
{}

j::Value  NutrimentB::getConfig() const {
    return getAppConfig()["nutriments"]["B"];
}

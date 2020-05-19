#pragma once
#include "Nutriment.hpp"
#include "Utility/Types.hpp"


class Bacterium;
class SimpleBacterium;
class TwitchingBacterium;
class SwarmBacterium;


class NutrimentB : public Nutriment
{
public:
    NutrimentB(const Quantity&,const Vec2d&);
    j::Value  getConfig() const override;

// Impact différencié des nutriments
    Quantity eatenBy(Bacterium& bact) override;
    Quantity eatenBy(SimpleBacterium& bact) override;
    Quantity eatenBy(TwitchingBacterium& bact) override;
    Quantity eatenBy(SwarmBacterium& bact) override;
};

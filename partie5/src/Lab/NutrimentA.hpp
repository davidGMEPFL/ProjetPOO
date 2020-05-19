#pragma once
#include "Nutriment.hpp"
#include "Utility/Types.hpp"


class NutrimentA: public Nutriment
{
public:
    NutrimentA(const Quantity&,const Vec2d&);
    j::Value  getConfig() const override;

// Impact différencié des nutriments sur bactéries
    Quantity eatenBy(Bacterium& bact) override;
    Quantity eatenBy(SimpleBacterium& bact) override;
    Quantity eatenBy(TwitchingBacterium& bact) override;
    Quantity eatenBy(SwarmBacterium& bact) override;

};

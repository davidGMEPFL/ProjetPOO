#pragma once
#include "Nutriment.hpp"
#include "Utility/Types.hpp"


class NutrimentB: public Nutriment
{
public:
    NutrimentB(const Quantity&,const Vec2d&);
    j::Value  getConfig() const override;

    //impact différencié des nutriments
    Quantity eatenBy(Bacterium& bact) override;
    Quantity eatenBy(SimpleBacterium& bact) override;
    Quantity eatenBy(TwitchingBacterium& bact) override;
    Quantity eatenBy(SwarmBacterium& bact) override;
};

#pragma once
#include "Nutriment.hpp"
#include "Utility/Types.hpp"


class NutrimentA: public Nutriment
{
public:
    NutrimentA(const Quantity&,const Vec2d&);
    j::Value  getConfig() const override;
};

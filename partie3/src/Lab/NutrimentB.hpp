#pragma once
#include "Nutriment.hpp"
#include "Utility/Types.hpp"


class NutrimentB: public Nutriment
{
public:
    NutrimentB(const Quantity&,const Vec2d&);
    j::Value const getConfig() override;
};

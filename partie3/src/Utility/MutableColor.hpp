#pragma once
#include "MutableNumber.hpp"
#include <array>
#include "Utility.hpp"
#include "SFML/Graphics.hpp"


class MutableColor
{
private :
    std::array<MutableNumber, 4> RGBA;

public:
    MutableColor(j::Value const& config);

    void mutate();
    sf::Color get() const;
};



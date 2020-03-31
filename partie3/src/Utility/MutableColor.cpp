#include "MutableColor.hpp"


MutableColor::MutableColor(j::Value const& config)
    : RGBA({MutableNumber(config["r"]),MutableNumber(config["g"]),
      MutableNumber(config["b"]),MutableNumber(config["a"])})
{}

void MutableColor::mutate(){
    for(auto& elem : RGBA) elem.mutate();
}


sf::Color MutableColor::get() {
    return { static_cast<sf::Uint8>(RGBA[0].get() * 255),
             static_cast<sf::Uint8>(RGBA[1].get() * 255),
             static_cast<sf::Uint8>(RGBA[2].get() * 255),
             static_cast<sf::Uint8>(RGBA[3].get() * 255) };
}

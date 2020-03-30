#pragma once
#include "CircularBody.hpp"
#include "Utility/Vec2d.hpp"
#include "Utility/Types.hpp"
#include "SFML/Graphics.hpp"
#include "Interface/Updatable.hpp"
#include "Interface/Drawable.hpp"

class Nutriment : public CircularBody, public Updatable, public Drawable {
    Quantity nbNutriments;
public:
    Nutriment(const Quantity&,const Vec2d&);

    Quantity takeQuantity(Quantity);
    void setQuantity(Quantity const&);
    void drawOn(sf::RenderTarget& target) ;
    void update(sf::Time dt);
    virtual j::Value const getConfig()=0;
};

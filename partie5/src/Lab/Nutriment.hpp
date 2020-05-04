#pragma once
#include "CircularBody.hpp"
#include "Utility/Vec2d.hpp"
#include "Utility/Types.hpp"
#include "SFML/Graphics.hpp"
#include "Interface/Updatable.hpp"
#include "Interface/Drawable.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"

class Bacterium;

class Nutriment : public CircularBody, public Updatable, public Drawable
{
protected:
    Quantity nbNutriments;
public:
    Nutriment(const Quantity&,const Vec2d&);

    Quantity takeQuantity(Quantity);
    void setQuantity(Quantity const&);

    //méthodes polymorphiques renvoyant qtité nut consommée slon type bactérie
    virtual Quantity eatenBy(Bacterium& bact) = 0;
    virtual Quantity eatenBy(SimpleBacterium& bact) = 0;
    virtual Quantity eatenBy(TwitchingBacterium& bact) = 0;
    virtual Quantity eatenBy(SwarmBacterium& bact) = 0;


    double getScoreNutriment(const Vec2d&);


    void drawOn(sf::RenderTarget& target) const;

    void update(sf::Time dt);
    bool testEpuise();

    virtual j::Value getConfig() const =0;
};

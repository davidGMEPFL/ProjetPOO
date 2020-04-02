#pragma once
#include "Bacterium.hpp"
#include "Utility/DiffEqSolver.hpp"

class SimpleBacterium: public Bacterium, public DiffEqFunction
{
    double t;
    double rotation;
public:
    SimpleBacterium(Vec2d);
    j::Value& getConfig() const;
    void move(sf::Time dt) override;
    Vec2d f(Vec2d position, Vec2d speed) const override;
    Vec2d getSpeedVector();
    void drawOn(sf::RenderTarget&) const override;
    Bacterium* clone() const;
    void update(sf::Time dt);
};



//class EquaSimpBact : public DiffEqFunction{
//public:
//    Vec2d f(Vec2d position, Vec2d speed) const override;
//}

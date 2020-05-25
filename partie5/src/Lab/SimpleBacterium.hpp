#pragma once
#include "Bacterium.hpp"
#include "Utility/DiffEqSolver.hpp"


class NutrimentA;
class NutrimentB;

class SimpleBacterium : public Bacterium, public DiffEqFunction
{
    double t;   // timer pour l'ondulation de la flagelle
    double rotation; //angle rotation flagelle
    double ancien_score; // score position précédente
    double TimerTumble; // temps écoulé entre basculements

    void update(sf::Time dt) override;

    Vec2d f(Vec2d position, Vec2d speed) const override; //force appliquée
    Vec2d getSpeedVector(); //retourne le vecteur vitesse

    j::Value& getConfig() const override;
public:
    SimpleBacterium(const Vec2d &);

// Méthodes utilitaires
    void drawOn(sf::RenderTarget&) const override;
    Bacterium* clone() const override;
    void move(sf::Time dt) override;

// Consommation selon nutriment
    Quantity eatableQuantity(NutrimentA& nutriment) override;
    Quantity eatableQuantity(NutrimentB& nutriment) override;

    ~SimpleBacterium();
};

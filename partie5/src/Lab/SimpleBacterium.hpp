#pragma once
#include "Bacterium.hpp"
#include "Utility/DiffEqSolver.hpp"


class NutrimentA;
class NutrimentB;

class SimpleBacterium : public Bacterium, public DiffEqFunction
{
    double t;
    double rotation; //angle rotation flagelle
    double ancien_score; // score position précédente
    double TimerTumble; // temps écoulé entre basculements
public:
    SimpleBacterium(const Vec2d &);

    j::Value& getConfig() const;

// Méthodes utilitaires
    void drawOn(sf::RenderTarget&) const override;
    void update(sf::Time dt);
    Bacterium* clone() const override;

// Déplacement de la bactérie
    void move(sf::Time dt) override;
    Vec2d f(Vec2d position, Vec2d speed) const override; //force de déplacement
    Vec2d getSpeedVector(); //retourne le vecteur vitesse

// Consommation selon nutriment
    Quantity eatableQuantity(NutrimentA& nutriment) override;
    Quantity eatableQuantity(NutrimentB& nutriment) override;

    ~SimpleBacterium();
};

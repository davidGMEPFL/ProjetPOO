#pragma once
#include "Bacterium.hpp"
#include "Grip.hpp"

class NutrimentA; //prédéclaration pour éviter dépendance circulaire
class NutrimentB;

enum Etats {IDLE, WAIT_TO_DEPLOY, DEPLOY, ATTRACT, RETRACT, EAT};
//énumération des différents états possibles de la bactérie

class TwitchingBacterium : public Bacterium
{
private:
    Grip grapin;
    double longueur_tentacule;
    Etats etat{};

public:
    TwitchingBacterium(const Vec2d&); //constructeur

    j::Value& getConfig() const override;
    void drawOn(sf::RenderTarget&) const override;
    Bacterium* clone() const override;

// Méthodes déplacement
    void moveGrip(const Vec2d& delta);
    void move(sf::Time dt) override;

// Méthodes consommation nutriment
    Quantity eatableQuantity(NutrimentA& nutriment) override;
    Quantity eatableQuantity(NutrimentB& nutriment) override;

// Getters utiles
    double EnergieDepl() const;     //énergie dépensée pour déplacement
    double EnergieTentac() const;   //énargie dépensée pour déploiment du tentacule
    Vec2d direction_tentacule() const; //retourne la direction du tentacule

    ~TwitchingBacterium();
};



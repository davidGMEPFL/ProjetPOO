#pragma once
#include "Bacterium.hpp"
#include "Grip.hpp"
#include <string>

class TwitchingBacterium : public Bacterium
{
private:
    Grip grapin;
    double longueur_tentacule;
    //Vec2d direction_tentacule;
    //int etat;
    enum etat{IDLE=0, WAIT_TO_DEPLOY=1, DEPLOY=2, ATTRACT=3, RETRACT=4, EAT=5};

public:
    TwitchingBacterium(const Vec2d&);

    j::Value& getConfig() const;

    enum Etats{};

    void moveGrip(const Vec2d& delta);

    void drawOn(sf::RenderTarget&) const override;
    void update(sf::Time dt);
    Bacterium* clone() const override;
    void move(sf::Time dt);


    double EnergieDepl() const; //getters utiles
    double EnergieTentac() const;


    Vec2d direction_tentacule() const;
};



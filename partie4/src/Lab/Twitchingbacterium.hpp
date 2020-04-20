#pragma once
#include "Bacterium.hpp"
#include "Grip.hpp"
#include <string>

class TwitchingBacterium : public Bacterium
{
private:
    Grip grapin;
    double longueur_tentacule;
    Vec2d direction_tentacule;
    //int etat;
    enum etat{IDLE=1, WAIT_TO_DEPLOY=2, DEPLOY=3, ATTRACT=4,RETRACT=5,EAT=6};
    double ancien_score;
    double TimerTumble;

public:
    TwitchingBacterium(const Vec2d&);

    j::Value& getConfig() const;

    void moveGrip(const Vec2d& delta);

    void drawOn(sf::RenderTarget&) const override;
    void update(sf::Time dt);
    Bacterium* clone() const override;
    void move(sf::Time dt);


    double EnergieDepl() const; //getters utiles
    double EnergieTentac() const;
    double MaxLength() const ;
};



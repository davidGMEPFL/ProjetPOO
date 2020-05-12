#pragma once
#include "Bacterium.hpp"
#include "Grip.hpp"
#include <string>

class NutrimentA;
class NutrimentB;


enum Etats {IDLE, WAIT_TO_DEPLOY, DEPLOY, ATTRACT, RETRACT, EAT};

class TwitchingBacterium : public Bacterium
{
private:
    Grip grapin;
    double longueur_tentacule;
    //Vec2d direction_tentacule;
    //int etat;
    Etats etat{};

public:
    TwitchingBacterium(const Vec2d&);

    j::Value& getConfig() const;

    void moveGrip(const Vec2d& delta);

    void drawOn(sf::RenderTarget&) const override;
//  void update(sf::Time dt);

    Quantity eatableQuantity(NutrimentA& nutriment) override;
    Quantity eatableQuantity(NutrimentB& nutriment) override;

    Bacterium* clone() const override;
    void move(sf::Time dt);


    double EnergieDepl() const; //getters utiles
    double EnergieTentac() const;
    Vec2d direction_tentacule() const;

    void addToGraph(const std::string & , std::unordered_map<std::string, double> &) override;
    void getAdditional(std::vector<double>&, std::vector<double>&) override;
    void getSpeed(std::vector<double>&);

};



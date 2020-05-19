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
    Etats etat{};

public:
    TwitchingBacterium(const Vec2d&);

    j::Value& getConfig() const;

    void moveGrip(const Vec2d& delta);

    void drawOn(sf::RenderTarget&) const override;

    Bacterium* clone() const override;

    void move(sf::Time dt);

    Quantity eatableQuantity(NutrimentA& nutriment) override;
    Quantity eatableQuantity(NutrimentB& nutriment) override;

    //getters utiles
    double EnergieDepl() const;
    double EnergieTentac() const;
    Vec2d direction_tentacule() const;

    //ajout des données pour le graphe
    void addToGraph(const std::string & , std::unordered_map<std::string, double> &) override;
    void getDataTwitching(std::vector<double>&, std::vector<double>&) override;
    void getSpeed(std::vector<double>&);

};



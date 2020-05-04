#pragma once
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "CircularBody.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Utility/MutableColor.hpp"
#include "Utility/Vec2d.hpp"
#include "Utility/Types.hpp"
#include <vector>
#include <string>

class Nutriment;
class NutrimentA;
class NutrimentB;

class Bacterium: public Drawable, public Updatable, public CircularBody
{
protected:
    MutableColor couleur;
    Vec2d direction;
    bool abstinence;
    Quantity energie;
    std::map<std::string, MutableNumber> Params;
    sf::Time TimeLastMeal;

public:
    Bacterium(Quantity energie, Vec2d position, Vec2d direction, double rayon, MutableColor couleur);

    virtual void move(sf::Time dt) =0;
    virtual Bacterium* clone()const=0;

    void drawOn(sf::RenderTarget&) const;
    void update(sf::Time dt);

    void eat(Nutriment& nutriment);    //gère consommation nutriments selon bactérie
    virtual Quantity eatableQuantity(NutrimentA& nutriment) = 0; //permet polymorphisme sur nutriments
    virtual Quantity eatableQuantity(NutrimentB& nutriment) = 0;

    void consumeEnergy(Quantity qt);
    bool testMort();
    void division();

    virtual j::Value& getConfig() const =0;

    //Getters utilitaires
    double getMinEnDiv() const;      //énergie minimale nécessaire à la division
    sf::Time getTempsDelay() const; //temps d'attente entre deux consommations de nutriments
    double EnergieDepl() const;     //énergie dépensée à chaque pas de déplacement
    double mealMax() const;        //quantité maximale qu'elle peut consommer

    void mutate();


    void addProperty(const std::string&, MutableNumber);
    MutableNumber& getProperty(const std::string&);

    virtual ~Bacterium();
};

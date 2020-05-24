#pragma once
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "CircularBody.hpp"
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

    static std::unordered_map<std::string, double> Data4Graphs;

public:

    Bacterium(Quantity energie, Vec2d position, Vec2d direction, double rayon, MutableColor couleur);

    virtual j::Value& getConfig() const =0; //à adapter pour chaque type de bactérie par polymorphisme
    void addProperty(const std::string&, MutableNumber);
    MutableNumber& getProperty(const std::string&); // propre aux paramètres mutables de chaque type de bactérie

// Méthodes utilitaires
    void drawOn(sf::RenderTarget&) const;
    void update(sf::Time dt);
    void mutate();

// A redéfinir pour chaque type de bactérie
    virtual void move(sf::Time dt) =0;
    virtual Bacterium* clone()const=0;

// Consommation nutriments
    void eat(Nutriment& nutriment);    //gère consommation nutriments selon bactérie
    virtual Quantity eatableQuantity(NutrimentA& nutriment) = 0; //permet polymorphisme sur nutriments
    virtual Quantity eatableQuantity(NutrimentB& nutriment) = 0;

// Actions en fonction énergie
    void consumeEnergy(Quantity qt);
    bool testMort()const;
    void division();

// Getters utilitaires
    double getMinEnDiv() const;       //énergie minimale nécessaire à la division
    sf::Time getTempsDelay() const;  //temps d'attente entre deux consommations de nutriments
    double EnergieDepl() const;     //énergie dépensée à chaque pas de déplacement
    double mealMax() const;        //quantité maximale qu'elle peut consommer

// Methods for getting data for the graphs
//    virtual void getDataTwitching(std::vector<double>&, std::vector<double>&); //collecte les tailles de tentacule + sa vitesse
//    virtual void getSpeed(std::vector<double>&) =0;                            //collecte les vitesses des bactéries qui en ont
//    virtual void getDataSimple(std::vector<double>&, std::vector<double>&); //collecte les basculements selon les tumble

    static std::unordered_map<std::string, double>& accesMap(){
        return Data4Graphs;
    }

// Destructeur
    virtual ~Bacterium();
};



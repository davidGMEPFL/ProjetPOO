#pragma once
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "CircularBody.hpp"
#include "Utility/MutableColor.hpp"
#include "Utility/Vec2d.hpp"
#include "Utility/Types.hpp"
#include <vector>
#include <string>

class Nutriment; //prédéfintion des nutriments pour éviter dépendance circulaire
class NutrimentA;
class NutrimentB;

class Bacterium: public Drawable, public Updatable, public CircularBody
{
protected:
    MutableColor couleur;
    Vec2d direction;
    bool abstinence;
    Quantity energie;
    std::map<std::string, MutableNumber> Params; //map de tous les paramètres mutables
    sf::Time TimeLastMeal; //compteur temps depuis dernier eat

    static std::unordered_map<std::string, double> Data4Graphs; //map des statistiques actuelles

    virtual j::Value& getConfig() const =0; //accès aux paramètres du fichier app.jason, par polymorphisme


    // A redéfinir pour chaque type de bactérie
    virtual void move(sf::Time dt) =0;
    virtual Bacterium* clone()const=0;

    // Actions liées à la consommation
    void eat(Nutriment& nutriment);    //méthode globale qui gère consommation
    void consumeEnergy(Quantity qt);
    void division(); //commune à tous les types de bactéries
public:

    Bacterium(Quantity energie, Vec2d position, Vec2d direction, double rayon, MutableColor couleur);




    // Méthodes utilitaires
    void mutate(); //fait muter tous les paramètres mutables
    void drawOn(sf::RenderTarget&) const override; // Dessin commun à toutes les bactéries
    void update(sf::Time dt) override; // Commun à toutes les bactéries, mais appelé pour les SimpleBacterium

    void addProperty(const std::string&, MutableNumber); //ajoute un paramètre mutable à la map
    MutableNumber& getProperty(const std::string&); //accès à la valeur du paramètre mutable

    // Consommation nutriments
    virtual Quantity eatableQuantity(NutrimentA& nutriment) = 0; //permet polymorphisme sur bactérie
    virtual Quantity eatableQuantity(NutrimentB& nutriment) = 0;

    bool testMort()const;

// Getters utilitaires
    double getMinEnDiv() const;       //énergie minimale nécessaire à la division
    sf::Time getTempsDelay() const;  //temps d'attente entre deux consommations de nutriments
    double EnergieDepl() const;     //énergie dépensée à chaque pas de déplacement
    double mealMax() const;        //quantité maximale qu'elle peut consommer

// Méthode donnant accès à l'attribut de classe 'map Data4Graphs'
    static std::unordered_map<std::string, double>& accesMap();

// Destructeur
    virtual ~Bacterium();
};



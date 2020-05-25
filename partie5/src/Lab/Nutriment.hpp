#pragma once
#include "CircularBody.hpp"
#include "Interface/Updatable.hpp"
#include "Interface/Drawable.hpp"
#include "Bacterium.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"


class Nutriment : public CircularBody, public Updatable, public Drawable
{
protected:
    Quantity nbNutriments; //nombre de nutriments de la source

public:
    Nutriment(const Quantity&,const Vec2d&); // constructeur

    virtual j::Value getConfig() const =0; // permet d'atteindre les paramètres du fichier
    // app.json de façon polymorphique

// Actions liées à quantité nutriments
    Quantity takeQuantity(Quantity); //prend la qtité de nutriment, si disponible
    void setQuantity(Quantity const&); //fixe la quantité, si admissible
    bool testEpuise() const; //test si aucun nutriment présent

// Méthodes utilitaires
    void drawOn(sf::RenderTarget& target) const override;
    void update(sf::Time dt) override;

// Méthodes polymorphiques renvoyant qtité nut consommée selon type bactérie
    virtual Quantity eatenBy(Bacterium& bact) = 0;
    virtual Quantity eatenBy(SimpleBacterium& bact) = 0;
    virtual Quantity eatenBy(TwitchingBacterium& bact) = 0;
    virtual Quantity eatenBy(SwarmBacterium& bact) = 0;

// Calcul du score d'un nutriment, utile pour donner score de la position
    double getScoreNutriment(const Vec2d&) const;

// Rajoute le nb de nutriments
    void addToGraph(std::unordered_map<std::string, double>&)const;

    ~Nutriment();
};

#pragma once
#include "CircularBody.hpp"
#include "Utility/Vec2d.hpp"
#include "Utility/Types.hpp"
#include "SFML/Graphics.hpp"
#include "Interface/Updatable.hpp"
#include "Interface/Drawable.hpp"
#include "Bacterium.hpp"
#include "SimpleBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "SwarmBacterium.hpp"


class Nutriment : public CircularBody, public Updatable, public Drawable
{
protected:
    Quantity nbNutriments;

public:
    Nutriment(const Quantity&,const Vec2d&);

    virtual j::Value getConfig() const =0; //propre à NutA et NutB

    Quantity takeQuantity(Quantity);
    void setQuantity(Quantity const&); 
    bool testEpuise(); //test si aucun nutriment présent

    void drawOn(sf::RenderTarget& target) const;
    void update(sf::Time dt);

// Méthodes polymorphiques renvoyant qtité nut consommée selon type bactérie, à définir
    virtual Quantity eatenBy(Bacterium& bact) = 0;
    virtual Quantity eatenBy(SimpleBacterium& bact) = 0;
    virtual Quantity eatenBy(TwitchingBacterium& bact) = 0;
    virtual Quantity eatenBy(SwarmBacterium& bact) = 0;

// Calcul du score d'un nutriment, utile pour donner score de la position
    double getScoreNutriment(const Vec2d&);


    void addToGraph(const std::string & ,std::unordered_map<std::string, double>&);
};

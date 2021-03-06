#include "Nutriment.hpp"
#include "Utility/Utility.hpp"
#include <string>
#include "Application.hpp"
#include <math.h>


Nutriment::Nutriment(const Quantity& nbNutriments,const Vec2d& position):
    CircularBody(position,nbNutriments), nbNutriments(nbNutriments)
{
    ++Bacterium::accesMap()[s::NUTRIMENT_SOURCES]; //incrémente le compteur de sources de nutriments
}

// NOMBRE NUTRIMENTS
Quantity Nutriment::takeQuantity(Quantity qtTaken)
{
    /* Retournera la quantité qui a pu être prélevée */

    Quantity ret(nbNutriments); //quantité nut dispo au début
    if((nbNutriments-=qtTaken)>=0) ret=qtTaken;
    else nbNutriments=0; //cas où plus à prélever que disponible
    rayon=nbNutriments; //mise à jour pour l'affichage
    return ret; //quantité de nut prélevée (soit qtTaken, soit nbNutriment)
}
void Nutriment::setQuantity(Quantity const& newQt)
{
    /* Permettant de mettre à jour la quantité de nutriments */

    if(newQt>0) {
        this->nbNutriments=newQt;
    } else {
        nbNutriments=0 ;    //source aura une quantité nulle si on affecte valeur négative
    }
    rayon=nbNutriments;        //rayon s'adapte de façon appropriée
}
bool Nutriment::testEpuise() const
{
    return nbNutriments==0.;
}

// Méthodes utilitaires
void Nutriment::drawOn(sf::RenderTarget& target) const
{
    /* Dessine le fond texturé du nutriment, adapté à son rayon, et affiche sa quantité juste au-dessus */

    //Dessin du Sprite
    auto const& texture = getAppTexture(getConfig()["texture"].toString());
    auto nutrimentSprite = buildSprite(position, rayon, texture);
    // adapte la taille du Sprite au rayon du nutriment:
    nutrimentSprite.setScale(2 * rayon / texture.getSize().x, 2 * rayon / texture.getSize().y);
    target.draw(nutrimentSprite);

    //Dessin du nombre de nutriments si mode debugging activé
    if (isDebugOn()) {
        auto const text = buildText(std::to_string(int(nbNutriments)),position + Vec2d(0,-100),
                                    getAppFont(),18,sf::Color::Black);
        target.draw(text);
    }
}
void Nutriment::update(sf::Time dt)
{
    /* Fait croître la quantité de nutriments à chaque pas de temps */

    double temp(getAppEnv().getTemperature());
    auto const& speed=getConfig()["growth"]["speed"].toDouble();
    auto const& minTemp=getConfig()["growth"]["min temperature"].toDouble();
    auto const& maxTemp=getConfig()["growth"]["max temperature"].toDouble();
    auto const& maxVal=getConfig()["quantity"]["max"].toDouble();
    auto growth = speed * dt.asSeconds(); //croissance du nutriment en fonction du temps

    //Si bornes température respectées + quantité max nut respectée -> croissance
    if(minTemp<=temp && temp<=maxTemp && (nbNutriments+growth)<=2*maxVal) nbNutriments+=growth;
    if(!getAppEnv().contains(*this))nbNutriments-=growth; //si la source dépasse l'assiette -> décroissance
    rayon=nbNutriments; //adaptation rayon
}

double Nutriment::getScoreNutriment(const Vec2d& pos) const
{
    /* Calcul du score de la position choisie, par rapport au nutriment */

    double puissance(getAppEnv().getGradientExponent());
    return nbNutriments/pow(distance(position, pos), puissance);
    //score proportionnel à qtité nutriments et inversement proportionnel à la distance au nutriment
}

// Ajout du nb de nutriments
void Nutriment::addToGraph(std::unordered_map<std::string, double>& GraphTemp) const
{
    GraphTemp[s::NUTRIMENT_QUANTITY] += nbNutriments;
}

//Destructeur : décrémente le compteur de soucres de nutriments
Nutriment::~Nutriment()
{
    --Bacterium::accesMap()[s::NUTRIMENT_SOURCES];
}


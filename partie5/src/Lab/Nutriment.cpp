#include "Nutriment.hpp"
#include "Utility/Utility.hpp"
#include <string>
#include "Application.hpp"

Nutriment::Nutriment(const Quantity& nbNutriments,const Vec2d& position):
    CircularBody(position,nbNutriments), nbNutriments(nbNutriments)
{}

Quantity Nutriment::takeQuantity(Quantity qtTaken) // retournera la quantité qui a pu être prélevée
{
    Quantity ret(nbNutriments); //quantité nut dispo
    if((nbNutriments-=qtTaken)>=0) ret=qtTaken;
    else nbNutriments=0; //cas où plus à prélever que disponible
    rayon=nbNutriments;
    return ret; //quantité de nut prélevée (soit qtTaken, soit nbNut)
}

void Nutriment::setQuantity(Quantity const& newQt) //permettant de mettre à jour la quantité
{
    if(newQt>0){
        this->nbNutriments=newQt;
    } else { nbNutriments=0 ; } //source aura une quantité nulle si on affecte valeur négative
    rayon=nbNutriments;        //rayon s'adapte de façon appropriée
}

bool Nutriment::testEpuise()
{
    return nbNutriments==0.;
}


void Nutriment::drawOn(sf::RenderTarget& target) const
{
    auto const& texture = getAppTexture(getConfig()["texture"].toString());
    auto nutrimentSprite = buildSprite(position, rayon, texture);
    // adapte la taille du Sprite au rayon du nutriment:
    nutrimentSprite.setScale(2 * rayon / texture.getSize().x, 2 * rayon / texture.getSize().y);
    target.draw(nutrimentSprite);

    if (isDebugOn()) {
        auto const text = buildText(std::to_string(int(nbNutriments)),position + Vec2d(0,-100),
                                    getAppFont(),18,sf::Color::Black);
        target.draw(text); //dessin du nombre de nutriments
    }
}

void Nutriment::update(sf::Time dt)
{
    double temp(getAppEnv().getTemperature());
    auto const& speed=getConfig()["growth"]["speed"].toDouble();
    auto const& minTemp=getConfig()["growth"]["min temperature"].toDouble();
    auto const& maxTemp=getConfig()["growth"]["max temperature"].toDouble();
    auto const& maxVal=getConfig()["quantity"]["max"].toDouble();

    //croissance du nutriment en fonction du temps
    auto growth = speed * dt.asSeconds();

    //si bornes température respectées + quantité max nut respectée -> croissance
    if(minTemp<=temp && temp<=maxTemp && (nbNutriments+growth)<=2*maxVal) nbNutriments+=growth;
    if(!getAppEnv().contains(*this))nbNutriments-=growth;
    rayon=nbNutriments; //adaptation rayon
}

double Nutriment::getScoreNutriment(const Vec2d& pos) //calcul du score d'un nutriment
{
    double puissance(getAppEnv().getGradientExponent());
    return nbNutriments/pow(distance(position, pos), puissance);
}

void Nutriment::addToGraph(const std::string & titreGraph ,std::unordered_map<std::string, double>& GraphTemp){
    if (s::GENERAL==titreGraph){
        ++GraphTemp[s::NUTRIMENT_SOURCES];
    }
    else if (s::NUTRIMENT_QUANTITY==titreGraph){
        GraphTemp[s::NUTRIMENT_QUANTITY] += nbNutriments;
    }

}

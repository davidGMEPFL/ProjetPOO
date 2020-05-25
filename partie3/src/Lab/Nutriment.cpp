#include "Nutriment.hpp"
#include "Utility/Utility.hpp"
#include <string>
#include "Application.hpp"

Nutriment::Nutriment(const Quantity& nbNutriments,const Vec2d& position):
    CircularBody(position,nbNutriments), nbNutriments(nbNutriments)
{}

Quantity Nutriment::takeQuantity(Quantity qtTaken)
{
    Quantity ret(nbNutriments);
    if((nbNutriments-=qtTaken)>=0) ret=qtTaken;
    else nbNutriments=0;

    // retournera la quantité qui a pu être prélevée
    rayon=nbNutriments;
    return ret;
}

void Nutriment::setQuantity(Quantity const& newQt)
{
    /*    permettant de mettre à jour la quantité.
     * Il ne devra pas être possible d'affecter une valeur négative à la quantité. Si on tente
     * d'affecter une quantité négative, la source aura au final une quantité nulle.
     * Vous veillerez à ce que le rayon s'adapte de façon appropriée;
    */
    if(newQt>0)this->nbNutriments=newQt;
    else nbNutriments=0;
    rayon=nbNutriments;
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
        target.draw(text);
    }
}

void Nutriment::update(sf::Time dt)
{
    double temp(getAppEnv().getTemperature());
    auto const& speed=getConfig()["growth"]["speed"].toDouble();
    auto const& minTemp=getConfig()["growth"]["min temperature"].toDouble();
    auto const& maxTemp=getConfig()["growth"]["max temperature"].toDouble();
    auto const& maxVal=getConfig()["quantity"]["max"].toDouble();

    auto growth = speed * dt.asSeconds();
    if(minTemp<=temp && temp<=maxTemp && (nbNutriments+growth)<=2*maxVal) nbNutriments+=growth;
    if(!getAppEnv().Petri.contains(*this))nbNutriments-=growth;
    rayon=nbNutriments;
}

bool Nutriment::testEpuise()
{
    return nbNutriments==0.;
}

double Nutriment::getScoreNutriment(const Vec2d& pos)
{
    double puissance(getAppEnv().getGradientExponent());
    return nbNutriments/pow(distance(position, pos), puissance);
}

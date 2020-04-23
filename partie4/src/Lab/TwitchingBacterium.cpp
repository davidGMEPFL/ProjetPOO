#include "TwitchingBacterium.hpp"
#include "Random/Random.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include <SFML/Graphics.hpp>

TwitchingBacterium::TwitchingBacterium(const Vec2d& position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(),getConfig()["energy"]["max"].toDouble()),
                position,  Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"]),

      grapin(position, (uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()))/4),
      longueur_tentacule(0.0)/*, direction_tentacule(direction)*/
{
    addProperty("tentacle length", MutableNumber::positive(getAppConfig()["twitching bacterium"]["tentacle"]["length"]));
    addProperty("tentacle speed", MutableNumber::positive(getAppConfig()["twitching bacterium"]["tentacle"]["speed"]));
}


void TwitchingBacterium::moveGrip(const Vec2d& delta)
{
    /*if(distance(grapin.getPosition(),position)+delta.length() <=getProperty("tentacle length").get())*/{
        grapin.move(delta);
    } /*else {
        grapin.setPosition(position+delta.normalised()*getProperty("tentacle length").get());
    }*/
}


void TwitchingBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);        // dessin bactérie
    double epaisseur(2);              // dessin  segment
    auto line = buildLine(position, grapin.getPosition(), couleur.get(), epaisseur);
    target.draw(line);
    auto border = buildAnnulus(grapin.getPosition(), grapin.getRadius(), couleur.get(), 1);
    target.draw(border);   //dessin grapin
}


Bacterium* TwitchingBacterium::clone() const
{
    TwitchingBacterium* ptr=new TwitchingBacterium(*this);
    ptr->mutate();
    ptr->position+=Vec2d(8.0,8.0);          //décalage du centre du clone
    ptr->grapin.setPosition(ptr->position); // tentacule rétracté
    ptr->moveGrip(Vec2d(1.0, -7.0));        // décalage orientation tentacule
    getAppEnv().addBacterium(ptr, true);
    return ptr;
}

void TwitchingBacterium::move(sf::Time dt)
{
    longueur_tentacule  = distance(grapin.getPosition(),position);
    double longueur_max = getProperty("tentacle length").get();
    double vitesse_tentacule = getProperty("tentacle speed").get();

    Quantity Qt_deploi  (EnergieTentac()*vitesse_tentacule*dt.asSeconds());
    Quantity Qt_depla   (EnergieDepl()*vitesse_tentacule*dt.asSeconds()*
                         getConfig()["speed factor"].toDouble());

    switch(etat) {
    case IDLE : {
        //grapin.setPosition(position);
        etat=WAIT_TO_DEPLOY;
        break;
    }

    case WAIT_TO_DEPLOY: {
        //Basculement
        Vec2d tempRand;
        for (int i(0); i<40; ++i) {
            tempRand=Vec2d::fromRandomAngle();
            if(getAppEnv().getPositionScore(position+tempRand)>
               getAppEnv().getPositionScore(position+direction))
                direction=tempRand;
        }
        etat=DEPLOY;
        break;
    }

    case DEPLOY: {
        moveGrip(direction*vitesse_tentacule*dt.asSeconds());
        consumeEnergy(Qt_deploi);
        if(getAppEnv().getNutrimentColliding(grapin)!=nullptr) etat=ATTRACT;
        else if((longueur_tentacule>=longueur_max)  or getAppEnv().doesCollideWithDish(grapin)) {
            etat=RETRACT;
        }
        break;
    }

    case ATTRACT: {
        if(getAppEnv().getNutrimentColliding(*this)!=nullptr) {
            etat=EAT ;
            break;
        }
//        else { etat=RETRACT ;}
        CircularBody::move(direction_tentacule()*vitesse_tentacule*dt.asSeconds()*
                           getConfig()["speed factor"].toDouble());
        consumeEnergy(Qt_depla);
        if(getAppEnv().getNutrimentColliding(grapin)==nullptr) etat=RETRACT;
        break;
    }

    case RETRACT: {
        if(getAppEnv().getNutrimentColliding(grapin)!=nullptr) {
            etat=ATTRACT ;
            break;
        }
        moveGrip((position-grapin.getPosition()).normalised()*vitesse_tentacule*dt.asSeconds());
        //déplacement grapin dans sens inverse
        consumeEnergy(Qt_deploi);
        if(longueur_tentacule <= rayon) etat=IDLE;
        break;
    }

    case EAT: {
        if(longueur_tentacule>rayon) {
            moveGrip((position-grapin.getPosition()).normalised()*vitesse_tentacule*dt.asSeconds());
            //déplacement grapin dans sens inverse
            consumeEnergy(Qt_deploi);
        }
        if(getAppEnv().getNutrimentColliding(*this)==nullptr && longueur_tentacule<=rayon) {
            etat=IDLE;
        }
        break;
    }
    }
}

//void TwitchingBacterium::update(sf::Time dt)
//{
//    move(dt);
////    Bacterium::update(dt);

//}


j::Value& TwitchingBacterium::getConfig() const
{
    return getAppConfig()["twitching bacterium"];
}

//getters
double TwitchingBacterium::EnergieDepl() const
{
    return getConfig()["energy"]["consumption factor"]["move"].toDouble();
}

double TwitchingBacterium::EnergieTentac() const
{
    return getConfig()["energy"]["consumption factor"]["tentacle"].toDouble();
}


Vec2d TwitchingBacterium::direction_tentacule() const
{
    return (grapin.getPosition()-position).normalised();
}

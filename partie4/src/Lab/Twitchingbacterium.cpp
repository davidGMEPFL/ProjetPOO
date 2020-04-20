#include "Twitchingbacterium.hpp"
#include "Random/Random.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include <SFML/Graphics.hpp>

TwitchingBacterium::TwitchingBacterium(const Vec2d& position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(),getConfig()["energy"]["max"].toDouble()),
      position,  Vec2d::fromRandomAngle() ,
      uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()),
      getConfig()["color"]),

      grapin(position, (uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()))/4),
      longueur_tentacule(0.0), direction_tentacule(direction),
      ancien_score(getAppEnv().getPositionScore(position-direction)), TimerTumble(0)
{     addProperty("tentacle length", MutableNumber::positive(getAppConfig()["twitching bacterium"]["tentacle"]["length"]));
      addProperty("tentacle speed", MutableNumber::positive(getAppConfig()["twitching bacterium"]["tentacle"]["speed"]));
}


j::Value& TwitchingBacterium::getConfig() const{
    return getAppConfig()["twitching bacterium"];
}

void TwitchingBacterium::moveGrip(const Vec2d& delta){
    if(distance(grapin.getPosition(),position)+delta.length() <=MaxLength()){
      grapin.move(delta);
    } else {
      grapin.setPosition(position+direction_tentacule*MaxLength());
    }
}


void TwitchingBacterium::drawOn(sf::RenderTarget& target) const{
    Bacterium::drawOn(target);        // dessin bactérie
    double epaisseur(2);              // dessin  segment
    auto line = buildLine(position, grapin.getPosition(), couleur.get(), epaisseur);
    target.draw(line);
    auto border = buildAnnulus(grapin.getPosition(), grapin.getRadius(), couleur.get(), 1);
    target.draw(border);   //dessin grapin
}



Bacterium* TwitchingBacterium::clone() const{
    TwitchingBacterium* ptr=new TwitchingBacterium(*this);
    ptr->mutate();
    ptr->position+=Vec2d(0.0,8.0);          //décalage du centre du clone
    ptr->grapin.setPosition(ptr->position); // tentacule rétracté
    ptr->moveGrip(Vec2d(1.0, -7.0));        // décalage orientation tentacule
    getAppEnv().addBacterium(ptr, true);
        return ptr;
}

void TwitchingBacterium::move(sf::Time dt){
    longueur_tentacule  = distance(grapin.getPosition(),position);
    double longueur_max = getConfig()["twitching bacterium"]["tentacle"]["length"].toDouble();
    direction_tentacule = (grapin.getPosition()-position).normalised();
    double vitesse_tentacule (getConfig()["twitching bacterium"]["tentacle"]["speed"].toDouble());
    Vec2d tempRand;
    Quantity Qt_deploi  (EnergieTentac()*vitesse_tentacule*dt.asSeconds());
    Quantity Qt_depla   (EnergieDepl()*vitesse_tentacule*dt.asSeconds()*
                         getConfig()["twitching bacterium"]["tentacle"]["speed factor"].toDouble());

//    switch (etat) {
//         case IDLE : //IDLE
//              //grapin.setPosition(position);
//              etat=WAIT_TO_DEPLOY;
//              break;

//         case WAIT_TO_DEPLOY:
//              //Basculement
//              if (score>=ancien_score) lambda=getProperty("tumble better").get();
//                  else lambda= getProperty("tumble worse").get();
//
//                  for (int i(0); i<getConfig()["tumble"]["algo"]["best of N"].toDouble(); ++i){
//                  tempRand=Vec2d::fromRandomAngle();
//                  if(getAppEnv().getPositionScore(position+tempRand)>
//                        getAppEnv().getPositionScore(position+direction))
//                    direction=tempRand;
//              }
//              ancien_score=score;
//              direction_tentacule=direction;
//              break;

//         case DEPLOY:
//              moveGrip(direction*vitesse_tentacule*dt.asSeconds());
//              consumeEnergy(Qt_deploi);
//              if(((longueur_tentacule==longueur_max) and (grapin.isColliding(Nutriment))) or grapin.isColliding(Petri)) {etat=RETRACT};
//        break;
//         case RETRACT:
//                        do { moveGrip(((position-grapin.getPosition()).normalised())*vitesse_tentacule*dt.asSeconds());
//                             //déplacement grapin dans sens inverse
//                             consumeEnergy(Qt_deploi);
//                        } while(longueur_tentacule > rayon); // longueur min tentac atteinte
//                        break;                               //retourne à case 0 IDLE
//              } else {}
//         case ATTRACT:
//              CircularBody::move(direction_tentacule*vitesse_tentacule*dt.asSeconds()*
//                                 getConfig()["twitching bacterium"]["tentacle"]["speed factor"].toDouble());
//              consumeEnergy(Qt_depla);
//              if(nutriment existe encore) {
//         case EAT:

//                  break;
//           }
//   }
}

void TwitchingBacterium::update(sf::Time dt){
    while(!testMort()) {
          move(dt);
          Bacterium::update(dt);
    }
}

//getters
double TwitchingBacterium::EnergieDepl() const{
    return getConfig()["energy"]["consumption factor"]["move"].toDouble();
}

double TwitchingBacterium::EnergieTentac() const{
    return getConfig()["energy"]["consumption factor"]["tentacle"].toDouble();
}

double TwitchingBacterium::MaxLength() const{
    return getConfig()["twitching bacterium"]["tentacle"]["length"].toDouble();
}

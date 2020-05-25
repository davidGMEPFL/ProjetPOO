#include "TwitchingBacterium.hpp"
#include "Random/Random.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include <Lab/NutrimentA.hpp>
#include <Lab/NutrimentB.hpp>

using namespace std;

TwitchingBacterium::TwitchingBacterium(const Vec2d& position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(),getConfig()["energy"]["max"].toDouble()),
                position,  Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"]),

      grapin(position, (uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()))/4),
      longueur_tentacule(0.0)
{
    addProperty("tentacle length", MutableNumber::positive(getAppConfig()["twitching bacterium"]["tentacle"]["length"]));
    addProperty("tentacle speed", MutableNumber::positive(getAppConfig()["twitching bacterium"]["tentacle"]["speed"]));

    /* prise en compte de la nouvelle bactérie dans les statistiques */
    ++Data4Graphs[s::TWITCHING_BACTERIA];
    Data4Graphs[s::TENTACLE_LENGTH]+=getProperty("tentacle length").get();
    Data4Graphs[s::TENTACLE_SPEED]+=getProperty("tentacle speed").get();
    Data4Graphs[s::SPEED] += getProperty("tentacle speed").get()*getConfig()["speed factor"].toDouble();
}



j::Value& TwitchingBacterium::getConfig() const
{
    return getAppConfig()["twitching bacterium"];
}

void TwitchingBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);       // dessin bactérie
    double epaisseur(2);
    auto line = buildLine(position, grapin.getPosition(), couleur.get(), epaisseur);
    target.draw(line);               // dessin  segment
    auto border = buildAnnulus(grapin.getPosition(), grapin.getRadius(), couleur.get(), 1);
    target.draw(border);             //dessin grapin
}

Bacterium* TwitchingBacterium::clone() const
{
    TwitchingBacterium* ptr=new TwitchingBacterium(*this); //création d'un pointeur sur une copie
    ptr->mutate();
    ptr->position+=Vec2d(8.0,8.0);          //décalage du centre du clone
    ptr->moveGrip(Vec2d(1.0, -7.0));        // décalage orientation tentacule
    getAppEnv().addBacterium(ptr, true);    //ajout du clone dans le vecteur des clones

    /* prise en compte de la bactérie clonée dans les statistiques */
    ++Data4Graphs[s::TWITCHING_BACTERIA];
    Data4Graphs[s::TENTACLE_LENGTH]+= ptr->getProperty("tentacle length").get();
    Data4Graphs[s::TENTACLE_SPEED] += ptr->getProperty("tentacle speed").get();
    Data4Graphs[s::SPEED] += ptr->getProperty("tentacle speed").get()*ptr->getConfig()["speed factor"].toDouble();

    return ptr;
}


//DEPLACEMENT :
void TwitchingBacterium::moveGrip(const Vec2d& delta)
{
        grapin.move(delta);
}


void TwitchingBacterium::move(sf::Time dt)
{ /* Permet de mouvoir la bactérie en la faisant passer d'un état à l'autre */

    longueur_tentacule  = distance(grapin.getPosition(),position);
    double longueur_max = getProperty("tentacle length").get();
    double vitesse_tentacule = getProperty("tentacle speed").get();
    Quantity Qt_deploi (EnergieTentac()*vitesse_tentacule*dt.asSeconds());
    Quantity Qt_depla  (EnergieDepl()*vitesse_tentacule*dt.asSeconds()*
                         getConfig()["speed factor"].toDouble());

    switch(etat) {
    case IDLE : {
        /* Par défaut ou pour commencer, elle est en état IDLE avec un grapin rétracté */
        etat=WAIT_TO_DEPLOY;
        break;
    }

    case WAIT_TO_DEPLOY: {
        /* Avant de déployer son tentacule, elle choisit parmi plusieurs directions
           celle qui est la plus avantageuse (meilleur score) */
        Vec2d tempRand;
        for (int i(0); i<20; ++i) {
            tempRand=Vec2d::fromRandomAngle();  //choix aléatoire de direction
            if(getAppEnv().getPositionScore(position+tempRand)>
                    getAppEnv().getPositionScore(position+direction))
                direction=tempRand;
        }
        etat=DEPLOY;
        break;
    }

    case DEPLOY: {
        //Déplacement grapin selon direction choisie
        moveGrip(direction*vitesse_tentacule*dt.asSeconds());
        consumeEnergy(Qt_deploi);

        if(getAppEnv().getNutrimentColliding(grapin)!=nullptr) etat=ATTRACT; //si grapin touche un nutriment, la bactérie s'approche
        else if((longueur_tentacule>=longueur_max)  or getAppEnv().doesCollideWithDish(grapin)) {
            etat=RETRACT;
            // si longueur max du tentacule atteinte sans avoir touché de nutriment ou bord assiette touché, alors se rétracte
        }
        break;
    }

    case ATTRACT: {
        /* Si la bactérie touche la source de nutriment, elle passe à l'état EAT.
           Sinon, elle se déplace dans la même direction que son tentacule et perd en conséquence de l'énergie.
           Dans la cas où le nutriment a disparu entre temps, elle se rétracte. */

        if(getAppEnv().getNutrimentColliding(*this)!=nullptr) { //bactérie en collision avec source nutriment
            etat=EAT ;
            break;
        }
        CircularBody::move(direction_tentacule()*vitesse_tentacule*dt.asSeconds()*
                           getConfig()["speed factor"].toDouble()); //déplacement vers source nutriment
        consumeEnergy(Qt_depla);
        if(getAppEnv().getNutrimentColliding(grapin)==nullptr) etat=RETRACT; //si le nutriment a disparu
        break;
    }

    case RETRACT: {
        /* Le tentacule se rétracte si le grapin touche le bord de l'assiette ou
           si sa longueur max a été atteinte sans avoir trouvé de nutriment.
         * Si le grapin touche une source, la bactérie passe à ATTRACT.
         * Sinon, le tentacule se rétracte et perd de l'énergie en conséquence, puis revient à l'état IDLE */

        if(getAppEnv().getNutrimentColliding(grapin)!=nullptr) { //grapin trouve un nutriment
            etat=ATTRACT ;
            break;
        }
        //Déplacement grapin dans sens inverse
        moveGrip((position-grapin.getPosition()).normalised()*vitesse_tentacule*dt.asSeconds());
        consumeEnergy(Qt_deploi);
        if(longueur_tentacule <= rayon) etat=IDLE; //distance du centre au grapin inférieure au rayon bactérie
        break;
    }

    case EAT: {
        /* Si la bactérie est en train de manger, elle continue de rétracter son grapin */
        if(longueur_tentacule>rayon) {
            moveGrip((position-grapin.getPosition()).normalised()*vitesse_tentacule*dt.asSeconds());
            //déplacement grapin dans sens inverse
            consumeEnergy(Qt_deploi);
        }
        if(getAppEnv().getNutrimentColliding(*this)==nullptr && longueur_tentacule<=rayon) {
            etat=IDLE; //plus de nutriment en contact et tentacule rétracté
        }
        break;
    }
    }
}


//EAT spécifique :
Quantity TwitchingBacterium::eatableQuantity(NutrimentA& nutriment){
    return nutriment.eatenBy(*this); //retourne quantité nutA mangeable
}
Quantity TwitchingBacterium::eatableQuantity(NutrimentB& nutriment) {
    return nutriment.eatenBy(*this); //retourne quantité nutB mangeable
}


//GETTERS :
double TwitchingBacterium::EnergieDepl() const
{
    return getConfig()["energy"]["consumption factor"]["move"].toDouble();
}
double TwitchingBacterium::EnergieTentac() const
{
    return getConfig()["energy"]["consumption factor"]["tentacle"].toDouble();
}
Vec2d TwitchingBacterium::direction_tentacule() const
{/* Retourne la différence normalisée entre la position du grapin et celle de la bactérie */
    return (grapin.getPosition()-position).normalised();
}

//Destructeur : prise en compte de la destruction de la bactérie dans les statistiques
TwitchingBacterium::~TwitchingBacterium(){
    --Data4Graphs[s::TWITCHING_BACTERIA];
    Data4Graphs[s::TENTACLE_LENGTH]-= getProperty("tentacle length").get();
    Data4Graphs[s::TENTACLE_SPEED] -= getProperty("tentacle speed").get();
    Data4Graphs[s::SPEED] -= getProperty("tentacle speed").get()*getConfig()["speed factor"].toDouble();
}


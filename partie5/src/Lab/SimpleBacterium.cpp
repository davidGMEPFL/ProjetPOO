#include "SimpleBacterium.hpp"
#include "Random/Random.hpp"
#include "Application.hpp"
#include "Utility/Constants.hpp"
#include <Lab/NutrimentA.hpp>
#include <Lab/NutrimentB.hpp>


SimpleBacterium::SimpleBacterium(const Vec2d & position)
    : Bacterium(uniform(getConfig()["energy"]["min"].toDouble(),getConfig()["energy"]["max"].toDouble()),
                position,  Vec2d::fromRandomAngle(),
                uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()),
                getConfig()["color"]),
      t(uniform(0.,PI)), rotation(direction.angle()),
      ancien_score(getAppEnv().getPositionScore(position-direction)), TimerTumble(0)
{
    addProperty("speed",MutableNumber::positive(getAppConfig()["simple bacterium"]["speed"]));
    addProperty("tumble better",MutableNumber::positive(getAppConfig()["simple bacterium"]["tumble"]["better"]));
    addProperty("tumble worse",MutableNumber::positive(getAppConfig()["simple bacterium"]["tumble"]["worse"]));

    /* prise en compte de la nouvelle bactérie dans les statistiques */
    ++Data4Graphs[s::SIMPLE_BACTERIA];
    Data4Graphs[s::BETTER]+=getProperty("tumble better").get();
    Data4Graphs[s::WORSE]+=getProperty("tumble worse").get();
    Data4Graphs[s::SPEED]+=getProperty("speed").get();
}

j::Value& SimpleBacterium::getConfig() const
{
    return getAppConfig()["simple bacterium"];
}

// Méthodes utilitaires
void SimpleBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target); // dessin corps bactérie

    // Création de la flagelle
    auto set_of_points = sf::VertexArray(sf::LinesStrip);
    float x,y;
    for (int i(0); i<30; i++) {
        x = static_cast<float>(-i * rayon / 10.0 -rayon); //décalage du début de la flagelle,
        //pour que la sinusoïde démarre à la surface du corps de la bactérie
        y = static_cast<float>(rayon * sin(t) * sin(2 * i / 10.0));
        set_of_points.append({{x, y}, couleur.get()});  // ajout des points à l'ensemble
    }
    auto transform = sf::Transform(); // déclare une matrice de transformation
    // ici ensemble d'opérations comme des translations ou rotations faites  sur transform:
    transform.translate(position);      // Déplace la flagelle à la position de la bactérie
    transform.rotate(rotation/DEG_TO_RAD); // Rotation aligne progressivement avec la direction
    target.draw(set_of_points, transform); // dessin de l'ensemble des points
                                           // fait après leur transformation
                                           // selon la matrice transform
}


void SimpleBacterium::update(sf::Time dt)
{

    Bacterium::update(dt); //méthode commune update pour le déplacement et la consommation


    //Basculement
    TimerTumble+=dt.asSeconds();
    double lambda, score(getAppEnv().getPositionScore(position));

    // Détermination probabilité de bassculement
    if (score>=ancien_score) lambda= getProperty("tumble better").get();
    else lambda= getProperty("tumble worse").get();
    double p = 1 - exp(-TimerTumble/lambda);

    // Choisi la meilleure direction parmi N (20 dans notre fichier app.json) vecteurs aléatoires
    Vec2d tempRand;
    if(bernoulli(p)) {
        for (int i(0); i<getConfig()["tumble"]["algo"]["best of N"].toDouble(); ++i) {
            tempRand=Vec2d::fromRandomAngle();
            if(getAppEnv().getPositionScore(position+tempRand)>
               getAppEnv().getPositionScore(position+direction))
                direction=tempRand;
        }
        TimerTumble=0; // Réinitialise le timer
    }
    ancien_score=score; // Stockage pour la prochaine itération


    // Vérifie que la flagelle ne sorte pas de l'assiette
    if(getAppEnv().doesCollideWithDish(*this)) direction=-direction;

    // Rotation Flagelle
    auto const angleDiff = angleDelta(direction.angle(), rotation); // calcule la différence entre l'angle
                                                        // de la flagelle instantannément et l'angle objectif
    auto dalpha = PI * dt.asSeconds();    // rotation max admissible en un temps dt
    dalpha = std::min(dalpha, std::abs(angleDiff)); // on ne peut tourner plus que de dalpha

    dalpha = std::copysign(dalpha, angleDiff); // on tourne dans la direction indiquée par angleDiff
    rotation += dalpha; // angle de rotation mis à jour


    //Variable pour le mouvement de la flagelle
    t += 3 * dt.asSeconds();
}

Bacterium* SimpleBacterium::clone() const
{
    Bacterium* ptr=new SimpleBacterium( *this); //création d'un pointeur sur une copie
    ptr->mutate();
    getAppEnv().addBacterium(ptr, true); //ajout du clone dans le vecteur des clones

    /* prise en compte de la bactérie clonée dans les statistiques */
    ++Data4Graphs[s::SIMPLE_BACTERIA];
    Data4Graphs[s::BETTER]+=ptr->getProperty("tumble better").get();
    Data4Graphs[s::WORSE]+= ptr->getProperty("tumble worse").get();
    Data4Graphs[s::SPEED]+= ptr->getProperty("speed").get();
    return ptr;
}

// DEPLACEMENT :
void SimpleBacterium::move(sf::Time dt)
{   /*Calcul de la nouvelle position en fonction de la vitesse et de de la force.
    La vitesse est considérée constante, on ne la met pas à jour.
    L'energie de la bactérie diminue en fonction du déplacement */
    DiffEqResult Result(stepDiffEq(position, getSpeedVector(), dt,  *this));
    consumeEnergy((position-Result.position).length()*EnergieDepl());
    position=Result.position;
}

Vec2d SimpleBacterium::getSpeedVector()
{
    return direction*getProperty("speed").get();
}
Vec2d SimpleBacterium::f(Vec2d position, Vec2d speed) const
{   // La force est nulle pour les SimpleBacterium
    return Vec2d (0,0);
}



//CONSOMMATION
Quantity SimpleBacterium::eatableQuantity(NutrimentA& nutriment){
    return nutriment.eatenBy(*this);
}
Quantity SimpleBacterium::eatableQuantity(NutrimentB& nutriment) {
    return nutriment.eatenBy(*this);
}

// Destructeur : : prise en compte de la destruction de la bactérie dans les statistiques
SimpleBacterium::~SimpleBacterium(){
    --Data4Graphs[s::SIMPLE_BACTERIA];
    Data4Graphs[s::BETTER]-=getProperty("tumble better").get();
    Data4Graphs[s::WORSE]-=getProperty("tumble worse").get();
    Data4Graphs[s::SPEED]-=getProperty("speed").get();
}

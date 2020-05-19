#include "SimpleBacterium.hpp"
#include "Random/Random.hpp"
#include "Application.hpp"
#include "Utility/DiffEqSolver.hpp"
//#include "Utility/Vec2d.hpp"
//#include "SFML/Graphics.hpp"
//#include "Utility/Utility.hpp"
#include "Utility/Constants.hpp"
#include <iostream>
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
}

j::Value& SimpleBacterium::getConfig() const
{
    return getAppConfig()["simple bacterium"];
}

void SimpleBacterium::move(sf::Time dt)
{
    DiffEqResult Result(stepDiffEq(position, getSpeedVector(), dt,  *this));
    consumeEnergy((position-Result.position).length()*EnergieDepl());
    position=Result.position;
}

void SimpleBacterium::drawOn(sf::RenderTarget& target) const
{
    Bacterium::drawOn(target);

    auto set_of_points = sf::VertexArray(sf::LinesStrip);
    float x,y;
    // ajout depoints à l'ensemble:
    for (int i(0); i<30; i++) {
        x = static_cast<float>(-i * rayon / 10.0 -rayon); //décalage du début de la flagelle,
        //pour que la sinusoïde démarre à la surface du corps de la bactérie
        y = static_cast<float>(rayon * sin(t) * sin(2 * i / 10.0));
        set_of_points.append({{x, y}, couleur.get()});
    }
    auto transform = sf::Transform(); // déclare une matrice de transformation
    // ici ensemble d'opérations comme des translations ou rotations faites  sur transform:
    transform.translate(position);
    transform.rotate(rotation/DEG_TO_RAD);
    // puis:
    target.draw(set_of_points, transform); // dessin de l'ensemble des points
    // fait après leur transformation
    //selon la matrice transform
}

Vec2d SimpleBacterium::getSpeedVector(){
    return direction*getProperty("speed").get();
}

Vec2d SimpleBacterium::f(Vec2d position, Vec2d speed) const
{
    return Vec2d (0,0);
}

Bacterium* SimpleBacterium::clone() const
{
    Bacterium* ptr=new SimpleBacterium( *this);
    ptr->mutate();
    getAppEnv().addBacterium(ptr, true); // ajoute le ptr vers le vecteur temporaire de nouvelles bact
    return ptr;
}

void SimpleBacterium::update(sf::Time dt)
{

    Bacterium::update(dt); //point communs
    //Basculement
    TimerTumble+=dt.asSeconds();
    double lambda, score(getAppEnv().getPositionScore(position));
    if (score>=ancien_score) lambda= getProperty("tumble better").get();
    else lambda= getProperty("tumble worse").get();
    double p = 1 - exp(-TimerTumble/lambda);
    Vec2d tempRand;

    if(bernoulli(p)) {
        for (int i(0); i<getConfig()["tumble"]["algo"]["best of N"].toDouble(); ++i) {
            tempRand=Vec2d::fromRandomAngle();
            if(getAppEnv().getPositionScore(position+tempRand)>
               getAppEnv().getPositionScore(position+direction))
                direction=tempRand;
        }
        TimerTumble=0;
    }
    ancien_score=score;

    //Déplacement bactéries
    if(getAppEnv().doesCollideWithDish(*this)) direction=-direction;

    // Rotation Flagelle
    auto const angleDiff = angleDelta(direction.angle(), rotation); // calcule la différence entre le nouvel
    // angle de direction et l'ancien
    auto dalpha = PI * dt.asSeconds();    // calcule dα
    dalpha = std::min(dalpha, std::abs(angleDiff)); // on ne peut tourner plus que de angleDiff

    dalpha = std::copysign(dalpha, angleDiff); // on tourne dans la direction indiquée par angleDiff
    rotation += dalpha; // angle de rotation mis à jour

    //Variable pour le mouvement de la flagelle
    t += 3 * dt.asSeconds();

}

Quantity SimpleBacterium::eatableQuantity(NutrimentA& nutriment){
    return nutriment.eatenBy(*this);
}
Quantity SimpleBacterium::eatableQuantity(NutrimentB& nutriment) {
    return nutriment.eatenBy(*this);
}


void SimpleBacterium::addToGraph(const std::string & titreGraph ,std::unordered_map<std::string, double>& GraphTemp){
    if (s::GENERAL==titreGraph){
        ++GraphTemp[s::SIMPLE_BACTERIA];
    }
    if (s::SIMPLE_BACTERIA==titreGraph){
        ++GraphTemp[s::SIMPLE_BACTERIA];
    }
}


void SimpleBacterium::getSpeed(std::vector<double>& Speed){
    Speed.push_back(getProperty("speed").get());
}

void SimpleBacterium::getDataSimple(std::vector<double>& Better, std::vector<double>& Worse){
    Better.push_back(getProperty("tumble better").get());
    Worse.push_back(getProperty("tumble worse").get());
}


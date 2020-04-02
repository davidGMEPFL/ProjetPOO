#include "SimpleBacterium.hpp"
#include "Random/Random.hpp"
#include "Application.hpp"
#include "Utility/DiffEqSolver.hpp"
#include "Utility/Vec2d.hpp"
#include "SFML/Graphics.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Constants.hpp"

SimpleBacterium::SimpleBacterium(Vec2d position)
    : Bacterium( uniform(getConfig()["energy"]["min"].toDouble(),getConfig()["energy"]["max"].toDouble()),
      position ,  Vec2d::fromRandomAngle() ,
      uniform(getConfig()["radius"]["min"].toDouble(),getConfig()["radius"]["max"].toDouble()),
      getConfig()["color"]), t(uniform(0.,PI)), rotation(direction.angle())
{}

j::Value& SimpleBacterium::getConfig() const{
        return getAppConfig()["simple bacterium"];
}

void SimpleBacterium::move(sf::Time dt){
    DiffEqResult Res(stepDiffEq(position, getSpeedVector(), dt,  *this));
    consumeEnergy((position-Res.position).length()*EnergieDepl());
    position=Res.position; direction=Res.speed/5;
}


void SimpleBacterium::drawOn(sf::RenderTarget& target) const{
    auto const circle = buildCircle(position, rayon, couleur.get());
    target.draw(circle);

    if (isDebugOn()){
        auto const text = buildText(std::to_string(int(energie)),position + Vec2d(0,-50),
                                    getAppFont(),18,sf::Color::Red);
        target.draw(text);
    }

    auto set_of_points = sf::VertexArray(sf::LinesStrip);
    float x,y;
    // ajout de points à l'ensemble:
    for (int i(0); i<30;i++){
        x = static_cast<float>(-i * rayon / 10.0 -rayon);
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
    return direction*5;
}

Vec2d SimpleBacterium::f(Vec2d position, Vec2d speed) const{
    return Vec2d (0,0);
}

Bacterium* SimpleBacterium::clone() const{

}

void SimpleBacterium::update(sf::Time dt){
    move(dt);
    TimeLastMeal+=dt;
    if(getAppEnv().doesCollideWithDish(*this)) direction=-direction;
    Nutriment* NutrProxi(nullptr);
    if ((NutrProxi=getAppEnv().getNutrimentColliding(*this)) != nullptr &&
            TimeLastMeal > getTempsDelay() && !abstinence){
        TimeLastMeal=sf::Time::Zero;
        energie+=NutrProxi->takeQuantity(mealMax());
    }
    t+=2*   dt.asSeconds();


    auto const angleDiff = angleDelta(direction.angle(), rotation); // calcule la différence entre le nouvel
                                                                    // angle de direction et l'ancien
    auto dalpha = PI * dt.asSeconds();    // calcule dα
    dalpha = std::min(dalpha, std::abs(angleDiff)); // on ne peut tourner plus que de angleDiff

    dalpha = std::copysign(dalpha, angleDiff); // on tourne dans la direction indiquée par angleDiff
    rotation += dalpha; // angle de rotation mis à jour
}

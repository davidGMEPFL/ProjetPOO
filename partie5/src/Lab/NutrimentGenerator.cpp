#include "NutrimentGenerator.hpp"
#include "Random/Random.hpp"
#include "Config.hpp"
#include "Utility/Types.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Lab.hpp"
#include "Application.hpp"
#include "Utility/Vec2d.hpp"


NutrimentGenerator::NutrimentGenerator():
    TimeLastGen(sf::Time::Zero) {}


void NutrimentGenerator::update(sf::Time dt)
{/* En fonction du temps écoulé, la méthode génère un nutriment en remettant à zéro le chrono.
    Selon le test de bernouilli, elle génèrera une source de NutrimentA ou de NutrimentB,
    de position donnée par une loi normale, et de quantité aléatoire */
    TimeLastGen+=dt;
    Nutriment* pointNut;

    if(TimeLastGen > sf::seconds(getShortConfig().generator_nutriment_delay)) { //si délai temps passé
        TimeLastGen=sf::Time::Zero;
        Vec2d tailleEnv(getApp().getLabSize()); //donne dimensions du lab
        double posX(normal(tailleEnv.x/2, tailleEnv.x*tailleEnv.x/16));
        double posY(normal(tailleEnv.y/2, tailleEnv.y*tailleEnv.y/16));
        Vec2d pos(posX,posY); //coordonnées aléatoire de la source, selon loi normale

        //Test de bernouilli qui dira si l'on retourne un NutA ou un NutB
        if(bernoulli(getShortConfig().generator_nutriment_prob )) {
            Quantity qt(uniform(getShortConfig().nutrimentA_min_qty,getShortConfig().nutrimentA_max_qty));
            pointNut=new NutrimentA(qt,pos);
            getAppEnv().addNutriment(pointNut);
            //ajout du nutriment A dans le Lab, ayant la position et une quantité aléatoirment choisies
        } else {
            Quantity qt(uniform(getShortConfig().nutrimentB_min_qty,getShortConfig().nutrimentB_max_qty));
            pointNut=new NutrimentB(qt,pos);
            getAppEnv().addNutriment(pointNut);
        }
    }
}


void NutrimentGenerator::reset() //remise du chrono à zéro
{
    TimeLastGen=sf::Time::Zero;
}

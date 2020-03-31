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
    TimeLastGen(sf::Time::Zero){}

void NutrimentGenerator::update(sf::Time dt){
    TimeLastGen+=dt;
    if(TimeLastGen > sf::seconds(getShortConfig().generator_nutriment_delay)){
        TimeLastGen=sf::Time::Zero;
        Vec2d tailleEnv(getApp().getLabSize());
        double posX(normal(tailleEnv.x/2, tailleEnv.x*tailleEnv.x/16));
        double posY(normal(tailleEnv.y/2, tailleEnv.y*tailleEnv.y/16));
//        Vec2d pos(normal(tailleEnv/2, tailleEnv*tailleEnv/16));
        Vec2d pos(posX,posY);
        if(bernoulli(getShortConfig().generator_nutriment_prob )){
            Quantity qt(uniform(getShortConfig().nutrimentA_min_qty,getShortConfig().nutrimentA_max_qty));
            NutrimentA nut(qt,pos);
            getAppEnv().addNutriment(&nut);
        }
        else {
            Quantity qt(uniform(getShortConfig().nutrimentB_min_qty,getShortConfig().nutrimentB_max_qty));
            NutrimentB nut(qt,pos);
            getAppEnv().addNutriment(&nut);
        }

    }
}

void NutrimentGenerator::reset(){
    TimeLastGen=sf::Time::Zero;
}

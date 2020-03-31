#include "NutrimentGenerator.hpp"
#include "Random/Random.hpp"
#include "Config.hpp"
#include "Utility/Types.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Lab.hpp"


NutrimentGenerator::NutrimentGenerator():
    TimeLastGen(sf::Time::Zero){}

Nutriment NutrimentGenerator::update(sf::Time dt){
    TimeLastGen+=dt;
    if(TimeLastGen > sf::seconds(getShortConfig().generator_nutriment_delay)){
        TimeLastGen=0;
        vec2d tailleEnv(getAppEnv().getLabSize());
        double posX(normal(tailleEnv.x/2, tailleEnv.x*tailleEnv.x/16));
        double posY(normal(tailleEnv.y/2, tailleEnv.y*tailleEnv.y/16));
        Vec2d pos(posX,posY);
        if(bernoulli(getShortConfig().generator_nutriment_prob )){
            Quantity qt(uniform(getShortConfig().nutrimentA_min_qty,getShortConfig().nutrimentA_max_qty));
            NutrimentA nut(qt,pos);
        }
        else {
            Quantity qt(uniform(getShortConfig().nutrimentB_min_qty,getShortConfig().nutrimentB_max_qty));
            NutrimentB nut(qt,pos);
        }
        return &nut;
    }
}

void NutrimentGenerator::reset(){
    TimeLastGen=0;
}

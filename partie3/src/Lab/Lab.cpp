#include "Lab.hpp"
#include "Application.hpp"

Lab::Lab():
    Petri(getApp().getCentre(),0.5*.95*getApp().getLabSize().x)
{}

void Lab::drawOn(sf::RenderTarget& targetWindow) const{
    Petri.drawOn(targetWindow);
}

void Lab::update(sf::Time dt){
    Generator.update(dt);
    Petri.update(dt);
}
void Lab::reset(){
    Petri.reset();
    Generator.reset();
}

bool Lab::contains(const CircularBody& autre){
    return Petri.contains(autre);
}
bool Lab::addNutriment(Nutriment* nut){
    return Petri.addNutriment(nut);
}




double Lab::getTemperature(){
    return Petri.getTemperature();
}
void Lab::increaseTemperature(){
    Petri.increaseTemperature();
}
void Lab::decreaseTemperature(){
    Petri.decreaseTemperature();
}
void Lab::resetTemp(){
    Petri.resetTemp();
}

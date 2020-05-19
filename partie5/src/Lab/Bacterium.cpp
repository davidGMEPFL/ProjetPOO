#include "Bacterium.hpp"
#include "Application.hpp"

using namespace std;

Bacterium::Bacterium(Quantity energie, Vec2d position, Vec2d direction, double rayon, MutableColor couleur)
    : CircularBody(position,rayon), couleur(couleur), direction(direction),abstinence(false),
      energie(energie), TimeLastMeal(sf::Time::Zero)
{}

void Bacterium::drawOn(sf::RenderTarget& target) const
{
    auto const circle = buildCircle(position, rayon, couleur.get());
    target.draw(circle); //dessin du disque de la bactérie

    if (isDebugOn()) {
        auto const text = buildText(std::to_string(int(energie)),position + Vec2d(0,-100),
                                    getAppFont(),18,sf::Color::Red);
        target.draw(text);
    } //ajout de la quantité d'énergie
}


void Bacterium::update(sf::Time dt)
{
    //Déplacement spécifique à chaque type de bactérie
    move(dt);

    // Bacterie mange des nutriments
    TimeLastMeal+=dt;
    Nutriment* NutrProxi(nullptr);

    if ((NutrProxi=getAppEnv().getNutrimentColliding(*this)) != nullptr &&
            TimeLastMeal > getTempsDelay() && !abstinence) { //si y a bien un nutriment en contact + pas en abstinence + délai de temps passé
        TimeLastMeal=sf::Time::Zero;
        eat(*NutrProxi);

        // Division bactérie
        division();
    }
}


void Bacterium::eat(Nutriment& nutriment) { //on ne peut pas être polymorphique directement sur le paramètre
    Quantity eaten(nutriment.eatenBy(*this)); //on s'arrange pour l'être en invoquant une méthode  polymorphique dessus
    energie+=eaten;
}

void Bacterium::consumeEnergy(Quantity qt)
{
    energie-=qt;
}

bool Bacterium::testMort()
{
    return energie<=0;
}

void Bacterium::division()
{
    if(energie>getMinEnDiv()) {
        energie/=2;
        clone();
        direction*=(-1); //dans sens opposé
    }
}

void Bacterium::mutate()
{
    couleur.mutate();
    std::map<std::string, MutableNumber>::iterator it = Params.begin();//itérateur sur premier paramètre mutable
    while (it != Params.end()) { //tant que dépasse pas le dernier élément
        it->second.mutate();     //contenu mutable pointé mute
        it++;
    }
}

//Getters utilitaires
double Bacterium::getMinEnDiv() const
{
    return getConfig()["energy"]["division"].toDouble();
}
sf::Time Bacterium::getTempsDelay() const
{
    return sf::seconds(getConfig()["meal"]["delay"].toDouble());
}
double Bacterium::EnergieDepl() const
{
    return getConfig()["energy"]["consumption factor"].toDouble();
}
double Bacterium::mealMax() const
{
    return getConfig()["meal"]["max"].toDouble();
}

// PARAMETRES MUTABLES :
void Bacterium::addProperty(const string& key, MutableNumber valeur)
{
    Params[key]=valeur; //dans la map Params, initialise la valeur Mutable Number à sa clé correspondante
}

MutableNumber& Bacterium::getProperty(const string& key) //associe la valeur liée à la clé
{
    auto it = Params.find(key);
    if (it != Params.end()) {
        return it->second; //retourne le contenu pointé par l'étiquette
    } else {
        throw std::out_of_range("unknown mutable property :" + key);
        //programme s'arrête si ne trouve aucune propriété correspondant à la clé
    }
}


// GRAPHS
void Bacterium::getDataTwitching(vector<double>&, vector<double>&){
}

void Bacterium::getDataSimple(vector<double>&, vector<double>&){
}

Bacterium::~Bacterium() {}

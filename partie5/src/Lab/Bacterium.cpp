#include "Bacterium.hpp"
#include "Application.hpp"

using namespace std;

Bacterium::Bacterium(Quantity energie, Vec2d position, Vec2d direction, double rayon, MutableColor couleur)
    : CircularBody(position,rayon), couleur(couleur), direction(direction),abstinence(false),
      energie(energie), TimeLastMeal(sf::Time::Zero)
{}

// Paramètres mutables
void Bacterium::addProperty(const string& key, MutableNumber valeur)
{   /*Dans la map Params, initialise la valeur Mutable Number à sa clé correspondante */

    Params[key]=valeur;
}

MutableNumber& Bacterium::getProperty(const string& key)
{ /* Associe la valeur liée à la clé */

    auto it = Params.find(key); //initialise l'itérateur à l'étiquette recherchée
    if (it != Params.end()) {
        return it->second; //retourne la valeur pointée
    } else {
        throw std::out_of_range("unknown mutable property :" + key);
        //programme s'arrête si ne trouve aucune propriété correspondant à la clé
    }
}

// Méthodes utilitaires
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
{/* Fait évoluer la vie d'une bactérie à chaque pas de temps.
    Elle lui permet de se mouvoir, de manger si possible, et de se diviser */

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

void Bacterium::mutate()
{ /* Permet de faire muter la couleur et les paramètres mutables de la bactérie */
    couleur.mutate();
    std::map<std::string, MutableNumber>::iterator it = Params.begin(); //itérateur sur premier paramètre mutable
    while (it != Params.end()) {  //tant que dépasse pas le dernier élément
        it->second.mutate();     //contenu mutable pointé mute
        it++;
    }
}

// Consommation nutriments
void Bacterium::eat(Nutriment& nutriment) {   //on ne peut pas être polymorphique directement sur le paramètre
    Quantity eaten(nutriment.eatenBy(*this)); //on s'arrange pour l'être en invoquant une méthode  polymorphique dessus
    energie+=eaten;
}

// Actions en fonction énergie
void Bacterium::consumeEnergy(Quantity qt)
{
    energie-=qt; //soustrait la quantité souhaitée
}
bool Bacterium::testMort() const
{ /* Test si énergie suffisante pour survie de la bactérie */
    return energie<=0;
}
void Bacterium::division()
{/* Si l'énergie de la bactérie dépasse un seuil, celle-ci se réduit de moitié,
    et la bactérie engendre un clône de même énérgie mais de direction opposée */

    if(energie>getMinEnDiv()) {
        energie/=2;
        clone();
        direction*=(-1); //sens opposé
    }
}


// GETTERS utilitaires
/* Retournent les valeurs associées aux étiquettes dans app.jason */
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


// GRAPHS
/*
void Bacterium::getDataTwitching(vector<double>&, vector<double>&) {
}
void Bacterium::getDataSimple(vector<double>&, vector<double>&){
}*/


std::unordered_map<std::string, double> Bacterium::Data4Graphs={ {s::SIMPLE_BACTERIA , 0},
                                                                {s::TWITCHING_BACTERIA , 0},
                                                                {s::SWARM_BACTERIA , 0},
                                                                {s::NUTRIMENT_SOURCES , 0},
                                                                {s::BETTER, 0},
                                                                {s::WORSE, 0},
                                                                {s::TENTACLE_LENGTH, 0},
                                                                {s::TENTACLE_SPEED, 0},
                                                                {s::SPEED, 0}};

//std::unordered_map<std::string, double> Bacterium::Data4Graphs[s::TWITCHING_BACTERIA]=0;
//std::unordered_map<std::string, double> Bacterium::Data4Graphs[s::SWARM_BACTERIA]=0;
//std::unordered_map<std::string, double> Bacterium::Data4Graphs[s::NUTRIMENT_SOURCES]=0;
//std::unordered_map<std::string, double> Bacterium::Data4Graphs[s::NUTRIMENT_QUANTITY]=0;
//std::unordered_map<std::string, double> Bacterium::Data4Graphs[s::DISH_TEMPERATURE]=0;
//std::unordered_map<std::string, double> Bacterium::Data4Graphs[s::BETTER]=0;
//std::unordered_map<std::string, double> Bacterium::Data4Graphs[s::WORSE]=0;
//std::unordered_map<std::string, double> Bacterium::Data4Graphs[s::TENTACLE_LENGTH]=0;
//std::unordered_map<std::string, double> Bacterium::Data4Graphs[s::TENTACLE_SPEEDt]=0;
//std::unordered_map<std::string, double> Bacterium::Data4Graphs[s::SPEED]=0;





// Destructeur virtuel
Bacterium::~Bacterium() {}

#include "MutableNumber.hpp"
#include "Random/Random.hpp"

MutableNumber::MutableNumber(const double& valeur_, const double& proba_,
                             const double& sigma,
                             const bool&  if_borne_inf_, const double& borneinf,
                             const bool& if_borne_sup_,const double& bornesup)
    : proba_mutation(proba_),
      if_borne_inf(if_borne_inf_), if_borne_sup(if_borne_sup_),
      borne_inf(borneinf), borne_sup(bornesup),
      ecart_type(sigma)
{
    set(valeur_) ; // utilisé pour forcer la valeur à respecter les bornes
}

MutableNumber::MutableNumber(j::Value const& config)
    : proba_mutation(config["rate"].toDouble()),
      if_borne_inf(config["clamp min"].toBool()), if_borne_sup(config["clamp max"].toBool()),
      borne_inf(config["min"].toDouble()), borne_sup(config["max"].toDouble()),
      ecart_type(config["sigma"].toDouble())
{
    set(config["initial"].toDouble()); // utilisé pour forcer la valeur à respecter les bornes
}

double MutableNumber::get() const
{
    return valeur;
}

void MutableNumber::set(double value)
{
    //Plafonnement de la nouvelle valeur
    if(if_borne_inf && value < borne_inf)
        value=borne_inf;
    else if(if_borne_sup && value > borne_sup)
        value=borne_sup;

    valeur=value; // mise à jour de l'attribut
}

void MutableNumber::mutate()
{
    if(bernoulli(proba_mutation))
        set(valeur+normal(0, ecart_type*ecart_type));
}

MutableNumber MutableNumber::probability(double initialValue,
        double mutationProbability, double sigma)
{   // Toujours entre 0 et 1
    return MutableNumber (initialValue, mutationProbability, sigma, true, 0., true, 1.);
}

MutableNumber MutableNumber::probability(j::Value const& config)
{   // Toujours entre 0 et 1
    return MutableNumber (config["initial"].toDouble(), config["rate"].toDouble(),
                          config["sigma"].toDouble(), true, 0., true, 1.);

}

MutableNumber MutableNumber::positive(double initialValue,
                                      double mutationProbability, double sigma,
                                      bool hasMax, double max)
{   // Toujours >=0, peut avoir une borne supérieure (max)
    return MutableNumber (initialValue, mutationProbability, sigma, true, 0., hasMax, max);
}


MutableNumber MutableNumber::positive(j::Value const& config, bool hasMax, double max)
{   // Toujours >=0, peut avoir une borne supérieure (max)
    return MutableNumber (config["initial"].toDouble(), config["rate"].toDouble(),
                          config["sigma"].toDouble(), true, 0, hasMax, max);
}

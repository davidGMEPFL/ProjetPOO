#include "MutableNumber.hpp"
#include "Random/Random.hpp"

MutableNumber::MutableNumber(const double& valeur_, const double& proba_,
                             const double& sigma,
                             const double& borneinf=0.0, const double& bornesup=0.0,
                             const bool&  if_borne_inf_=false,const bool& if_borne_sup_=false)
    : proba_mutation(proba_),
      if_borne_inf(if_borne_inf_), if_borne_sup(if_borne_sup_),
      borne_inf(borneinf), borne_sup(bornesup),
      ecart_type(sigma)
{    set(valeur_);}

MutableNumber::MutableNumber(j::Value const& config)
    : proba_mutation(config["rate"].toDouble()),
      if_borne_inf(config["clamp min"].toDouble()), if_borne_sup(config["clamp max"].toDouble()),
      borne_inf(config["min"].toDouble()), borne_sup(config["max"].toDouble()),
      ecart_type(config["sigma"].toDouble())
{
    set(config["initial"].toDouble());
}

double MutableNumber::get() const {
    return valeur;
}

void MutableNumber::set(double value) {
    if(if_borne_inf && value < borne_inf) {
        value=borne_inf;
    }
    else if(if_borne_sup && value > borne_sup) {
        value=borne_sup;
    }
    valeur=value;
}

void MutableNumber::mutate() {
    bernoulli(proba_mutation);
    if(bernoulli(proba_mutation)){
        const double& nb_tire =  normal(0, ecart_type*ecart_type);
        set(valeur+nb_tire);
    }

}

MutableNumber MutableNumber::probability(double initialValue,
                                         double mutationProbability, double sigma){
    return MutableNumber (initialValue, mutationProbability, sigma, 0., 1. ,true, true);

}

MutableNumber MutableNumber::probability(j::Value const& config){
    return MutableNumber (config["initial"].toDouble(), config["rate"].toDouble(),
            config["sigma"].toDouble(), 0, 1 ,true, true);

}

MutableNumber MutableNumber::positive(double initialValue,
                                      double mutationProbability, double sigma,
                                      bool hasMax=false, double max=0.){
    return MutableNumber (initialValue, mutationProbability, sigma, max, 0. ,true, hasMax);
}


MutableNumber MutableNumber::positive(j::Value const& config, bool hasMax=false, double max=0.){
    return MutableNumber (config["initial"].toDouble(), config["rate"].toDouble(),
            config["sigma"].toDouble(), max, 0. ,true, hasMax);
}

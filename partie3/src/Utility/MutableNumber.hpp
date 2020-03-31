#pragma once
#include "Utility.hpp"

class MutableNumber
{
private :
    double valeur;
    double proba_mutation;
    bool if_borne_inf;
    bool if_borne_sup;
    double borne_inf;
    double borne_sup;
    double ecart_type;

public:
    MutableNumber(const double&, const double&, const double&, const double&,
                  const double&,  const bool&, const bool&);

    MutableNumber(j::Value const&);

    double get() const ;
    void set(double value) ;

    void mutate();

    static MutableNumber probability(double initialValue, double mutationProbability, double sigma);
    static MutableNumber probability(j::Value const& config);
    static MutableNumber positive(double initialValue, double mutationProbability, double sigma, bool hasMax, double max);
    static MutableNumber positive(j::Value const& config, bool hasMax, double max);


};

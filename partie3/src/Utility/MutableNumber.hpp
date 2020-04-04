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
    MutableNumber(const double& valeur_, const double& proba_, const double& sigma,
                                 const bool&  if_borne_inf_=false, const double& borneinf=0.0,
                                 const bool& if_borne_sup_=false,const double& bornesup=0.0);

    MutableNumber(j::Value const&);
    MutableNumber()=default;

    double get() const ;
    void set(double value) ;

    void mutate();

    static MutableNumber probability(double initialValue, double mutationProbability, double sigma);
    static MutableNumber probability(j::Value const& config);
    static MutableNumber positive(double initialValue, double mutationProbability, double sigma, bool hasMax=false, double max=0.);
    static MutableNumber positive(j::Value const& config, bool hasMax=false, double max=0.);


};

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
    //Constructeurs
    MutableNumber(const double& valeur_, const double& proba_, const double& sigma,
                  const bool&  if_borne_inf_=false, const double& borneinf=0.0,
                  const bool& if_borne_sup_=false,const double& bornesup=0.0);
    // Argument optionnel

    MutableNumber(j::Value const&); // Contructeur à partir des paramètres du fichier app.json
    MutableNumber()=default; //Constructeurs par défaut, utile pourr Bacterium::getProperty

    double get() const ; // Retourne la valeur du MutableNumber
    void set(double value); // Permet de donner une valeur en respecant les bornes

    void mutate();


    //Methodes pour simplifier la génération de nombres mutables de différentes natures
    static MutableNumber probability(double initialValue, double mutationProbability, double sigma);
    static MutableNumber probability(j::Value const& config);
    static MutableNumber positive(double initialValue, double mutationProbability, double sigma, bool hasMax=false, double max=0.);
    static MutableNumber positive(j::Value const& config, bool hasMax=false, double max=0.);
};

#pragma once
#include <memory>
#include <map>
#include "Graph.hpp"
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"

class Stats : public Drawable, public Updatable
{

    std::map<int, std::pair<std::string, std::unique_ptr<Graph>>> Graphs; // map qui associe à tout indice une pair titre-graph
    std::map<int, std::pair<std::string, std::unique_ptr<Graph>>>::iterator activeID; // itérateur sur la map
    sf::Time TimeLastUpdate;


public:
    Stats(); //constructeur

// Méthodes utiles
    void update(sf::Time) override;
    void drawOn(sf::RenderTarget& TargetWindow) const override;

// Méthodes d'accès et d'indexation
    void setActiveId(const int&);
    std::string getCurrentTitle() const;
    void next();
    void previous();

// Ajout des séries
    void addGraph(int, std::string const&, std::vector<std::string>, double, double, const Vec2d &);

    void reset(); //remise à zéro des valeurs des graphes
};


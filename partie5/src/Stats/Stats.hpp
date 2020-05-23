#pragma once
#include <memory>
#include <map>
#include "Graph.hpp"

class Stats 
{
//    std::vector<std::unique_ptr<Graph>> Graphs;
//    std::vector<std::string> Libelles;
//    int index;

    std::map<int, std::pair<std::string, std::unique_ptr<Graph>>> Graphs;
    std::map<int, std::pair<std::string, std::unique_ptr<Graph>>>::iterator activeID;
//    std::map<std::string, std::unique_ptr<Graph>> Graphs;
//    std::map<std::string, std::unique_ptr<Graph>>::iterator activeID
    sf::Time TimeLastUpdate;


public:
    Stats(); //constructeur

// Méthodes utiles
    void update(sf::Time);
    void drawOn(sf::RenderTarget& TargetWindow);

// Méthodes d'accès et d'indexation
    void setActiveId(const int&);
    std::string getCurrentTitle();
    void next();
    void previous();

// Ajout des séries
    void addGraph(int, std::string const&, std::vector<std::string>, double, double, const Vec2d &);
//    mCurrentGraphId, title, series, min, max, getStatsSize()

    void reset(); //remise à zéro des valeurs des graphes
};


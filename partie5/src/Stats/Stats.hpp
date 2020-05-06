#pragma once
#include <memory>
#include <vector>
#include "Graph.hpp"

class Stats 
{
    std::vector<std::unique_ptr<Graph>> Graphs;
    std::vector<std::string> Libelles;
//    int index;
    int activeID;
//    std::map<std::string, std::unique_ptr<Graph>> Graphs;
//    std::map<std::string, std::unique_ptr<Graph>>::iterator activeID;


public:
    void setActiveId(const int&);
    std::string getCurrentTitle();
    void next();
    void previous();

    void reset();

    void update(sf::Time);

    void addGraph(int, std::string const&, std::vector<std::string>, double, double, const Vec2d &);
//    mCurrentGraphId, title, series, min, max, getStatsSize()

    void drawOn(sf::RenderTarget& TargetWindow);
};


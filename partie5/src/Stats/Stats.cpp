#include <Stats/Stats.hpp>

using namespace std;
// CLASSE A CODER

void Stats::setActive(const int& id){
    activeID=id;
}


std::string Stats::getCurrentTitle(){
    if(!Libelles.empty())
        return Libelles[activeID];
    else return "";
}

void Stats::next(){
    ++activeID;
}

void Stats::previous(){
    --activeID;
}

void Stats::reset(){
    for (auto& telGraph: Graphs) {
    telGraph.reset();
    }
}

void Stats::update(sf::Time dt){

}

void Stats::drawOn(sf::RenderTarget& TargetWindow){

}


void Stats::addGraph(int idGraph, std::string const& titreGraph,
                     std::vector<std::string> sesLibelles, double min, double max, Vec2d const& size){
//    if (Graphs[idGraph])
//    Graphs[idGraph].reset();
//    Graphs[idGraph]=unique_ptr<Graph>(new Graph(sesLibelles, size,  min,  max));
//    Libelles[idGraph]=titreGraph;
//    activeID=idGraph;
}

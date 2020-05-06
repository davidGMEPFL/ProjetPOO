#include <Stats/Stats.hpp>

using namespace std;
// CLASSE A CODER

void Stats::setActiveId(const int& id){
    activeID=id;
}


std::string Stats::getCurrentTitle(){
    if(!Libelles.empty())
        return Libelles[activeID];

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
//    if (Graphs.size()>idGraph)    Graphs[idGraph].reset();
//    iterator iter(iterator Graphs.begin() + idGraph);
//    Graphs.insert( iter, unique_ptr<Graph>(new Graph(sesLibelles, size,  min,  max)));
//    Libelles[idGraph]=titreGraph;
//    activeID=idGraph;
}

#include <Stats/Stats.hpp>

using namespace std;
// CLASSE A CODER


Stats::Stats():
    iter(Graphs.begin())
{}


void Stats::setActiveId(const int& id){
    iter= Graphs.find(id);
}


std::string Stats::getCurrentTitle(){
//        return activeID.second;
    return iter->second.first;
}

void Stats::next(){
    ++iter;
    if (Graphs.end() == iter) iter=Graphs.begin();
}

void Stats::previous(){
    if (Graphs.begin() == iter)  iter = Graphs.end();
    --activeID;
}

void Stats::reset(){
    for (auto& telGraph: Graphs) {
        telGraph.second.second.reset();
    }
}

void Stats::update(sf::Time dt){

}

void Stats::drawOn(sf::RenderTarget& TargetWindow){
    iter->second.second->drawOn(TargetWindow);
}


void Stats::addGraph(int idGraph, std::string const& titreGraph,
                     std::vector<std::string> sesLibelles, double min, double max, Vec2d const& size){
    Graphs[idGraph].second.reset();
//    if (Graphs.size()>idGraph)    Graphs[idGraph].reset();
//    iterator iter(iterator Graphs.begin() + idGraph);
    Graphs[idGraph]=std::pair<std::string, std::unique_ptr<Graph>> (titreGraph, unique_ptr<Graph>(new Graph(sesLibelles, size,  min,  max)));
//    Libelles[idGraph]=titreGraph;
//    activeID=idGraph;
    iter=Graphs.find(idGraph);
}

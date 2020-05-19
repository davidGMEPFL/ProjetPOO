#include <Stats/Stats.hpp>
#include <Application.hpp>

using namespace std;


Stats::Stats():
    activeID(Graphs.begin())
{}


void Stats::setActiveId(const int& id){
    activeID= Graphs.find(id);
}


std::string Stats::getCurrentTitle(){
//        return activeID.second;
    return activeID->second.first;
}

void Stats::next(){
    ++activeID;
    if (Graphs.end() == activeID) activeID=Graphs.begin();
}

void Stats::previous(){
    if (Graphs.begin() == activeID)  activeID = Graphs.end();
    --activeID;
}

void Stats::reset(){
  //  TimeLastUpdate+=sf::Time::Zero;
    for (auto& telGraph: Graphs) {
        if(&telGraph != nullptr){
            unique_ptr<Graph> ceGraph (new Graph(*telGraph.second.second));
            ceGraph->reset();
           // ceGraph->updateData(TimeLastUpdate, getAppEnv().fetchData(telGraph.second.first));
        }
 }  //la suppression des graphes nécessite de redonner des valeurs, pour empêcher un SegFault dans le drawOn
}

void Stats::update(sf::Time dt){
    TimeLastUpdate+=dt;
    if(TimeLastUpdate > sf::seconds(getAppConfig()["stats"]["refresh rate"].toDouble())) {
        for (auto& unGraph : Graphs)
            unGraph.second.second->updateData(TimeLastUpdate, getAppEnv().fetchData(unGraph.second.first));
        TimeLastUpdate=sf::Time::Zero;
    }
}

void Stats::drawOn(sf::RenderTarget& TargetWindow){
    activeID->second.second->drawOn(TargetWindow);
}


void Stats::addGraph(int idGraph, std::string const& titreGraph,
                     std::vector<std::string> sesLibelles, double min, double max, Vec2d const& size){
    Graphs[idGraph].second.reset();
    Graphs[idGraph]=std::pair<std::string, std::unique_ptr<Graph>> (titreGraph, unique_ptr<Graph>(new Graph(sesLibelles, size,  min,  max)));
    activeID=Graphs.find(idGraph);
}

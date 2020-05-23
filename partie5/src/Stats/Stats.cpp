#include <Stats/Stats.hpp>
#include <Application.hpp>

using namespace std;


Stats::Stats():
    activeID(Graphs.begin())
{}

// Méthodes utiles :
void Stats::update(sf::Time dt)
{
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


// ACCES ET INDEXATION :
void Stats::setActiveId(const int& id)
{/* Met à jour l'identificateur actif */
    activeID= Graphs.find(id);
}
std::string Stats::getCurrentTitle()
{/* Retourne le titre associé à l'id actif */
    return activeID->second.first; //return activeID.second;
}
void Stats::next()
{/* */
    ++activeID;
    if (Graphs.end() == activeID) activeID=Graphs.begin();
}
void Stats::previous()
{/* */
    if (Graphs.begin() == activeID)  activeID = Graphs.end();
    --activeID;
}


// AJOUT des séries :
void Stats::addGraph(int idGraph, std::string const& titreGraph,
                     std::vector<std::string> sesLibelles, double min, double max, Vec2d const& size){
    Graphs[idGraph].second.reset();
    Graphs[idGraph]=std::pair<std::string, std::unique_ptr<Graph>> (titreGraph, unique_ptr<Graph>(new Graph(sesLibelles, size,  min,  max)));
    activeID=Graphs.find(idGraph);
}

void Stats::reset()
{/* Itère sur chaque courbe pour supprimer les valeurs */
    for (auto& telGraph: Graphs) {
        telGraph.second.second->reset();
    }
}


#include "Stats.hpp"
using namespace std;

Stats::Stats ()
: ensembleGraphes (), libelles (), identifiantActif(-1) //initialiser le constructeur
{}

void Stats::update(const sf::Time& dt)
{
	compteur += dt;

	/*if (compteur >= getAppConfig().stats_refresh_rate)

	{

		compteur = sf::Time;
	}*/
}


void Stats::setActive (double new_identifiant_actif)
{
    identifiantActif = new_identifiant_actif;
}


void Stats::focusOn(std::string title)
{
   for (auto& nom : libelles)
    {
		if (nom.second == title)
		{
			setActive (nom.first);
			ensembleGraphes.at (identifiantActif) -> reset();
		}
	}
}

void Stats::draw(sf::RenderTarget& targetWindow)
{
	ensembleGraphes.at(identifiantActif)->draw (targetWindow);    
}

void Stats::addGraph(double identifiantGraphe, std::string const& title, std::vector<std::string> const& series,
double min, double max, Vec2d size)
{
	//std::unique_ptr <Graph> graph (new Graph(series, size, min, max));
	///restter le graphe et le libelle
	
	//ensembleGraphes.at(identifiantGraphe)->Graph::reset();
	ensembleGraphes.insert (std::make_pair(identifiantGraphe, std::unique_ptr <Graph> (new Graph(series, size, min, max))));
	
	//ensembleGraphes.at(identifiantGraphe)->reset (graph);
    
    libelles.insert (std::make_pair(identifiantGraphe, title));
    setActive(identifiantGraphe);
    
}

void Stats::reset()
{
	for (auto& graphe : ensembleGraphes)
	{
		graphe.second->Graph::reset();
	}
}

Stats::~Stats ()
{}

#ifndef STATS_HPP
#define STATS_HPP

#include <Interface/Updatable.hpp>
#include <string>
#include <vector>
#include "Graph.hpp"
#include <unordered_map>
#include <memory>

class Graph;
class Stats : public Updatable , public Drawable

{
	public : 
	
	Stats ();
	
	virtual ~Stats ();
	
	void update(const sf::Time& dt) override;
	
	void reset();
	
	void setActive(double new_identifiant_actif) ; //methode permettant de mnettre a jour l'identifiant actif
	
	void focusOn (std::string title); //basculer d'un graphe à l'autre
	
	void draw(sf::RenderTarget& targetWindow)  override; // dessiner les stats
	
	void addGraph(double identifiant_actif, std::string const& title, 
	std::vector<std::string> const& series, double min, double max, Vec2d size);

	
	
	protected :
	
	
	
	private : 
	
	std::unordered_map <double,std::unique_ptr<Graph>> ensembleGraphes; //tableau de graphes
	
	std::unordered_map <double, std::string> libelles;
	
	int identifiantActif; //graphe visible
	
	sf::Time compteur;
	
};

#endif

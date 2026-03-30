#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <Environment/Environment.hpp>
#include "Animal/Animal.hpp"
#include "Environment/OrganicEntity.hpp"
#include <vector>
#include <Application.hpp>
#include <algorithm>

using namespace std;

void Environment::draw(sf::RenderTarget& targetWindow)  //dessine les entités organiques
{

    for (auto (*entites) : ensembleEntites) {
            (*entites).draw(targetWindow);
            //utilise la methode virtuelle pure de organic entity qui utilise de facon polymorphique les methodes opportunes selon le type de organic entity
    } 
    
    for (auto (*ondes) : waves) {
		if (ondes -> Wave::getIntensite () > getAppConfig().wave_intensity_threshold) {
			(*ondes).draw(targetWindow);
		}
	}
	
	for (auto (*obstacle) : ensembleObstacles) {
		(*obstacle).draw(targetWindow);
	}

}
void Environment::addEntity (OrganicEntity* entity)  // méthode permettant d'ajouter une entité organique à l'environnement
{
    ensembleEntites.push_back(entity);
}
// nettoyage de l'environnememt
void Environment::clean ()
{
    for (auto& entity : ensembleEntites) {
		delete entity;
        entity = nullptr;
    }
    
    ensembleEntites.erase(std::remove(ensembleEntites.begin(), ensembleEntites.end(), nullptr), ensembleEntites.end());
	ensembleEntites.clear();

	for (auto& ondes : waves) {
		delete ondes;
		ondes = nullptr;
	}

    waves.erase(std::remove(waves.begin(), waves.end(), nullptr), waves.end());
	waves.clear();

    for (auto& obst : ensembleObstacles) {
		delete obst;
		obst = nullptr;
	}
	
    ensembleObstacles.erase(std::remove(ensembleObstacles.begin(), ensembleObstacles.end(), nullptr), ensembleObstacles.end());
	ensembleObstacles.clear();
}

//mettre a jour les animaux de la flore
void Environment::update(const sf::Time& dt)
{
    for (auto& (entite) : ensembleEntites) {
        (*entite).update(dt);
        if (entite->isDead())
        {
			delete entite;
			entite = nullptr;
		}
	}
		ensembleEntites.erase(std::remove(ensembleEntites.begin(), ensembleEntites.end(), nullptr), ensembleEntites.end());
		
        //utilise la methode virtuelle pure de organic entity qui utilise de facon polymorphique les methodes opportunes selon le type de organic entity
    

    for (auto& (generateur) : ensembleGenerateurs) {
        (*generateur).update(dt) ;
    }

	for (auto& (ondes) : waves) {{
		(*ondes).update (dt);
	}
	
	
	for (auto& (cailloux) : ensembleObstacles) {
		ondes->Wave::collision (cailloux);
	}
}
}
// destructeur d'environment
Environment::~Environment ()
{
        clean();
}

vector <OrganicEntity*> Environment::getEntitiesInSightForAnimal (Animal const* animal) const
{
    vector <OrganicEntity*> liste (0) ;
    for (auto entite : ensembleEntites) {
		if (entite != nullptr) {
        if ((*animal).isTargetInSight (entite->getPosition()) and (animal != entite)) {
            liste.push_back (entite);
        }
    }}
    return liste;
}

// methode qui ajoute un generateur a la liste de generatuers
void Environment::addGenerator (FoodGenerator* generateur)
{
    ensembleGenerateurs.push_back(generateur);
}

void Environment::addWave (Wave* wave) 
{
	waves.push_back (wave);
}

void Environment::addObstacle (CircularCollider* obstacle)
{
	ensembleObstacles.push_back (obstacle);
}

double Environment::getSumOfIntensities(Vec2d location)
{
	double sum(0.0);
	for (auto ondes : waves)
	{
		//si location est sur le rayon de l'onde ou si appartient a un des arcs de l'onde -> getIntensity
		if (ondes-> isPointOnWave(location))
		{
			sum += ondes->getIntensite();
		}
		else 
		{
			sum += 0.0;
		}
	}
	return sum;
}
/*
std::unordered_map Environment::fetchData (std::string title)
{


return new_data; 

}*/

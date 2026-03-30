#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP


#include <Interface/Updatable.hpp>
#include <SFML/Graphics.hpp>

class OrganicEntity;
class Environment;
class FoodGenerator : public Updatable
{
public:
    FoodGenerator(); // constructeur par defaut qui initialise le temps a zero
	virtual ~FoodGenerator();
    void update (const sf::Time& dt) /*override*/; // methode qui fait ecoluer le compteur du temps

protected:

private:
    sf::Time time; // temps ecoulé depuis la precedente generation de nourriture

};

#endif




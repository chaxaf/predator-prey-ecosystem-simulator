#ifndef ROCK_HPP
#define ROCK_HPP

#include "CircularCollider.hpp"

class Rock : public CircularCollider

{
	
	public :

	Rock (Vec2d position_ ); //constructeur d'un ROCK
	virtual ~Rock (); //destructeur d'un ROCK

///DESSIN DES OBSTACLES 
 /*!
 * @brief méthode qui dessine les cailloux
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe 
 * @return void
 */
	virtual void draw (sf::RenderTarget& targetWindow)  override;
		
	protected :
	private : 
	double orientation; //Orientation d'un caillou
};

#endif


#ifndef WAVEGERBIL_HPP
#define WAVEGERBIL_HPP

#include "Animal/Animal.hpp"
#include "Animal/Gerbil.hpp"
#include "Environment/Food.hpp"

class Wave;
class WaveGerbil : public Gerbil 

{
	
	public :
	///CONSTRUCTEURS DE WAVE GERBIL
	WaveGerbil (Vec2d position_ , double niveauEnergie, bool sexe);
	WaveGerbil (Vec2d position_);
	///DESTRUCTEUR DE WAVE GERBIL
	virtual ~WaveGerbil () ; 
	///UPDATE DE WAVE GERBIL
		/*!
 * @brief  méthode qui s'occupe du deplacement de la gerbille et de l'emission des ondes
 *
 * @param pas de temps ecoulé de type sf::Time
 */
	void update (const sf::Time& dt) override;

	protected :

	
	private :
	///ATTRIBUTS DE LA CLASSE WAVE GERBIL
	sf::Time compteur; //Compteur utilisé pour l'emission des ondes à chaque second (1.0/getAppConfig().wave_gerbil_frequency)
	
};

#endif

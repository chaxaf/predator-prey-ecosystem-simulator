#ifndef WAVE_HPP
#define WAVE_HPP

#include <SFML/Graphics.hpp>
#include <Utility/Vec2d.hpp>
#include <Interface/Updatable.hpp>
#include <Obstacle/CircularCollider.hpp>

typedef std::pair <double, double > arc;
typedef std::vector <arc> onde;

class Wave : public CircularCollider, public Updatable // La classe wave hérite de Updatable car le rayon de l'onde varie en fonction du temps 
{
	public :
	
/*!
 * @brief CONSTRUCTEUR DE WAVE
 *
 * @note Appel au contructeur de la super classe Circular Collider
 */
	Wave (Vec2d origine_, double energy_, double rayon_, double mu_, double speed_); 
/*!
 * @brief DESTRUCTEUR DE WAVE
 *
 * @note virtuel pour eviter des fuites de mémoire lors de la création des sous classes
 */
	virtual ~Wave (); 

///DESSIN DES WAVES
 /*!
 * @brief méthode polymorphique qui dessine l'onde
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe 
 * @return void
 */
 	virtual void draw(sf::RenderTarget& targetWindow) override; 

///UPDATE DES WAVES
/*!
 * @brief  méthode qui s'occupe de l'update les attributs de la vague en fonction du temps dt
 * 
 * @param pas de temps ecoulé de type sf::Time
 */
	virtual void update(const sf::Time& dt) override; 
	
	void collision (CircularCollider* obstacle);
	bool isPointOnWave (Vec2d point) const; //verifie si un point est sur le rayon de l'onde ou si il appartient à un des arcs de l'onde

	///GETTERS
	double getStandardSpeed () const; 	//getter vitesse
	double getEnergy () const; 	// getter energie
	double getEnergieInitiale () const; //getter d'energie initiale
	double getRayonInitial () const ; //getter de rayon initial
	double getMu () const; //getter de la constante mu
	double getIntensite () const;
	
	
	protected :
	///SETTERS
	void setEnergy (const double a) ; //setter d'energie
	void setIntensite (const double a); //setter d'intensite
	
	///TESTS DE COLLISION
	bool isOnRadius(Vec2d point) const; //teste si le point en parametre est sur le razon de l'onde 
	bool isOnArc(Vec2d point) const; // teste si le point appartient a un des arcs de l'onde
	
	
	private :
	///ATTRIBUTS
	double energieInitiale;
	double rayonInitial;
	double mu; //constante mu
	double speed ; // VU QUE LA VITESSE EST CONSTANTE IL FAUT FAIRE UN TRUC??	
	double energy; 	
	sf::Time tempsEcouleDepuisDebutOnde ;
	double intensite; //intensite de la vague
	onde ensembleArcs ;

};

#endif

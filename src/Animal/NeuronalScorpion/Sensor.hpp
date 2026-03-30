#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <Application.hpp>
#include <SFML/Graphics.hpp>

class Wave;
class NeuronalScorpion;
class Sensor : public Updatable, public Drawable 
{
	public:
	Sensor(NeuronalScorpion* owner, size_t i); //constructeur d'un senseur
	virtual ~Sensor(); // destructeur 
	/*!
 * @brief Méthode qui ré-initialise le senseur
 *
 * @note  le score et le degré d'inhibition sont remis à zéro et le senseur devient inactif 
 * @note utile car le scorpion neuronale va désactiver senseurs s'ils sont actifs depuis un temps qui depasse un certain seuil
 */
	void initialiseSensor(); 
	/*!
 * @brief getter du score
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return le score du senseur, un double
 */
	double getScore() const; 
	/*!
 * @brief getter de l'index du senseur
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return l'index du senseur, un size_t
 */
	size_t getIndex() const; 
	/*!
 * @brief getter de isActive, l'etat du senseur
 *
 * @note  retourne true si le senseur est actif et false si il est inactif
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return l'etat actif ou pas du senseur, un bool
 */
	bool isActivated() const;
		/*!
 * @brief méthode qui incremente le degré d'inhibition du senseur
 *
 * @note utilisé dans la méthode NeuronalScorpion::InhibitionSenseursConnectes() 
 *  */
	void incrementInhibition(double ToAdd); 

	///DESSIN D'UN SENSEUR
		/*!
 * @brief  méthode draw qui s'occupe du dessin d'un senseur
 *
 * @param  fenetre graphique targetWindow, de type sf::RenderTarget
 */
	void draw(sf::RenderTarget& targetWindow); 
	
	///UPDATE DU SENSEUR
	/*!
 * @brief  méthode qui s'occupe de l'evolution du senseur
 *
 * @param pas de temps ecoulé de type sf::Time
 */
	void update(const sf::Time& dt);
	
	
	private:
	
	///MÉTHODE UTILE POUR LE DESSIN D'UN SENSEUR
		/*!
 * @brief méthode retournant la couleur du senseur selon son etat et son degré d'inhibition
 *
 * @note  magenta = actif et inhibition > 0.2, 
 * @note bleu = inactif et inhibition > 0.2 ,
 * @note  rouge = actif et inhibition < 0.2, 
 * @note vert = touts les autres cas
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return la couleur sf::Color
 */
	sf::Color getColor()const;
	
	///MÉTHODES POUR L'UPDATE D'UN SENSEUR	
	/*!
 * @brief  méthode qui s'occupe de plafonner l'inhibiteur s'il depasse les valeurs limites
 *
 * @note le degré d'inhibition doit etre positif et ne pas depasser la constante getAppConfig().sensor_inhibition_max
 */
	void plafonnerInhibitor(); 
		/*!
 * @brief  methode qui tempère le score 
 *
 */
	void TempererScore(); 
		/*!
 * @brief  méthode qui augemente le degré d'inhibition des senseurs connectés a this
 *
 * @note le senseur d'index i peut inhiber les 3 senseurs d'index (i+index)%8, ou index peut etre 3, 4, 5
 * @note par exemple, le senseur 5 inhibe les senseurs 0, 1 ,2
 */
	//void InhibitionSenseursConnectes(); 
	
	///ACTIVATION ET INHIBITION DES SENSEURS
			/*!
 * @brief  methode qui active le senseur
 *
 * @note le senseur est activé si l'intensité totale des ondes presents dans l'environment depasse le seuil, sinon il est inactive
 */
	void activer (); 
	
	///ATTRIBUTS PRIVES
	NeuronalScorpion* scorpion; // scorpion associé à un senseur
	size_t index; //index du senseur
	double score; //perception d'une onde
	double inhibitor; // degré de inhibition
	bool isActive; //etat du sensor, true=active, false=inactive
	sf::Time tempsActivation;
	
};



#endif

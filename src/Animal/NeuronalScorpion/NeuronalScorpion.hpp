#ifndef NEURONALSCORPION_HPP
#define NEURONALSCORPION_HPP

#include "Animal/Scorpion.hpp"
#include "Animal/NeuronalScorpion/Sensor.hpp"
#include <array>
#include <utility> 
#include <map>


//constantes a rajouter dans le fichiers de configuration je ne sais pas comment le faire 
//  getAppConfig().neuronal_scorpion_time_moving
//getAppConfig().neuronal_scorpion_time_idle) 
//nb j'ai enlevé le vielliessement de l'animal dans animal update attributs pour debugger mais apres il faut le remettre

class Sensor;
class NeuronalScorpion : public Scorpion
{
	public:
	enum class Etat {
		IDLE, 			// au repos, scorpion receptif aux ondes emises par les gerbilles
		WANDERING, 		//déambule au hasard
		TARGET_IN_SIGHT, //proie dans le champs vision
		MOVING 			//proie perçue mais pas encore vue, reorientation 
	};
	///CONSTRUCTEURS DE NEURONAL SCORPION
	NeuronalScorpion (Vec2d position_);//constructeur de NeuronalScorpion
	NeuronalScorpion (Vec2d position_, double niveauEnergie, bool sexe); //constructeur de NeuronalScorpion
	virtual ~NeuronalScorpion(); // destructeur qui fait le delete des senseurs, alloués dynamiquement 
	
	///METHODES PUBLIQUES
	/*!
 * @brief  methode retournant la position d'un senseur  donné dans le repère global
 *
 * @param un size_t qui represent l'index du senseur desiré, utilisé pour acceder à l'angle i associé
 * @return le vecteur position d'un senseur dans le repère global
 */
	Vec2d getPositionOfSensor (size_t i); 
	/*!
 * @brief  getter d'état
 *
 * @return l'etat du neuronal scorpion courant this
 */
	NeuronalScorpion::Etat getEtat(); 
	/*!
 * @brief  méthode qui active le scorpion
 *
 * @note un scorpion est active si un de ses senseurs est acitf, par défaut un scorpion est inactif
 */
	void activate(); 
/*!
 * @brief  méthode qui gère l'inhibition des senseurs connectés a chaque senseur
 *
 * @note appellé dans l'update de Sensor
 */
	void InhibitionSenseursConnectes(); 

	protected:
	
	
	private:

	///ATTRIBUTS PRIVES
	Vec2d estimationDirection; //vecteur direction vers la cible
	sf::Time time_idle; // horologe associé a l'etat IDLE - il assure que le neuronal scorpion ne reste dans cet etat plus du temps maximale
	sf::Time time_moving; // horologe associé a l'etat MOVING - il assure que le neuronal scorpion ne reste dans cet etat plus du temps maximale
	NeuronalScorpion::Etat etat; //etat du scorpion
	std::map<Sensor*, double> angles; //table associative des angles liés aux senseurs
	bool scorpionActive; //etat actif ou pas d'un scorpion, un scoprion est active si un de ses senseurs est actif
	std::array<Sensor*, 8> sensors; //ensemble des 8 senseurs du scorpion 
	
	///UPDATE DU NEURONAL SCORPION
		/*!
 * @brief  méthode qui s'occupe du deplacement du scoprion selon son etat
 *
 * @param pas de temps ecoulé de type sf::Time
 */
	void update (const sf::Time& dt); 
		/*!
 * @brief  méthode qui s'occupe du changement d'etat du scorpion
 *
 * @param pas de temps ecoulé de type sf::Time
 */
	void UpdateState (const sf::Time& dt); 
		/*!
 * @brief méthode qui mets a jour les senseurs en faisant appel à la méthode update de Sensor
 *
 * @param pas de temps ecoulé de type sf::Time
 */
	void updateSensors(const sf::Time& dt); 
	/*!
 * @brief méthode qui s'ocuupe de la gestion des horologes liés aux etats IDLE et MOVING
 *
 * @note  un NeuronalScorpion peut rester en IDLE pour pas plus de 5 secondes et en MOVING pour 3 secondes
 */
	void gestionHorologes(); 
	
	///CALCUL DE LA FORCE POUR LA MIS A JOUR DE L'ETAT
	
		/*!
 * @brief  methode retournant la force d'attraction dans l'etat MOVING 
 *
 * @return le vecteur force de la force d'attraction
 */
	Vec2d getForceAttractionMoving(); 
	
	///ESTIMATION DE LA DIRECTION VERS LA CIBLE
	
		/*!
 * @brief  methode qui s'occupe du calcul de l'estimation de la direction vers la cible 
 *
 * @note  la direction est calculé au moyen des signaux percus par les senseurs
 */
	void SetEstimationDirection(); 
			/*!
 * @brief  methode retournant le score de l'estimation 
 *
 * @note  le score est donné par la norme du Vec2d estimationDirection
 * @return la valeur du score (un double)
 */
	double ScoreEstimation () ;
	
	///TEST 26: AFFICHAGE EN MODE DEBUGGING
	
		/*!
 * @brief  conversion d'un etat en string
 *
 * @param un etat du scorpion neuronale à convertire 
 * @return un string qui correspond a un etat du scorpion
 */
	std::string fromEnumToString(NeuronalScorpion::Etat etat); 
		/*!
 * @brief  concatenation des strings pour obtenir le texte à afficher en mode DEBUGGING
 *
 * @param un etat du scorpion neuronale
 * @param le sexe du scorpion, un bool, TRUE = "female"; FALSE = "male" 
 * @param le niveau d'energie du scorpion (un double)

 * @note  on aurait pu faire autrement en appelant trois fois la méthode dans draw et en affichant les trois strings séparémment ce qui aurait permis de centrer le texte
 
 * @return la chaine de charactères (string) à afficher dans le mode DEBUGGING
 */
	std::string texteAAfficher (NeuronalScorpion::Etat etat, bool sexe, double energyLevel); 
	/*!
 * @brief  methode retournant la couleur a afficher en mode debugging pour le texte
 *
 * @return un sf::Color 
 */
	sf::Color stateColor (); 
	/*!
 * @brief  méthode qui dessin les 8 senseurs du NeuronalScorpion
 *
 * @note  fait appele à la méthode draw de Sensor, qui choisit la couleur selon l'etat du senseur 
 */
	void drawSensors (sf::RenderTarget& targetWindow); 
	
	///DESSIN DU NEURONAL SCOPRION
		/*!
 * @brief  méthode draw qui s'occupe du dessin d'un scorpion
 *
 * @param  fenetre graphique targetWindow, de type sf::RenderTarget
 */
	void draw (sf::RenderTarget& targetWindow); 
	
	

	
	
	
};

#endif

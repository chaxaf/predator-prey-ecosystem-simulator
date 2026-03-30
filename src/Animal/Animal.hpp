#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <SFML/Graphics.hpp>
#include "Environment/OrganicEntity.hpp"
#include <list>


enum valeurDeceleration {forte=9, moyenne=6, faible=3};
	// Valeurs de la deceleration a choix: 0.9 si la deceleration est forte et la vitesse est faible,
	//0.6 pour valeurs moyennes et 0.3 si la deceleration est faible et la vitesse est forte


class Animal: public OrganicEntity

{
public:
   
 /*!
 * @brief  type enumeré de l'état de l'animale
 *
 * @note declaré dans la classe pour ensuite en faire un override dans la classe Neuronal Scorpion
 */
	enum class Etat {
		FOOD_IN_SIGHT, // nourriture en vue
		FEEDING,       // en train de manger (là en principe il arrête de se déplacer)
		RUNNING_AWAY,  // en fuite
		MATE_IN_SIGHT, // partenaire en vue
		MATING,        // vie privée (rencontre avec un partenaire!)
		GIVING_BIRTH,  // donne naissance
		WANDERING     // déambule
	};
 /*!
 * @brief  CONSTRUCTEUR D'UN ANIMALE
 *
 */
    Animal (Vec2d position_, double taille, double niveauEnergie, bool sexe_);
 /*!
 * @brief  DESTRUCTEUR D'UN ANIMALE
 *
 * @note declaré virtuel pour éviter des fuites de mémoire lorsque on cré des sousclasses
 */
    virtual ~Animal(); 
    
	///DESSIN DE L'ANIMALE
	/*!
 * @brief méthode qui dessine les animales et ses cibles virtuelles (si on mode debug), en faisant un choix polymorphique
 * 
 * @param  fenetre graphique targetWindow, de type sf::RenderTarget
 * @note il aurait été mieux de déclarer cette méthode const dans toutes les classes car elle ne doit pas changer les attributs de classe 
 * @return void
 */
    virtual void draw(sf::RenderTarget& targetWindow)  override; 

	///UPDATE DE L'ANIMALE
/*!
 * @brief  méthode qui s'occupe du deplacement de l'animale selon son etat
 *
 * @param pas de temps ecoulé de type sf::Time
 */
	 virtual void update(const sf::Time& dt) override;
/*!
 * @brief  methode determinant si la cible à la position en paramètre est dans le champs de vision de l'animale
 *
 * @param un vec2d répresentant la position de la cible
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode publique car elle est utilisé dans environment
 * @return un bool, TRUE = cible dans le champs vision, FALSE = cible hors du champs vision
 */
    bool isTargetInSight (Vec2d positionCible) const; 
  
protected:

	///MÉTHODES UTILES POUR LA MIS À JOUR DE L'ANIMALE
/*!
 * @brief  methode permettant à l'animal de se déplacer et qui calcule la position et la vitesse de l'automate au bout de l'ecoulement du pas d'un intervalle de temps dt
 *
 * @return le vecteur (Vec2d) de la force calculée
 */
	Vec2d getForceAttraction ();
/*!
 * @brief  methode mettant a jour le vecteur direction apres une rotation d angle donne
 *
 * @note l'angle en radians pour la rotation
 * @return void
 */	
    void setRotation(double angle);
 /*!
 * @brief  methode calculant la force d'attraction quand l'animale est en mode food_in_sight et quand il entre en collision avec sa nourriture
 *
 * @return le vecteur (vec2d) de la force calculée
 */	
	Vec2d getForceAttractionWhenFeeding (); 
/*!
 * @brief  methode qui convert un vecteur exprimé dans le repere local d'un animal en un vecteur dans le repere global
 *
 * @param le vecteur (vec2d) à convertir
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode en protected car elle est utilisé aussi dans le NeuronalScorpion  
 * @return le vecteur (vec2d) converti en coordonnés globales
 */	
	Vec2d ConvertToGlobalCoord(Vec2d local) const; 
 /*!
 * @brief  methode qui met à jour l'etat de l'animal
 *
 * @param pas de temps ecoulé de type sf::Time
 * @return void
 */		
	 void UpdateState (const sf::Time& dt) ; 
/*!
 * @brief methode qui genère la cibe virtuelle, calcule et retourne la position de la cible
 *
 * @return le vecteur position (vec2d) 
 */	 
	 Vec2d randomWalk() ;
/*!
 * @brief analyse l'environnement pour savoir si l'entité vue est une proie , un prédateur ou un mate
 *
 * @return void 
 */		 
	void analyzeEnvironment (); 
 /*!
 * @brief  update les attributs direction, speed ... pour etre appelée dans la methode update
 * et aussi le viellissement de l'animal
 *
 * @param la force Vec2d calculé, specifique à l'état de l'animale
 * @param pas de temps ecoulé de type sf::Time
 * @return void
 */	
	 void updateAttributs (Vec2d force , const sf::Time& dt) ; 
 /*!
 * @brief  methode mettant en place la mise bas
 *
 * @param le nombre des enfants 
 * @note méthode virtuelle pure car elle est redéfinie de manière spécifique dans chaque sous classe, 
 * mais on en a besoin dans la mis à jour de l'animale
 * @return void
 */		 
	virtual void give_birth (unsigned int nbEnfants) = 0 ; 
	
/*!
 * @brief  methode calculant le vecteur vitesse de l'animal
 *
 * @note ce vecteur est donné par le produit de la direction et la norme de la vitesse
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un vecteur de type Vec2d   
 */   
    Vec2d getSpeedVector() const;
    /*!
 * @brief accesseur qui retourne la vitesse maximale
 *
 * @note selon l'etat de l'animale on affecte à sa vitesse des valeurs spécifiques
 * @return un double  
 */
	double getMaxSpeed (); 
	
/*!
 * @brief  methode qui affiche en gris le champs de vision de l'animal
 *
 * @param fenetre graphique targetWindow, de type sf::RenderTarget
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un temps sf::Time 
 */		
	 void drawVision(sf::RenderTarget& targetWindow) const;
   
	
	///SETTERS PROTEGÉS
/*!
 * @brief manipulateur qui affecte à l'attribut pregnant la valeur baby 
 * 
 * @param la valeur à affecter
 * @return void
 */
	void setPregnant(bool baby);
/*!
 * @brief manipulateur qui affecte à l'attribut tempsPauseGivingBirth la valeur en paramètre pause
 * 
 * @param la valeur à affecter
 * @return void
 */	
	void setTimeGivingBirth(sf::Time pause);
/*!
 * @brief manipulateur qui affecte à l'attribut tempsDeGestation la valeur en paramètre gestation
 * 
 * @param la valeur à affecter
 * @return void
 */	
	void setTimeGestation(sf::Time gestation);
/*!
 * @brief manipulateur qui affecte à l'attribut tempsPauseMating la valeur en paramètre mating
 * 
 * @param la valeur à affecter
 * @return void
 */		
	void setTimeMating(sf::Time mating);
/*!
 * @brief manipulateur qui affecte à l'attribut etat_ la valeur en paramètre etat
 * 
 * @param la valeur à affecter
 * @return void
 */	
	void setEtat (Etat etat);
/*!
 * @brief manipulateur qui affecte à l'attribut nbEnfants la valeur en paramètre nb
 * 
 * @param la valeur à affecter
 * @return void
 */		
	void setNumberChildren(unsigned int nb);
/*!
 * @brief manipulateur qui affecte à l'attribut targetPosition la valeur en paramètre newPosition
 * 
 * @param la valeur à affecter
 * @return void
 */
	 void setTargetPosition(Vec2d newPosition);
   	
	
	///GETTERS PROTEGÉS
	
/*!
 * @brief  accesseur qui retourne le sexe de l'animale
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un bool, TRUE = femelle, FALSE = male
 */	
	bool isFemale() const;
/*!
 * @brief  accesseur qui retourne si l'animale est enceinte ou pas
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un bool, TRUE = enceinte, FALSE = non enceinte
 */	
	bool isPregnant() const;
/*!
 * @brief  accesseur qui retourne le nombre des enfants de l'animale
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un unsigned int, car cette valeur ne peut pas etre negative
 */		
	unsigned int getNumberChildren() const;
/*!
 * @brief  accesseur qui retourne l'état de l'animale
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un Etat
 */		
	Etat getEtat() const; 
/*!
 * @brief  accesseur qui retourne le poiteur sur la nourriture plus proche relevé par l'animale
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un pointeur sur une organic Entity
 */	
	OrganicEntity* getNourritureProche() const;
/*!
 * @brief  accesseur qui retourne la direction de deplacement de l'animale
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return le vecteur direction 
 */	
	virtual Vec2d getDirection () const;
/*!
 * @brief  accesseur qui retourne la valeur constante de la vitesse maximale de deplacement de l'animal
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car elle est nécessaire pour les calculs liés au déplacement de l'animale, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle sera redéfinie en manière spécifique dans chaque sous-classe
 * @return un double  
 */		
	  virtual double getStandardMaxSpeed() const = 0;
/*!
 * @brief  accesseur qui retourne la valeur constante de la masse de l'animal
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car elle est nécessaire pour les calculs liés au déplacement de l'animale, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle sera redéfinie en manière spécifique dans chaque sous-classe
 * @return un double  
 */	
    virtual double getMass() const = 0;
/*!
 * @brief  accesseur qui retourne la valeur constante de l'angle de vision (en radians) de l'animal
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car elle est nécessaire dans la classe Animal,
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle sera redéfinie en manière spécifique dans chaque sous-classe
 * @return un double  
 */	
    virtual double getViewRange() const = 0;
/*!
 * @brief accesseur qui retourne la valeur constante de la distance maximale pour le champ de vision
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car elle est nécessaire dans la classe Animal,
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle sera redéfinie en manière spécifique dans chaque sous-classe
 * @return un double  
 */
    virtual double getViewDistance() const = 0;
/*!
 * @brief accesseur qui retourne la valeur de la perte d'énergie
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car elle est nécessaire dans la classe Animal,
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle sera redéfinie en manière spécifique dans chaque sous-classe
 * @return un double  
 */
	 virtual double getEnergyLossFactor() const=0; 
/*!
 * @brief  accesseur qui retourne l'angle du vecteur direction en coordonnees polaires
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note on utilise la methode angle() de Vec2d
 * @return un double  
 */	   
	 double getRotation() const;
 /*!
 * @brief  méthode qui convert un double en temps (sf::Time)
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note on utilise la methode sf::seconds 
 * @return un temps sf::Time 
 */	
	sf::Time fromDouble (double d) const; 

private:

	///MÉTHODES PRIVÉES
/*!
 * @brief methode calculant la force d'attraction quand l'animale est en mode RUNNING_AWAY
 *
 * @return un vecteur de type Vec2d
 */	
    Vec2d getForceAttractionFuite(); 
    
    ///GETTERS VIRTUELS PURS
 /*!
 * @brief accesseur de le rayon du cercle de la cible virtuelle
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car elle est nécessaire dans la classe Animal,
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle sera redéfinie en manière spécifique dans chaque sous-classe
 * @return un double  
 */
    virtual double getRandomWalkRadius() const = 0; 
/*!
 * @brief accesseur de la distance du centre de cercle a la position de l'animal
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car elle est nécessaire dans la classe Animal,
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle sera redéfinie en manière spécifique dans chaque sous-classe
 * @return un double  
 */   
    virtual double getRandomWalkDistance() const = 0; 
  /*!
 * @brief accesseur du facteur d'amplification du deplacement de la cible virtuelle
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car elle est nécessaire dans la classe Animal,
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle sera redéfinie en manière spécifique dans chaque sous-classe
 * @return un double  
 */   
    virtual double getRandomWalkJitter() const = 0; 
    
    ///METHODES POUR LE DESSIN DE L'ANIMALE
 /*!
 * @brief méthode convertisseur d'état en string
 * 
 * @param l'etat à convertire
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return le string converti
 */   
    std::string fromEnumToString(Etat etat) const;  
     /*!
 * @brief méthode qui retourne le texte à afficher pour le debugging
 * 
 * @param un etat du scorpion neuronale
 * @param le sexe du scorpion, un bool, TRUE = "female"; FALSE = "male" 
 * @param le niveau d'energie du scorpion (un double)
 * @note  on aurait pu faire autrement en appelant trois fois la méthode dans draw et en affichant les trois strings séparémment ce qui aurait permis de centrer le texte
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return le string à afficher
 */   
    std::string texteAAfficher (Etat etat, bool sexe, double energyLevel) const; 
 /*!
 * @brief  methode retournant la couleur a afficher en mode debugging pour le texte
 *
 * @return un sf::Color 
 */ 
    sf::Color stateColor () const; 
   
   
	///ATTRIBUTS DE LA CLASSE ANIMAL 
	Vec2d direction; // direction de deplacement de l'animal
	double speed; // norme de la vitesse de l'animal
    Vec2d targetPosition; // position de la cible pursuivi par l'animal
	Vec2d current_target;
	bool sexe;	//attribut sexe de l'animal
	bool pregnant;
    unsigned int nbEnfants; //attribut nombre d'enfants
    Etat etat_;

	///HOROLOGES LIÉS AU ANIMALE
    sf::Time tempsPause; // compteur du temps de pause apres la consommation de nourriture
   	sf::Time tempsPauseMating; //temps pause apres mating
	sf::Time tempsDeGestation;  //attribut temps de gestation
	sf::Time tempsPauseGivingBirth; //temps pause pour la mise bas
	
    ///ATTRIBUTS UTILES POUR L'ANALYSE DE L'ENVIRONNEMENT
    std::vector <OrganicEntity*> listeDePredateurs; // liste de prédateurs en vue pour la proie
    OrganicEntity* nourritureProche; //attribut nourriture la plus proche pour l'animal
    OrganicEntity* mateProche; //attribut mate le plus proche pour l'animal
   
};

#endif


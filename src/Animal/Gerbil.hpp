#ifndef GERBIL_HPP
#define GERBIL_HPP

#include "Animal/Animal.hpp"
#include "Animal/Scorpion.hpp"
#include "Environment/Food.hpp"



class Gerbil: public Animal
{
	public:

/*!
 * @brief CONSTRUCTEUR DE GERBIL
 *
 * @note La classe Gerbil a deux contructeurs
 * @note Le premier prend en paramètre une position, un niveau d'energie et un sexe
 * @note Le second prend seulement une position, 
 * car le niveau d'energie est initialisé par defaut a une constante et le sexe est tiré au hasard par la fonction uniform
 * @note ce deuxième contructeur est utile pour la reproduction : le sexe du nouveau né doit etre aléatoirement choisi
 */

    Gerbil (Vec2d position_, double niveauEnergie, bool sexe); 
	Gerbil (Vec2d position_);
/*!
 * @brief DESTRUCTEUR DE GERBIL
 *
 * @note declaré virtual pour eviter des fuites de mémoire lorsque on cré des sousclasses
 */
    virtual ~Gerbil(); 
        
///DESSIN DES GERBILLES
 /*!
 * @brief méthode qui dessine les gerbilles
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe 
 * @return void
 */
    virtual void draw(sf::RenderTarget& targetWindow) override;

/*!
 * @brief methode qui teste si gerbille est morte ou non 
 *
 * @note override de la méthode virtuelle de organic entity qui utilise la longevité specifique des gerbilles
 * @return un bool, true si l'energie est inferieur d'un seuil critique ou si l'age depasse la longevité maximale de l'animale
 */
    virtual bool isDead () const override; 
	
	
	protected:
	
///GETTERS
 /*!
 * @brief accesseur qui retourne la valeur constante de la vitesse maximale de deplacement de la gerbille
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */
    virtual double getStandardMaxSpeed() const override;
/*!
 * @brief accesseur qui retourne la valeur constante de la masse de la gerbille
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un double
 */
    double getMass() const override;
/*!
 * @brief accesseur qui retourne la valeur constante de l'angle de vision (en radians) de la gerbille
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
* @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe * 
 * 
 * @return un double
 */
    double getViewRange() const override;
/*!
 * @brief  accesseur qui retourne la valeur constante de la distance maximale pour le champ de vision
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */
    virtual double getViewDistance() const override;
/*!
 * @brief   accesseur de le rayon du cercle de la cible virtuelle
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */
    double getRandomWalkRadius() const override; 
/*!
 * @brief  accesseur de la distance du centre de cercle a la position de la gerbille
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */
    double getRandomWalkDistance() const override;    
/*!
 * @brief accesseur du facteur d'amplification du deplacement de la cible virtuelle
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe  
 * @return un double
 */
    double getRandomWalkJitter() const override; 
 /*!
 * @brief accesseur retorunant la valeur de la perte d'énergie
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */ 
    virtual double getEnergyLossFactor() const override;
 

/// DOUBLE DISPATCH - EST-CE MANGEABLE?
/*!
 * @brief methode qui permet d'evaluer si un entité organique peut manger ou non l'enité this
 *
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note le double dispatch permet d'eveiter des dangereux tests de type
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un bool, true si la gerbille this peut manger l'entité organique en paramètre,  sinon false
 */
    virtual bool eatable(OrganicEntity const* entity) const override; 
/*!
 * @brief methode qui permet de evaluer si this peut etre mangé par l'entité organique other en paramètre
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note retourne true seulement pour les scorpions
 * @return un bool
 */
    bool eatableBy(Scorpion const*  wolf) const override;
    bool eatableBy(Gerbil const* sheep) const override;
    bool eatableBy(Food const* food) const override;

/// DOUBLE DISPATCH REPRODUCTION
 /*!
 * @brief methode qui permet de evaluer si this peut se reproduire avec l'entité organique other en paramètre
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note le double dispatch permet d'eveiter des dangereux tests de type
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note on test aussi si l'organic entity en paramètre est la meme que this 
 * @return un bool
 */
    virtual bool matable(OrganicEntity const* other) const override;
    
   /*!
 * @brief methode qui permet de evaluer si la réproduction peut avoir lieu
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note une gerbille peut se reproduire seulement avec une autre gerbille de sexe opposé, 
 * seulement si elle a assez energie, si elle est suffisament agé et si elle n'est pas enceinte ou en train de mettre bas
 * @return un bool
 */ 
    virtual bool canMate(Scorpion const* scorpion) const override;
    virtual bool canMate(Gerbil const* gerbil) const override;
    virtual bool canMate(Food const* food) const override;

   
  /// DOUBLE DISPATCH RENCONCTRE ET REPRODUCTION
 /*!
 * @brief méthode mettant en place la reproduction
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note le double dispatch permet d'eveiter des dangereux tests de type
 * @return un bool
 */
    virtual void meet (OrganicEntity* entity)  override ; 
    virtual void meetDispatch (Scorpion* scorpion)  override;
	virtual void meetDispatch (Gerbil* gerbil)  override;
	virtual void meetDispatch (Food* food)  override;
	
	/*!
 * @brief  methode mettant en place la mise bas
 *
 * @param le nombre des enfants 
 * @return void
 */	
    virtual void give_birth (unsigned int nbEnfants) override ;
	
private:


};

#endif


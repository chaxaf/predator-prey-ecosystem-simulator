#ifndef SCORPION_HPP
#define SCORPION_HPP

#include "Animal/Animal.hpp"
#include "Animal/Gerbil.hpp"
#include "Environment/Food.hpp"

class Gerbil;
class Scorpion : public Animal
{
public:

/*!
 * @brief CONSTRUCTEUR DE SCORPION 
 *
 * @note La classe Scorpion a deux contructeurs
 * @note Le premier prend en paramètre une position, un niveau d'energie et un sexe
 * @note Le second prend seulement une position, 
 * car le niveau d'energie est initialisé par defaut a une constante et le sexe est tiré au hasard par la fonction uniform
 * @note ce deuxième contructeur est utile pour la reproduction : le sexe du nouveau né doit etre aléatoirement choisi
 */
	Scorpion (Vec2d position_);
    Scorpion (Vec2d position_, double niveauEnergie, bool sexe);
/*!
 * @brief DESTRUCTEUR DE SCORPION
 *
 * @note declaré virtual pour eviter des fuites de mémoire lorque on cré des sousclasses
 */
    virtual ~Scorpion (); 
  
///DESSIN DES SCORPIONS
 /*!
 * @brief méthode qui dessine le scorpion et sa cible (si on est en mode debug)
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe 
 * @return void
 */
    virtual void draw(sf::RenderTarget& targetWindow) override;
  
 /*!
 * @brief methode qui teste si le scorpion est mort ou non 
 *
 * @note override de la méthode virtuelle de organic entity qui utilise la longevité specifique des scorpions
 * @return un bool, true si l'energie est inferieur d'un seuil critique ou si l'age depasse la longevité maximale de l'animale
 */
    virtual bool isDead () const override; 

	protected:

///GETTERS
/*!
 * @brief accesseur qui retourne la valeur constante de la vitesse maximale de deplacement du scorpion
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe *  
 * @return un double
 */
    virtual double getStandardMaxSpeed() const override;
/*!
 * @brief accesseur qui retourne la valeur constante de la masse du scorpion
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */
    virtual double getMass() const override;
 /*!
 * @brief accesseur qui retourne la valeur constante de l'angle de vision (en radians) du scorpion
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */
    virtual double getViewRange() const override;
 /*!
 * @brief accesseur qui retourne la valeur constante de la distance maximale pour le champ de vision
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */
    virtual double getViewDistance() const override;
 /*!
 * @brief accesseur de le rayon du cercle de la cible virtuelle
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */
    virtual double getRandomWalkRadius() const override;  
 /*!
 * @brief accesseur de la distance du centre de cercle a la position du scoprion
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */
    virtual double getRandomWalkDistance() const override; 
 /*!
 * @brief accesseur du facteur d'amplification du deplacement de la cible virtuelle
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note declaré virtual car elle est nécessaire dans la superclasse Animal, 
 * mais, a ce niveau de la hierarchie, on sait pas comment définire cette valeur. Elle est donc redéfinie en manière spécifique dans chaque sous-classe
 * @return un double
 */
    virtual double getRandomWalkJitter() const override; 
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
 * @return un bool, true si le scorpion this peut manger l'entité organique other en paramètre, sinon false
 */
    virtual bool eatable(OrganicEntity const* entity) const override; 
 /*!
 * @brief methode qui permet de evaluer si this peut etre mangé par l'entité organique other en paramètre
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note retourne toujours false car les scorpions n'ont pas des predateurs
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
 * @note un scorpion peut se reproduire seulement avec un autre scorpion de sexe opposé, 
 * seulement s'il a assez energie, s'il est suffisament agé et s'il n'est pas enceinte ou en train de mettre bas
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
    virtual void meet (OrganicEntity* entity)   override; 
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

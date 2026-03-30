#ifndef ORGANICENTITY_HPP
#define ORGANICENTITY_HPP

#include "Obstacle/CircularCollider.hpp"
#include <SFML/Graphics.hpp>
#include <Interface/Updatable.hpp>
#include <Interface/Drawable.hpp>

class Scorpion;
class Food;
class Gerbil;
class OrganicEntity : public CircularCollider , public Updatable
{
public:

/*!
 * @brief CONSTRUCTEUR D'UNE ORGANIC ENTITY
 *
 * @note Comme Organic Entity hérite de Circular Collider, dans son constructeur on fait appel au constructeur de cette super classe
 */
    OrganicEntity (Vec2d position, double taille, double niveauEnergie); 
    /*!
 * @brief DESTRUCTEUR DE ORGANIC ENTITY
 *
 * @note declaré virtual pour eviter des fuites de mémoire lorque on cré des sousclasses
 */
    virtual ~OrganicEntity(); 
    ///UPDATE D'UNE ORGANIC ENTITY
/*!
 * @brief  méthode qui s'occupe du viellissement de l'entité organique
 * 
 * @note declaré virtuelle car elle verra redéfinie après dans les sous classes
 * @param pas de temps ecoulé de type sf::Time
 */
    virtual void update(const sf::Time& dt);
 
/*!
 * @brief methode qui teste si l'entité est morte ou non 
 *
 * @note méthode virtuelle redéfinie après dans chaque sous classe avec la longevité spécifique de classe
 * @return un bool, true si l'energie est inferieur d'un seuil critique ou si l'age depasse la longevité maximale
 */
 virtual bool isDead () const; // methode qui teste si entity est morte ou non ( en utilisant la longevité par default)

/// DOUBLE DISPATCH - EST-CE MANGEABLE?
/*!
 * @brief methode qui permet d'evaluer si un entité organique peut manger ou non l'enité this
 *
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note le double dispatch permet d'eveiter des dangereux tests de type
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car, à ce niveau de conception, on ne peut pas encore la définire, mais on en a besoin dans les méthodes de mis à jour de Animal
 * @return un bool
 */
    virtual bool eatable ( OrganicEntity const* entity) const = 0;
/*!
 * @brief methode qui permet de evaluer si this peut etre mangé par l'entité organique other en paramètre
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car, à ce niveau de conception, on ne peut pas encore la définire, mais on en a besoin dans les méthodes de mis à jour de Animal
 * @return un bool
 */
    virtual bool eatableBy(Scorpion const*  wolf) const = 0;
    virtual bool eatableBy(Gerbil const* sheep) const = 0;
    virtual bool eatableBy(Food const* food) const = 0;
    
    /// DOUBLE DISPATCH REPRODUCTION
 /*!
 * @brief methode qui permet de evaluer si this peut se reproduire avec l'entité organique other en paramètre
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note le double dispatch permet d'eveiter des dangereux tests de type
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car, à ce niveau de conception, on ne peut pas encore la définire, mais on en a besoin dans les méthodes de mis à jour de Animal
 * @return un bool
 */
    virtual bool matable(OrganicEntity const* other) const = 0;
 /*!
 * @brief methode qui permet de evaluer si la réproduction peut avoir lieu
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note méthode virtuelle pure car, à ce niveau de conception, on ne peut pas encore la définire, mais on en a besoin dans les méthodes de mis à jour de Animal
 * @return un bool
 */ 
    virtual bool canMate(Scorpion const* scorpion) const = 0;
    virtual bool canMate(Gerbil const* gerbil) const = 0;
    virtual bool canMate(Food const* food) const = 0;

  
    /// DOUBLE DISPATCH RENCONCTRE ET REPRODUCTION
 /*!
 * @brief méthode mettant en place la reproduction
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note le double dispatch permet d'eveiter des dangereux tests de type
 * @note méthode virtuelle pure car, à ce niveau de conception, on ne peut pas encore la définire, mais on en a besoin dans les méthodes de mis à jour de Animal
 * @return un bool
 */
    virtual void meet (OrganicEntity* entity) = 0; 
	virtual void meetDispatch (Scorpion* scorpion) =0;
    virtual void meetDispatch (Gerbil* gerbil) = 0;
    virtual void meetDispatch (Food* food) = 0;
    
 /*!
 * @brief méthode qui s'occupe du viellissement de l'entité organique 
 *
 * @param pas de temps ecoulé de type sf::Time, à décrementer à l'age
 * @return void
 */ 
    void Viellissement(const sf::Time& dt);
     ///GETTERS
  /*!
 * @brief accesseur qui retourne le niveau d'energie de l'entité organique
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un double
 */
     double getEnergyLevel() const;
  /*!
 * @brief accesseur qui retourne l'age de l'entité organique
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return l'attribut sf::Time age
 */
     sf::Time getAge() const;
     
     ///MANIPULATEURS SUR L'ENERGIE DE L'ENTITÉ ORGANIQUE
 /*!
 * @brief manipulateur qui affecte au niveau d'energie de this la valeur newEnergy
 *
 * @param la valeur à affecter
 * @return void
 */  
     void setEnergyLevel (double newEnergy); 
 /*!
 * @brief manipulateur qui decremente le niveau d'energie d'une quantité energyLost
 *
 * @param la valeur à décrementer
 * @return void
 */    
     void EnergyLoss (double energyLost); 
 /*!
 * @brief manipulateur qui incremente le niveau d'energie d'une quantité eneryGained
 *
 * @param la valeur à incrementer
 * @return void
 */     
     void EnergyGain (double energyGained); 
 
     
protected:
 
private:
	///ATTRIBUTS DE LA CLASSE ORGANIC ENTITY
	double energyLevel; //niveau d'energie de l'entité organique
    sf::Time age; // horologe associé a l'age

};

#endif




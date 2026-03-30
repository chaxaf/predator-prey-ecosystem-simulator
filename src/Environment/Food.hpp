#ifndef FOOD_HPP
#define FOOD_HPP

#include <SFML/Graphics.hpp>
#include "Environment/OrganicEntity.hpp"


//class OrganicEntity;
class Scorpion;
class Gerbil;
class Food : public OrganicEntity

{

public:

    Food (Vec2d const& position); //constructeur d'une source de nourriture
    virtual ~Food (); //destructeur déclaré virtual pour éviter des fuites de mémoire, si on cré de eventuelles sous-classes de food

///DESSIN DES FOOD
 /*!
 * @brief méthode qui dessine les sources de nourriture
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe 
 * @return void
 */
    void draw(sf::RenderTarget& targetWindow) override;
///UPDATE DES FOOD
		/*!
 * @brief  méthode rédefinie vide pour éviter que la classe Food, heritante de Organic Entity, ne soit pas virtuelle pure et donc non-instanciable
 *
 * @note on doit pouvoir créer des nouvelles sources de nourriture à rajouter à l'environnement 
 * @param pas de temps ecoulé de type sf::Time
 */
    void update (const sf::Time& dt) override;
    
    protected:
    
/// DOUBLE DISPATCH - EST-CE MANGEABLE?
/*!
 * @brief methode qui permet d'evaluer si un entité organique peut manger ou non l'enité this
 *
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note le double dispatch permet d'eveiter des dangereux tests de type
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un bool, true si le food this peut manger l'entité organique en paramètre, sinon false
 */
    virtual bool eatable(OrganicEntity const* entity) const override; // methode returnant true si food this peut manger l'entité organique other

/*!
 * @brief methode qui permet de evaluer si this peut etre mangé par l'entité organique other en paramètre
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note retourne true seulement pour les gerbilles
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
 * @return un bool
 */
    virtual bool matable(OrganicEntity const* other) const override;
/*!
 * @brief methode qui permet de evaluer si la réproduction peut avoir lieu
 * 
 * @param pointeur sur une organic entity qui represente l'entité qui rencontre this
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @note un food peut se reproduire avec un autre food
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
    virtual void meet (OrganicEntity* entity) override; 
    virtual void meetDispatch (Scorpion* scorpion) override;
    virtual void meetDispatch (Gerbil* gerbil)  override;
    virtual void meetDispatch (Food* food)  override;



private:


};

#endif


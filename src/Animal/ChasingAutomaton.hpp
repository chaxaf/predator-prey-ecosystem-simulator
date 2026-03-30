#ifndef CHASINGAUTOMATON_HPP
#define CHASINGAUTOMATON_HPP

#include <Utility/Vec2d.hpp>
#include "Obstacle/CircularCollider.hpp"
#include <SFML/Graphics.hpp>
#include <Environment/Environment.hpp>

enum valeurDeceleration {forte=9, moyenne=6, faible=3};
	// Valeurs de la deceleration a choix: 0.9 si la deceleration est forte et la vitesse est faible,
	//0.6 pour valeurs moyennes et 0.3 si la deceleration est faible et la vitesse est forte


class ChasingAutomaton : public CircularCollider
{
public:
    //constructeur d'un automate
    ChasingAutomaton (Vec2d position_);
    ///GETTERS 
 /*!
 * @brief  accesseur qui retourne la valeur constante de la vitesse maximale de deplacement de l'automate
 *
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return un double
 */
    double getStandardMaxSpeed() const;
 /*!
 * @brief accesseur qui retourne la valeur constante de la masse de l'automate
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe 
 * @return un double
 */
    double getMass() const;
     /*!
 * @brief  methode calculant le vecteur vitesse de l'automate 
 * 
 * @note le vecteur est donné par le produit de la direction et la norme de la vitesse
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe 
 * @return un vecteur de type Vec2d
 */
    Vec2d getSpeedVector() const;
     
    ///SETTERS
 /*!
 * @brief manipulateur qui modifie la valeur de la position de la cible, en lui affectant la valeur newPosition
 * 
 * @return void
 */
    void setTargetPosition(Vec2d newPosition);
    
 /*!
 * @brief méthode qui dessine l'automate et sa cible
 * 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe 
 * @return void
 */
    void draw(sf::RenderTarget& targetWindow) ;
   
   ///DEPLACEMENT DE L'AUTOMATE
/*!
 * @brief methode calculante la force d'attraction vers la cible, necessaire pour le deplacement de l'automate
 * 
 * @return un vecteur de type Vec2d
 */
     Vec2d getForceAttraction() ; 
 /*!
 * @brief methode permettant a l'automate de se deplacer et qui calcule la position et la vitesse de l'automate au bout de l'ecoulement du pas d'un intervalle de temps dt
 *  
 * @param le pas de temps dt ecoulé, de type sf::Time
 * @return void
 */
    void update(sf::Time dt);
   

private:
    Vec2d direction; // direction de deplacement du automate
    double speed; // norme de la vitesse du automate
    Vec2d targetPosition; // position de la cible pursuit par l'automate

};

#endif

#include <iostream>
#include "Animal/ChasingAutomaton.hpp"
#include <Application.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <Environment/Environment.hpp>

using namespace std;

// constructeur d automate
ChasingAutomaton::ChasingAutomaton (Vec2d position_)
    : CircularCollider (position_ , CHASING_AUTOMATON_RADIUS ),
      direction (Vec2d(1.0, 0.0)), speed (0.0),  targetPosition (Vec2d(0.0, 0.0))
{}

// accesseur qui retourne la valeur constante de la vitesse maximale de deplacement de l'automate
double ChasingAutomaton::getStandardMaxSpeed() const
{
    return CHASING_AUTOMATON_MAX_SPEED;
}
// accesseur qui retourne la valeur constante de la masse de l'automate
double ChasingAutomaton::getMass() const
{
    return CHASING_AUTOMATON_MASS;
}

// manipulateur qui modifie la valeur de la position de la cible, en lui affectant la valeur newPosition
void ChasingAutomaton::setTargetPosition(Vec2d newPosition)
{
    targetPosition = newPosition;
}

// methode calculant le vecteur vitesse de l'automate donnee par le produit de la direction et la norme de la vitesse
Vec2d ChasingAutomaton::getSpeedVector() const
{
    return (direction*speed); // utilisation de la surcharge de l'operateur * du Vec2d
}

// methode permettant a l'automate de se deplacer et qui calcule la position et la vitesse de l'automate au bout de l'ecoulement du pas d'un interval de temps dt
/*void ChasingAutomaton::update(sf::Time dt)
{
}
*/
// methode qui dessine l'automate
void ChasingAutomaton::draw(sf::RenderTarget& targetWindow) 
{
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite(getPosition(),(getRadius()*2), texture));
    targetWindow.draw(image_to_draw);
    targetWindow.draw(buildCircle (targetPosition, 5 , sf::Color(255,0,0)));
}
/*
// methode qui initialise la deceleration a valeur
void ChasingAutomaton::initialise_deceleration (double deceleration, valeurDeceleration valeur)
{
	deceleration = valeur/10.0;
}

*/
// methode qui retourne la force d'attraction (etape 1)
Vec2d ChasingAutomaton::getForceAttraction ()
{

    /*double deceleration;
    valeurDeceleration v(forte);
    initialise_deceleration (deceleration, v);*/

    valeurDeceleration deceleration (moyenne);
    Vec2d toTarget (targetPosition - getPosition()); //position de la cible - position de l'automate
    double speed_ ;

    Vec2d nul (0,0);
    if (toTarget == nul) {
        return nul;
    }

    else {

        if ((toTarget.length()/(deceleration/10.0)) < getStandardMaxSpeed()) {
            speed_ = (toTarget.length()/(deceleration/10.0));
        } else  {
            speed_ = getStandardMaxSpeed();
        }

        Vec2d targetSpeed ((toTarget/toTarget.length())*(speed_)); // vitesse que l'automate souhaite avoir vers la cible
        return targetSpeed - getSpeedVector();
    }
}


// methode permettant a l'automate de se deplacer et qui calcule la position et la vitesse de l'automate au bout de l'ecoulement du pas d'un intervalle de temps dt
void ChasingAutomaton::update(sf::Time dt)
{
    /*sf::Clock clock; //horloge
    dt = clock.getElapsedTime(); //Récupération du temps écoulé*/

    Vec2d acceleration (getForceAttraction()/ getMass());
    Vec2d newSpeed (getSpeedVector() + acceleration * dt.asSeconds());
    Vec2d newDirection = newSpeed.normalised(); // nouvelle vitesse normalisee

    // plafonner la nouvelle vitesse
    if (newSpeed.length() > getStandardMaxSpeed()) {
        newSpeed = newDirection * getStandardMaxSpeed();
    }
    move(newSpeed * dt.asSeconds());
    direction = newDirection;
    speed = newSpeed.length();
}






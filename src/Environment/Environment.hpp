#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP


//inclure dans le cpp animal.hpp mais pas ici
#include <list>
#include <vector>
#include <iostream>
#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <Application.hpp>
#include "Environment/FoodGenerator.hpp"
#include <Interface/Updatable.hpp>
#include <Interface/Drawable.hpp>
#include "Wave.hpp" 
#include "Obstacle/Rock.hpp"

class Wave;
class OrganicEntity;
class Animal;
class Environment : public Updatable, public Drawable
{
public :

    Environment () = default; //constructeur d'environnement

    virtual ~Environment (); //destructeur d'environnement

///AJOUT DES ENTITES AU ENVIRONNEMENT
 /*!
 * @brief méthode permettant d'ajouter une entite organique à l'environnement
 * 
 * @param L'Organic Entity à rajouter à la liste des entités presentes dans l'environnement
 */
    void addEntity (OrganicEntity* entity) ; 
 /*!
 * @brief  methode qui ajout un generateur a la liste de generatuers
 * 
 * @param Le Food Generator à rajouter à la liste 
 */
     void addGenerator (FoodGenerator* generateur); 
 /*!
 * @brief  methode qui ajout une onde a la liste des ondes de l'environnement
 * 
 * @param La Wave à rajouter à la liste 
 */
	void addWave (Wave* wave); 
/*!
 * @brief  methode qui ajout un obstacle à la liste des obstacles de l'environnement
 * 
 * @param Le CircularCollider à rajouter à la liste 
 */
	void addObstacle (CircularCollider* obstacle); 

///UPDATE DE L'ENVIRONNEMENT
/*!
 * @brief  méthode qui s'occupe de l'évolution des animaux de la faune, des sources de nourriture, des ondes et des obstacles
 *
 * @note dans cette méthode on s'ocuppe de la suppression des entités mortes
 * @param pas de temps ecoulé de type sf::Time
 */
    virtual void update(const sf::Time& dt) override ; 
 
 ///DESSIN DE L'ENVIRONMENT
	/*!
 * @brief méthode qui dessine l'environment
 * 
 * @param  fenetre graphique targetWindow, de type sf::RenderTarget
 * @note il aurait été mieux de déclarer cette méthode const dans toutes les classes car elle ne doit pas changer les attributs de classe 
 * @return void
 */
    virtual void draw(sf::RenderTarget& targetWindow) ; 
    
	/*!
 * @brief méthode effacant de l'environnement tout animal ou cible
 * 
 * @return void
 */
    void clean ();  
    
 /*!
 * @brief méthode retournant la liste des entités dans le champs vision de l'animale en paramètre
 * 
 * @param un pointeur constante sur un animale 
 * @return l'ensemble des entités vues, un vector des pointeur sur Organic Entity 
 */   
	std::vector <OrganicEntity*> getEntitiesInSightForAnimal (Animal const* animal) const;
 /*!
 * @brief méthode qui calcule la somme des intensités des ondes dans l'environment
 * 
 * @param un vecteur position Vec2d 
 * @return la somme des intensités calculée
 */  
	double getSumOfIntensities(Vec2d location); 
	
	//std::unordered_map fetchData (std::string title);


private :
	
	///ATTRIBUTS DE LA CLASSE ENVIRONMENT 
    std::list <OrganicEntity*> ensembleEntites; //ensemble des entités presentes dans l'environnement
    std::list <FoodGenerator*> ensembleGenerateurs; //ensemble des generateurs de nourriture
    std::list <Wave*> waves; // ensemble des ondes presentes dans l'environnement
	std::list <CircularCollider*> ensembleObstacles; // ensemble des obstacles presents dans l'environnement

 /*!
 * @brief constructeur de copie supprimé pour empêcher toute copie de l'environnement
 * 
 */ 
    Environment (const Environment& otherEnvironment) = delete; 
};

#endif

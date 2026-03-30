#ifndef CIRCULARCOLLIDER_HPP
#define CIRCULARCOLLIDER_HPP

#include <Utility/Vec2d.hpp>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <Interface/Drawable.hpp>

class CircularCollider : public Drawable
{
public :

    CircularCollider (Vec2d position, double radius); //constructeur de cercle défini par son rayon et la position de son centre
	CircularCollider (CircularCollider const& cercle);  //constructeur de copie
    virtual ~CircularCollider() =default; //destructeur declaré virtual pour eviter des fuites de memoire

///SURCHARGE DES OPÉRATEURS
    CircularCollider operator=(CircularCollider& copieCercle) const; //operateur d'affectation =
    Vec2d& operator+=(Vec2d const& dx)  ;
    bool operator>(CircularCollider const& other) const ; //operateur > entre deux CircularCollider verifiant si other est à l'intérieur d'un autre CircularCollider
    bool operator|(CircularCollider const& other) const ; //operateur | verifiant si deux CircularCollider sont en collision
    bool operator>(Vec2d point) const ; //operateur > entre un point et un circularCollider vérifiant si le point est à l'intérieur du CircularCollider
    void affiche (std::ostream& out) const; // affiche le message demandé (méthode publique définie pour coder l'opérateur << )

	/*!
 * @brief  algorithme clamping qui incrémente + ou - la taille du monde aux valeurs fournies si celle-ci est inférieure à 0
 */
    void Clamping ();
	/*!
 * @brief methode calculant la distance la plus faible entre deux points to et from vecteur le plus court
 *
 * @param le vecteur to
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return le vecteur d'extremités from et to avec la norme la plus faible
 */
    Vec2d directionTo (Vec2d to) const; 
    /*!
 * @brief methode retournant la distance la plus faible entre un cercle et un point
 *
 * @param un cercle de depart, son vecteur position jouera le role du vecteur to de la méthode precedente
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return le vecteur d'extremités from et to avec la norme la plus faible
 */
    Vec2d directionTo (const CircularCollider& cercle) const ;
  /*!
 * @brief  methode retournant la longueur du vecteur torique calculé dans la méthode directionTo
 *
 * @param un vecteur to
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return le norme du vecteur 
 */
    double distanceTo (Vec2d to) const; 
     /*!
 * @brief  methode retournant la norme de la distance du centre d'un cercle à l'origine
 *
 * @param un cercle 
 * @note méthode déclarée const car elle ne doit pas changer les attributs de classe
 * @return le norme du vecteur calculé dans la méthode directionTo
 */
  double distanceTo (const CircularCollider& c) const; 
  	/*!
 * @brief methode ajoutant a la position de l'instance courante le vecteur dx 
 *
 * @param le vecteur dx à rajouter
 * @note utilisation de l'operateur +
 */
    void move (Vec2d dx) ; 
    

	///GESTION DES COLLISIONS
    bool isCircularColliderInside (CircularCollider other) const; // vérifie que other soit à l'intérieur de l'autre circularcollider
    bool isColliding (CircularCollider other) const; //vérifie si other est en collision avec l'autre circularcollider
    bool isPointInside (Vec2d point)const; //verifie si un point est à l'intérieur d'un circularcollider

	///GETTERS 
    Vec2d getPosition () const; //getter de position (centre d'un cercle)
    double getRadius () const; //getter de radius
    virtual void draw (sf::RenderTarget& targetWindow)  override; // dessin du circular collider


protected :

	///SETTERS 
    void setPosition (Vec2d a ); //setter de position
    void setRadius(double b); //setter de radius

private :

    ///ATTRIBUTS
    Vec2d position;
    double radius;

};

///SURCHARGE EXTERNE
// opérateur << d'affichage dans le terminal fonction externe , utilise la methode affiche
std::ostream& operator<<(std::ostream& out, const CircularCollider& circular_collider );

#endif

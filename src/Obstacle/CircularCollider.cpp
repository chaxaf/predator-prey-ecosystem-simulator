#include <iostream>
#include <string>
#include "CircularCollider.hpp"
#include <Application.hpp>
#include <fstream>
#include <Utility/Utility.hpp>

using namespace std;

//algorithme clamping qui incrémente + ou - la taille du monde aux valeurs fournies si celle-ci est inférieure à 0
void CircularCollider::Clamping () {
	
	double worldSize = getAppConfig().simulation_world_size;
	auto width  = worldSize; // largeur
	auto height = worldSize; // hauteur
	
	if (position.x < 0) {
		position.x += width; 
	}
	if (position.x > width) {
		position.x -= width;
	}
    if (position.y < 0) {
		position.y += height;
	}
	if (position.y > height) {
		position.y -= height;
	}
}
void CircularCollider::draw (sf::RenderTarget& targetWindow) {
targetWindow.draw(buildCircle (getPosition(), getRadius() , sf::Color::White)); 
}


CircularCollider::CircularCollider (Vec2d position_, double radius_) //constructeur de cercle (rayon et centre)
: position (position_) , radius (radius_ )
{
	if (radius < 0 ) 
	{
		throw string ("erreur rayon negatif");
	}
	Clamping ();
}
	
		
Vec2d CircularCollider::getPosition() const //getter de position
	{
		return position;
	}
double CircularCollider::getRadius() const // getter de radius
	{
		return radius;
	}
CircularCollider::CircularCollider(CircularCollider const& cercle) //constructeur de copie
: position (cercle.position) , radius (cercle.radius) {}
		
//operateur d'affectation =
CircularCollider CircularCollider::operator=(CircularCollider& copieCercle) const
	{
	
		copieCercle.position = position;
		copieCercle.radius = radius;
		return copieCercle;
	}


// methode calculant la distance la plus faible entre deux points to et from vecteur le plus court

// methode calculant la distance la plus faible entre deux points to et from vecteur le plus court
Vec2d CircularCollider::directionTo (Vec2d to) const
{
	double worldSize = getAppConfig().simulation_world_size;
	auto width  = worldSize; // largeur
	auto height = worldSize; // hauteur
	
	
	Vec2d vecteur(to);
	Vec2d tmp2;
	
	for (int i (-1); i<=1 ; ++i)  {	//on fait varier i et j entre -1 et 1 pour incrementer a to.x et to.y plus ou moins la taille de l'environnement afin de calculer la distance la plus faible 
		
		for (int j (-1); j<=1; ++j) {
			Vec2d tmp(i*width, j*height);
			tmp2 = to + tmp;
			if (distance(tmp2, this ->position ) < distance(vecteur, this -> position)) {
				vecteur = tmp2;}}}

return vecteur - this -> position;	
}

// methode retournant la distance la plus faible entre les centres de deux cercles
Vec2d CircularCollider::directionTo (const CircularCollider& c) const
{
	
	return directionTo(c.position);
}


// methode retournant la longueur du vecteur torique to
double CircularCollider::distanceTo (Vec2d to) const
{ 
	return directionTo(to).length();
}	

//methode retournant la distance entre les centres 
double CircularCollider::distanceTo (const CircularCollider& c) const
{
	return directionTo(c).length();
}

 // methode ajoutant a la position de l'instance courante le vecteur dx utilisant l'operateur +
void CircularCollider::move (Vec2d dx) 
{
	position = position + dx;
	Clamping();	
}

// methode ajoutant a la position de l'instance courante le vecteur dx utilisant l'operateur +=
Vec2d& CircularCollider::operator+=(Vec2d const& dx) 
{
	move(dx);
	Clamping();
	return position;
}

// vérifie que other soit à l'intérieur de l'autre circularcollider
bool CircularCollider::isCircularColliderInside (CircularCollider other) const
{
return ((radius >= other.getRadius()) && (distanceTo(other) <= (radius - other.getRadius())))  ;

}

//vérifie si other est en collision avec l'autre circularcollider
bool CircularCollider::isColliding (CircularCollider other) const
{
	
	return (distanceTo(other) <= (radius + other.getRadius()));
}

//verifie si un point est à l'intérieur d'un circularcollider
bool CircularCollider::isPointInside (Vec2d point) const
{
	return (distanceTo(point) <= radius ); 
}

bool CircularCollider::operator>(CircularCollider const& other) const //operateur > entre deux CircularCollider verifiant si other est à l'intérieur d'un autre CircularCollider
{
	return (isCircularColliderInside(other));
}

//operateur | verifiant si deux CircularCollider sont en collision
bool CircularCollider::operator|(CircularCollider const& other) const 
{
		return (isColliding(other));
}

//operateur > entre un point et un circularCollider vérifiant si le point est à l'intérieur du CircularCollider
bool CircularCollider::operator>(Vec2d point) const 
{
	return (isPointInside(point));
}


// affiche le message ci dessous (méthode publique définie pour coder l'opérateur << )
void CircularCollider::affiche (std::ostream& out ) const 
{
		out << "CircularCollider : position = (" << position.x << " , " << position.y << "), radius = " << radius << flush ;
}



// opérateur << d'affichage dans le terminal fonction externe , utilise la methode affiche
ostream& operator<<(ostream& out, const CircularCollider& circular_collider ) 
{ 
	circular_collider.affiche(out);
	return out;
}

void CircularCollider::setRadius (double a)
{
		radius = a;
}

void CircularCollider::setPosition (Vec2d b)
{
	position = b;
}		
	
		
		



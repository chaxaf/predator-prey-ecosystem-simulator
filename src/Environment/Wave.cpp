#include "Wave.hpp" 
#include <Utility/Constants.hpp>
#include <cmath>
#include <Utility/Utility.hpp>
#include <Application.hpp>
#include <Random/Uniform.hpp>
#include <Animal/Animal.hpp>

using namespace std;


//constructeur de vague
Wave::Wave (Vec2d origine_, double energy_, double rayon_, double mu_, double speed_)
	: CircularCollider (origine_, rayon_), energieInitiale (energy_), rayonInitial (rayon_), mu (mu_), 
	speed (speed_), energy (energieInitiale), tempsEcouleDepuisDebutOnde (sf::Time::Zero)
{
	ensembleArcs.push_back (arc (-PI, PI));
}


double Wave::getStandardSpeed () const
{
	return speed;
}

//getter d'energie
double Wave::getEnergy () const
{
	return energy;
}

//getter d'energie initiale
double Wave::getEnergieInitiale () const
{
	return energieInitiale;
}

//getter de rayon initial
double Wave::getRayonInitial () const
{
	return rayonInitial;
}

//getter de la constante mu
double Wave::getMu () const
{
	return mu;
}

double Wave::getIntensite () const
{
	return getEnergieInitiale() * exp (-getRadius() / getMu ()) / (2 * PI * getRadius());
}

void Wave::setEnergy (const double a) 
{
	energy = a;
}

void Wave::setIntensite (const double a)
{
	intensite = a;
}

//methode polymorphique qui update les attributs de la vague en fonction du temps dt
void Wave::update(const sf::Time& dt) 
{
	//update les attributs rayon, energie et intensite
	setRadius (getStandardSpeed() * tempsEcouleDepuisDebutOnde.asSeconds() + getRayonInitial()); 
	setEnergy (getEnergieInitiale() * exp ( - getRadius() / getMu ())); 
	
	tempsEcouleDepuisDebutOnde += dt; //incremente le compteur sur la "duree de vie" de la vague
}

//methode polymorphique dessinant la vague
void Wave::draw(sf::RenderTarget& targetWindow)
{
	for (auto arc_ : ensembleArcs)
	{
		Arc a = buildArc (arc_.first/DEG_TO_RAD, arc_.second/DEG_TO_RAD, getRadius(), getPosition(), sf::Color::Black , 
		0.f, getIntensite() * getAppConfig().wave_intensity_thickness_ratio);
		targetWindow.draw (a);
	}
}

//destructeur virtuel de vague car la classe contient des methodes virtuelles pures
Wave::~Wave () 
{}

void Wave::collision (CircularCollider* obstacle)
{
	for (auto& ondes : ensembleArcs)
	{	
		double angle ((obstacle-> getPosition() - getPosition()).angle());
		
		if ((isColliding(*obstacle) or isCircularColliderInside(*obstacle)) 
		and (angle>= ondes.first and angle<= ondes.second))
		{
			arc newArc (angle + std::atan2(getRadius() , getRadius() + obstacle->getRadius())/4, ondes.second);
			ondes.second = angle - std::atan2(getRadius(), getRadius() + obstacle -> getRadius())/4;
			
			ensembleArcs.push_back (newArc);
		}
	}
}

bool Wave::isPointOnWave (Vec2d point) const
{
	return ((isOnRadius(point)) or (isOnArc(point)));
	
}

bool Wave::isOnRadius(Vec2d point) const
{
	//pour plus tard distance ... see vec2d hpp
	//peut etre mieux distance(point, getPosition());
	double dist = (point-getPosition()).length(); //la distance entre le point et l'origine de l'onde
	return (isEqual(dist, getRadius(), getAppConfig().wave_on_wave_marging)); //tester si la distance entre dist et le radius est proche de la constante
}


//le point appartient a un des arcs de l'onde si l'angle entre le point et l'orgine de l'onde est contenu dans l'arc
bool Wave::isOnArc(Vec2d point) const
{

	double angle ((point-getPosition()).angle());
	double debut_arc;
	double fin_arc;
	
	for (auto arc_ : ensembleArcs)
	{
		debut_arc = arc_.first;
		fin_arc = arc_.second;
		//controler cette ligne
	if ((angle >= debut_arc) or (angle <= fin_arc))
	{
		return true; //si le point est dans l'arc la méthode rétourne true directement , sinon elle continue a iterer sur les elements de esnembleArcs
	}}
	
	return false;
}


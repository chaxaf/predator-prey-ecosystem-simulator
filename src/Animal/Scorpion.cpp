#include <iostream>
#include <Utility/Vec2d.hpp>
#include "Animal/Scorpion.hpp"
#include <Application.hpp>
#include <Random/Uniform.hpp>
#include <Utility/Utility.hpp>

using namespace std;

Scorpion::Scorpion(Vec2d position_, double niveauEnergie, bool sexe)
    : Animal (position_, getAppConfig().scorpion_size, niveauEnergie, sexe)
{}

// sexe tiré au hasard avec la fonction uniform, constructeur initialiser des nouveau-nes
Scorpion::Scorpion (Vec2d position_)
    : Animal(position_, getAppConfig().scorpion_size, getAppConfig().scorpion_energy_initial, (uniform(0, 1) == 0))
{}

//retourne la vitesse standard maximale du scorpion
double Scorpion::getStandardMaxSpeed() const
{
    return  getAppConfig().scorpion_max_speed;
}

//retourne la masse du scorpion
double Scorpion::getMass() const
{
    return getAppConfig().scorpion_mass;
}

//retourne la valeur constante de l'angle de vision (en radians) du scorpion
double Scorpion::getViewRange() const
{
    return getAppConfig().scorpion_view_range;
}

//accesseur qui retourne la valeur constante de la distance maximale pour le champ de vision
double Scorpion::getViewDistance() const
{
    return getAppConfig().scorpion_view_distance;
}

double Scorpion::getRandomWalkRadius() const
{
    return getAppConfig().scorpion_random_walk_radius;

}

double Scorpion::getRandomWalkDistance() const
{
    return getAppConfig().scorpion_random_walk_distance;

}

double Scorpion::getRandomWalkJitter() const
{
    return getAppConfig().scorpion_random_walk_jitter;
}

//methode dessinant un animal
void Scorpion::draw(sf::RenderTarget& targetWindow)
{
        Animal::draw(targetWindow);
        sf::Texture texture; 
        if (getAge() < fromDouble(getAppConfig().scorpion_min_age_mating))
        {
			texture = getAppTexture (getAppConfig().scorpion_baby_texture);
			setRadius( getAppConfig().scorpion_size / 1.5 );
		}
		else 
		{
			texture = getAppTexture (getAppConfig().scorpion_texture);
			setRadius( getAppConfig().scorpion_size);
		}
        auto image_to_draw(buildSprite(getPosition(),(getRadius()*2), texture, getRotation() / DEG_TO_RAD));
        targetWindow.draw(image_to_draw);
}



// methode returnant true si le scorpion this peut manger l'entité organique other
bool Scorpion::eatable(OrganicEntity const* entity) const
{
    return entity->eatableBy(this);
}

//double dispatch

bool Scorpion::eatableBy(Scorpion const* wolf) const
{
    return false;
}

bool Scorpion::eatableBy(Gerbil const* sheep) const
{
    return false;
}

bool Scorpion::eatableBy(Food const* food) const
{
    return false;
}

bool Scorpion::isDead () const
{
    return  ((getEnergyLevel() <= getAppConfig().animal_min_energy) or (getAge() >=  getAppConfig().scorpion_longevity));
}


double Scorpion::getEnergyLossFactor() const
{
    return  getAppConfig().scorpion_energy_loss_factor;
}

//double dispatch pour la reproduction des scorpions
bool Scorpion::matable(OrganicEntity const* other) const
{
    return (other->canMate(this) and (this!= other));
}
// un scorpion peut se reproduire seulement avec un aure scorpion de sexe opposé et
// seulement si il a assez energie, il est suffisament agé, il n'est pas enceinte ou entrain de mettre bas //EST ENCEINTE OU PAS PAS IMPLEMENTE
bool Scorpion::canMate(Scorpion const* scorpion) const
{
    double energie_min (0.0);
    if (isFemale()) {
        energie_min = getAppConfig().scorpion_energy_min_mating_female;
    } else {
        energie_min = getAppConfig().scorpion_energy_min_mating_male;
    }

    return (((scorpion->isFemale()) != (this->isFemale())) and (getEnergyLevel() >=  energie_min) and 
    (getAge() >= sf::seconds(getAppConfig().scorpion_min_age_mating)) and (not isPregnant()) and (getEtat() != Etat::MATING)
    and (getEtat() != Etat::GIVING_BIRTH));


}

bool Scorpion::canMate(Gerbil const* gerbil) const
{
    return false;
}

bool Scorpion::canMate(Food const* food) const
{
    return false;
}

Scorpion::~Scorpion ()
{}


void Scorpion::meet (OrganicEntity* entity) 
{
	setTimeMating(Animal::fromDouble(getAppConfig().animal_mating_time));
	entity->meetDispatch (this);
	setEtat(Etat::MATING);
}

void Scorpion::meetDispatch (Scorpion* scorpion) 
{
	if (isFemale())
		
		{
			setNumberChildren(uniform (getAppConfig().scorpion_min_children, getAppConfig().scorpion_max_children));
			EnergyLoss( getNumberChildren() * getAppConfig().scorpion_energy_loss_female_per_child);
			setPregnant(true);
			setTimeGestation(Animal::fromDouble(getAppConfig().scorpion_gestation_time));
		
		}	else
				
		{
			EnergyLoss(getAppConfig().scorpion_energy_loss_mating_male);
		
		}	
}

void Scorpion::meetDispatch (Gerbil* food) 
{}

void Scorpion::meetDispatch (Food* food) 
{}


void Scorpion::give_birth (unsigned int nbEnfants) 
{ 
	setEtat(Etat::GIVING_BIRTH);
	setTimeGivingBirth(fromDouble(getAppConfig().animal_delivery_time));
	for (size_t i(0); i<= nbEnfants; i++) 
	{
		OrganicEntity* entity = new Scorpion (getPosition());
		getAppEnv().Environment::addEntity (entity);
	}
	setPregnant(false);
}

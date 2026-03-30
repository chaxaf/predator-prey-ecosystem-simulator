#include <iostream>
#include "Animal/Gerbil.hpp"
#include <Application.hpp>
#include <Random/Uniform.hpp>
#include <Utility/Utility.hpp>

using namespace std;

Gerbil::Gerbil (Vec2d position_, double niveauEnergie, bool sexe)
    : Animal (position_, getAppConfig().gerbil_size, niveauEnergie, sexe)
{}

// sexe tiré au hasard avec la fonction uniform, constructeur initialiser des nouveau-nes
Gerbil::Gerbil (Vec2d position_)
    : Animal(position_, getAppConfig().gerbil_size, getAppConfig().gerbil_energy_initial, (uniform(0, 1) == 0))
{}

double Gerbil::getStandardMaxSpeed() const
{
    return  getAppConfig().gerbil_max_speed;
}

double Gerbil::getMass() const
{
    return getAppConfig().gerbil_mass;
}

double Gerbil::getViewRange() const
{
    return getAppConfig().gerbil_view_range;
}

double Gerbil::getViewDistance() const
{
    return getAppConfig().gerbil_view_distance;
}

double Gerbil::getRandomWalkRadius() const
{
    return getAppConfig().gerbil_random_walk_radius;

}

double Gerbil::getRandomWalkDistance() const
{
    return getAppConfig().gerbil_random_walk_distance;

}

double Gerbil::getRandomWalkJitter() const
{
    return getAppConfig().gerbil_random_walk_jitter;
}
//methode dessinant une gerbille
void Gerbil::draw(sf::RenderTarget& targetWindow) 
{
        Animal::draw(targetWindow);
        sf::Texture texture;
        if (isFemale()) {
			if (getAge() < fromDouble(getAppConfig().gerbil_min_age_mating)) 
			{
				texture = getAppTexture (getAppConfig().gerbil_texture_baby_female);
				setRadius( getAppConfig().gerbil_size / 1.5 );
			}
			else 
			{
				texture = getAppTexture (getAppConfig().gerbil_texture_female);
				setRadius( getAppConfig().gerbil_size);
				
			}
        } else {
			if (getAge() < fromDouble(getAppConfig().gerbil_min_age_mating)) 
			{
				texture = getAppTexture (getAppConfig().gerbil_texture_baby_male);
				setRadius (getAppConfig().gerbil_size/1.5);
			}
			else 
			{
				texture = getAppTexture(getAppConfig().gerbil_texture_male);
				setRadius( getAppConfig().gerbil_size);
			}
        }
        auto image_to_draw(buildSprite(getPosition(),(getRadius()*2), texture, getRotation() / DEG_TO_RAD));

        targetWindow.draw(image_to_draw);
}



// methode returnant true si la gerbille courant this peut manger ou pas l'entité organique other
bool Gerbil::eatable(OrganicEntity const* entity) const
{
    return entity->eatableBy(this);

}

//la gerbille peut se faire manger seulement par des scorpions
bool Gerbil::eatableBy(Scorpion const* wolf) const
{
    return true;
}

bool Gerbil::eatableBy(Gerbil const* sheep) const
{
    return false;
}

bool Gerbil::eatableBy(Food const* food) const
{
    return false;
}


bool Gerbil::isDead () const
{
    return ((getEnergyLevel() <= getAppConfig().animal_min_energy) or (getAge() >= getAppConfig().gerbil_longevity));
}


double Gerbil::getEnergyLossFactor() const
{
    return getAppConfig().gerbil_energy_loss_factor;
}

//double dispatch pour la reproduction des gerbilles
bool Gerbil::matable(OrganicEntity const* other) const
{
    return ((other->canMate(this)) and (this!= other));
}

bool Gerbil::canMate(Scorpion const* scorpion) const
{
    return false;
}

// une gerbille peut se reproduire seulement avec une gerbille de sexe opposé et
// seulement si elle a assez energie, elle est suffisament agé, elle n'est pas enceinte ou entrain de mettre bas
bool Gerbil::canMate(Gerbil const* gerbil) const
{
    double energie_min (0.0);
    if (isFemale()) {

        energie_min = getAppConfig().gerbil_energy_min_mating_female;
    } else {
        energie_min = getAppConfig().gerbil_energy_min_mating_male;
    }

    return ((gerbil->isFemale() != this->isFemale()) and (getEnergyLevel() >= energie_min) and
    (getAge() >= sf::seconds(getAppConfig().gerbil_min_age_mating)) and (not isPregnant()) and (getEtat() != Etat::MATING)
    and (getEtat() != Etat::GIVING_BIRTH));


}

bool Gerbil::canMate(Food const* food) const
{
    return false;
}


Gerbil::~Gerbil()
{}

void Gerbil::meet (OrganicEntity* entity) 
{	
	setTimeMating(Animal::fromDouble(getAppConfig().animal_mating_time));
	entity->meetDispatch (this);
	setEtat(Etat::MATING);
}

void Gerbil::meetDispatch (Scorpion* scorpion) 
{}

void Gerbil::meetDispatch (Gerbil* gerbil) 
{
	if (isFemale()) 
	{
			setNumberChildren(uniform (getAppConfig().gerbil_min_children, getAppConfig().gerbil_max_children));
			EnergyLoss (getNumberChildren() * getAppConfig().gerbil_energy_loss_female_per_child);
			setPregnant(true);

			
			setTimeGestation(Animal::fromDouble(getAppConfig().gerbil_gestation_time));
		}  else{
			EnergyLoss(getAppConfig().gerbil_energy_loss_mating_male);
		}	
	 
}

void Gerbil::meetDispatch (Food* food) 
{}


void Gerbil::give_birth (unsigned int nbEnfants) 
{
	setEtat(Etat::GIVING_BIRTH);
	setTimeGivingBirth(fromDouble(getAppConfig().animal_delivery_time));
	for (size_t i(0); i<= nbEnfants; i++) 
	{
		OrganicEntity* entity = new Gerbil (getPosition());
		getAppEnv().Environment::addEntity (entity);
		/*while (this != nullptr && entity->age < fromDouble(getAppConfig().gerbil_min_age_mating))  faire que les petits restent avec la mere appeler update attributs??*/
			
	}
	setPregnant(false);
}


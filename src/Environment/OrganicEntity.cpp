#include <iostream>
#include <Utility/Vec2d.hpp>
#include "Environment/OrganicEntity.hpp"
#include <SFML/Graphics.hpp>
#include <Application.hpp>


using namespace std;

//constructeur d'une entité organique
OrganicEntity::OrganicEntity (Vec2d position, double taille, double niveauEnergie)
    : CircularCollider (position, (taille/2)), energyLevel (niveauEnergie), age (sf::Time::Zero)
{}

bool OrganicEntity::isDead () const
{
    return ((energyLevel <= getAppConfig().animal_min_energy) or (age >= sf::seconds(1E9)));
}

OrganicEntity::~OrganicEntity()
{}

void OrganicEntity::Viellissement(const sf::Time& dt)
{
	age -= dt;
}
double OrganicEntity::getEnergyLevel() const
{
    return energyLevel;
}

sf::Time OrganicEntity::getAge() const
{
	return age;
}

void OrganicEntity::setEnergyLevel (double newEnergy)
{
	energyLevel = newEnergy;
}
void OrganicEntity::EnergyLoss (double energyLost)
{
	energyLevel -= energyLost;
}
void OrganicEntity::EnergyGain (double energyGained)
{
	energyLevel += energyGained;
}

void OrganicEntity::update(const sf::Time& dt)
{
        Viellissement(dt);
}







#include <iostream>
#include "Environment/FoodGenerator.hpp"
#include "Food.hpp"
#include <Random/Normal.hpp>
#include <Application.hpp>
#include "Environment/OrganicEntity.hpp"
#include "Environment/Environment.hpp"
#include <Random/Normal.hpp>

using namespace std;


FoodGenerator::FoodGenerator() // constructeur par defaut qui initialise le temps a zero
    :time (sf::Time::Zero)
{}

// methode qui fait ecoluer le compteur du temps
void FoodGenerator::update (const sf::Time& dt)
{
    time += dt;
    if (time >= sf::seconds(getAppConfig().food_generator_delta)) {
        time = (sf::Time::Zero);
        Vec2d position (normal( getAppConfig().simulation_world_size/2,
                                (getAppConfig().simulation_world_size/4 * getAppConfig().simulation_world_size/4)),
                        normal(getAppConfig().simulation_world_size/2,
                               (getAppConfig().simulation_world_size/4 * getAppConfig().simulation_world_size/4)));
        //ajouter à l'environnement une source de nourriture
        Food* newFood = new Food(position);
        getAppEnv().addEntity(newFood);

    }
}

FoodGenerator::~FoodGenerator()
{
	}

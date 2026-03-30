#include <iostream>
#include "Environment/Food.hpp"
#include "Environment/OrganicEntity.hpp"
#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <Utility/Utility.hpp>

#include "Animal/Gerbil.hpp"
#include "Animal/Scorpion.hpp"

using namespace std;

//constructeur d'une entité organique
Food::Food (Vec2d const& position)
    : OrganicEntity(position, getAppConfig().food_size, getAppConfig().food_energy)
{}

void Food::draw(sf::RenderTarget& targetWindow) 
{
        if (isDebugOn ()) {
            CircularCollider::draw(targetWindow);
        }


        sf::Texture& texture = getAppTexture(getAppConfig().food_texture);
        auto image_to_draw(buildSprite(getPosition(),(getRadius()*2), texture));
        targetWindow.draw(image_to_draw);
}

void Food::update (const sf::Time& dt)
{

}



// methode returnant true si food this peut manger l'entité organique other
bool Food::eatable(OrganicEntity const* entity) const
{
    return (entity->eatableBy(this));
}

//double dispatch
bool Food::eatableBy(Scorpion const* wolf) const
{
    return false;
}
bool Food::eatableBy(Gerbil const* sheep) const
{
    return true;
}

bool Food::eatableBy(Food const* food) const
{
    return false;
}

bool Food::matable(OrganicEntity const* other) const
{
    return other->canMate(this);
}

bool Food::canMate(Scorpion const* scorpion) const
{
    return false;
}

bool Food::canMate(Gerbil const* gerbil) const
{
    return false;
}

// un food peut se reproduire seulement avec un autre food (aucune condition?)
bool Food::canMate(Food const* food) const
{
    return true;

}

void Food::meet (OrganicEntity* entity) 
{
	entity->meetDispatch (this);
}

void Food::meetDispatch (Scorpion* scorpion)
{}

void Food::meetDispatch (Gerbil* gerbil)
{}

void Food::meetDispatch (Food* food)
{}

Food::~Food ()
{
}


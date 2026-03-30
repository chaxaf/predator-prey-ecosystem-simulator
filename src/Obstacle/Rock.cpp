#include "Rock.hpp"
#include <Random/Uniform.hpp>
#include <algorithm> 
#include <Application.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>

using namespace std;

Rock::Rock (Vec2d position_)
: CircularCollider (position_, std::max (1, uniform (getAppConfig().simulation_world_size/50, 2*getAppConfig().simulation_world_size/50))),
orientation (uniform(-PI, PI))
{}

void Rock::draw (sf::RenderTarget& targetWindow) 
{
	sf::Texture& texture = getAppTexture (getAppConfig().rock_texture);
    targetWindow.draw(buildSprite(getPosition(),(getRadius()*2), texture));
   
}

Rock::~Rock () 
{}

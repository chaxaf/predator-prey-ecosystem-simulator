#include "WaveGerbil.hpp"
#include <Application.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include "Environment/Wave.hpp"

using namespace std;

WaveGerbil::WaveGerbil (Vec2d position_ , double niveauEnergie, bool sexe) 
: Gerbil (position_, niveauEnergie, sexe), compteur (sf::Time::Zero)
{ 
	/*Wave (position_, getAppConfig().wave_default_energy,
getAppConfig().wave_default_radius, getAppConfig().wave_default_mu, getAppConfig().wave_default_speed);*/

}

WaveGerbil::WaveGerbil (Vec2d position_)
    : Gerbil (position_)
{}

WaveGerbil::~WaveGerbil ()
{}

void WaveGerbil::update (const sf::Time& dt)
{
	Gerbil::update(dt);
	compteur += dt;
	if (compteur.asSeconds() >= (1.0/getAppConfig().wave_gerbil_frequency) /*&& not(isDead())*/) 
	{
		Wave* wave = new Wave(getPosition(),
                          getAppConfig().wave_default_energy,
                          getAppConfig().wave_default_radius,
                          getAppConfig().wave_default_mu,
                          getAppConfig().wave_default_speed);
		getAppEnv().addWave(wave);
		compteur = sf::Time::Zero;
	}
	
}

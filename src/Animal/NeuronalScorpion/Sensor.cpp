
#include "Animal/NeuronalScorpion/Sensor.hpp"
#include "Environment/Wave.hpp"
#include "Animal/NeuronalScorpion/NeuronalScorpion.hpp"
#include <Utility/Utility.hpp>

using namespace std;
	
Sensor::Sensor (NeuronalScorpion* owner, size_t i)
:scorpion(owner), index(i), tempsActivation (sf::Time::Zero)
{
	initialiseSensor();
}

void Sensor::initialiseSensor()
{
	score = 0.0;
	inhibitor = 0.0;
	isActive = false;
}
	 
double Sensor::getScore() const 
{
	return score;
}

bool Sensor::isActivated() const
{
	return isActive;
}

void Sensor::incrementInhibition(double ToAdd)
{
	inhibitor += ToAdd;
}

size_t Sensor::getIndex() const
{
	return index;
}

///ACTIVATION ET INHIBITION DES SENSEURS
void Sensor::activer ()
{
	double intensiteTotale = (getAppEnv().getSumOfIntensities(scorpion->getPositionOfSensor(index))); 
	isActive = (intensiteTotale > getAppConfig().sensor_intensity_threshold);
	if (isActivated())
	{
		tempsActivation = sf::seconds(getAppConfig().sensor_activation_duration);
	}
}


void Sensor::plafonnerInhibitor()
{
	if (inhibitor < 0.0)
	{
		inhibitor = 0.0;
	}
	
	if (inhibitor > getAppConfig().sensor_inhibition_max)
	{
		inhibitor = getAppConfig().sensor_inhibition_max;
	}
	
}

void Sensor::TempererScore()
{
	score += 2.0*(1.0 - inhibitor);
}

void Sensor::update(const sf::Time& dt) 
{
	plafonnerInhibitor();
	
	if (tempsActivation <= sf::Time::Zero)
	{	
		initialiseSensor ();
		activer();
	}

	if (isActivated())
	{	
		tempsActivation -= dt;
		//mis a jour du score de this
		TempererScore();
		//augmentation de degré d'inhibition des senseurs connectés a this
		scorpion->InhibitionSenseursConnectes();
		scorpion->activate(); 
	}
	/*cout << "score : " << score << endl;
	cout << "isActivated : " << isActivated() << endl;
	cout << " inhibition : " << inhibitor << endl;
	cout << "temps : " << tempsActivation.asSeconds() << endl;*/
}

///TEST 26 DESSIN D'UN SENSEUR

sf::Color Sensor::getColor() const
{
	if (isActivated() && (inhibitor > 0.2))
	{
		return sf::Color::Magenta;
	} else if ((not(isActivated())) && ((inhibitor > 0.2)))
	{
		return sf::Color::Blue;
	} else if (isActivated() && (inhibitor < 0.2))
	{
		return sf::Color::Red; 
	} else 
	{
		return sf::Color::Green; 
	}
	
}


void Sensor::draw(sf::RenderTarget& targetWindow)
{
	targetWindow.draw(buildCircle ((scorpion->getPositionOfSensor(index)), (scorpion->getRadius()/6), (getColor())));
}


Sensor::~Sensor()
{}

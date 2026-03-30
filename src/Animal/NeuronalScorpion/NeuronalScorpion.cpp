#include "Animal/NeuronalScorpion/NeuronalScorpion.hpp"
#include <Utility/Utility.hpp>

using namespace std;


NeuronalScorpion::NeuronalScorpion (Vec2d position_)
:Scorpion (position_) , estimationDirection (0.0, 0.0), time_idle (sf::Time::Zero), time_moving (sf::Time::Zero), 
etat (Etat::WANDERING), scorpionActive (false)
{
	
	// array des angles utilisé pour initialiser la map des angles lié aux senseurs
	array<double, 8> angles_ = {18, 54, 90, 140, -140, -90, -54, -18}; 
	//comme on n'a pas plus besoin de cet element, on l'initialise dans sa porté et pas comme attribut de classe
	
	// initialisation des angles : l'angle lié au i-ème senseur est initialisé au i-ème angle de l'array angles_
	for (size_t i(0); i < sensors.size(); ++i)
	{
		sensors[i] = new Sensor (this, i);
		angles[sensors[i]] = angles_[i]; 
	}

}

NeuronalScorpion::NeuronalScorpion (Vec2d position_, double niveauEnergie, bool sexe)
:Scorpion (position_, niveauEnergie, sexe) , estimationDirection (0.0, 0.0), time_idle (sf::Time::Zero), time_moving (sf::Time::Zero), 
etat (Etat::WANDERING), scorpionActive(false)
{
	// array des angles utilisé pour initialiser la map des angles lié aux senseurs
	array<double, 8> angles_ = {18, 54, 90, 140, -140, -90, -54, -18}; 
	//comme on n'a pas plus besoin de cet element, on l'initialise dans sa porté et pas comme attribut de classe
	
	// initialisation des angles : l'angle lié au i-ème senseur est initialisé au i-ème angle de l'array angles_
	for (size_t i(0); i < sensors.size(); ++i)
	{
		sensors[i] = new Sensor (this, i);
		angles[sensors[i]] = angles_[i]; 
	}
}

Vec2d NeuronalScorpion::getPositionOfSensor (size_t i)
{
	return (ConvertToGlobalCoord(Vec2d(((cos((angles[sensors[i]])*DEG_TO_RAD))*getAppConfig().scorpion_sensor_radius), ((sin(((angles[sensors[i]])*DEG_TO_RAD)))*getAppConfig().scorpion_sensor_radius))));
}

void NeuronalScorpion::SetEstimationDirection()
{
	Vec2d dir{0.0 , 0.0};
	for (auto& sens : sensors)
	{
		if(sens != nullptr) {
		double angle ((angles[sens]*DEG_TO_RAD) + getRotation()); //l'angle est donné par la somme de l'angle du senseur et l'angle direction de l'animale
		dir += (((getRadius()/4)*(Vec2d(cos(angle), sin(angle))))*(sens->getScore()));	
	 }}
	estimationDirection = dir;
}

double NeuronalScorpion::ScoreEstimation () 
{
	return estimationDirection.length();
}
NeuronalScorpion::Etat NeuronalScorpion::getEtat()
{
	return etat; 
}

void NeuronalScorpion::update (const sf::Time& dt)
{
	//SetEstimationDirection();
	updateSensors(dt);	
	
	/*if (time_idle > sf::seconds(getAppConfig().sensor_activation_duration)) ///PROBLEME
	{
			etat = Etat::WANDERING;
			SetEstimationDirection();
			for (auto& sensor : sensors) 
			{
				sensor->initialiseSensor();
			}
	}*/
		
	UpdateState(dt);
	Vec2d force;

	
        switch (etat) {
			
			case Etat::WANDERING :
            force = randomWalk() - getPosition();
            SetEstimationDirection();
            break;
			case Etat::TARGET_IN_SIGHT :
            force = getForceAttraction();
            SetEstimationDirection();
            break;
			case Etat::MOVING :
			time_moving+= dt;
			force = getForceAttractionMoving();
			SetEstimationDirection();
			break;
			case  Etat::IDLE :
            force = {(0.0) , (0.0)};
			time_idle+=dt;
			SetEstimationDirection();
            break;
            default :
            force = {(0.0) , (0.0)};
        }

	 updateAttributs(force, dt); 


}

void NeuronalScorpion::UpdateState (const sf::Time& dt)
{
	
	analyzeEnvironment();
	 
	if (getNourritureProche() != nullptr)
	  {
		  etat =  Etat::TARGET_IN_SIGHT;
	  }
	  
	else if (etat == Etat::IDLE) {
	  
		 //SetEstimationDirection();
		 double score_ = ScoreEstimation();
		
		 if (score_ >= getAppConfig().scorpion_minimal_score_for_action) 
		  {
			  etat = Etat::MOVING;
		  }
		 if (time_idle > getAppConfig().neuronal_scorpion_time_idle)
		  {
			  etat = Etat::WANDERING;
		  }
		}
	
	else if (etat == Etat::MOVING) {
		if (time_moving > getAppConfig().neuronal_scorpion_time_moving) {
			etat = Etat::IDLE;
		}
	}
		
	else if (etat == Etat::WANDERING) {
		  for (auto& sensor : sensors)
	  {
		  if ((sensor != nullptr) and (sensor->isActivated()))
		  {
			etat = Etat::IDLE; 
		  } 
	  }
  }
		
	 else if (etat == Etat::TARGET_IN_SIGHT) {
		  etat = Etat::IDLE;
	}
		
		gestionHorologes();
}

void NeuronalScorpion::gestionHorologes ()
{
	if (time_moving > getAppConfig().neuronal_scorpion_time_moving)
	{
		//reinitialiser le compteur
		time_moving = sf::Time::Zero;
					
		//le scorpion oublie les ondes d'avant 
		for (auto& sensor_ : sensors)
		{
			if(sensor_ != nullptr) 
			{
			 sensor_->initialiseSensor();  //chaque senseur est donc reinitialisé
			}
		}
		SetEstimationDirection();
	}
			
	if (time_idle > getAppConfig().neuronal_scorpion_time_idle) 
	{
		//reinitialiser le compteur		
		time_idle = sf::Time::Zero;
	}
	
}

void NeuronalScorpion::updateSensors(const sf::Time& dt)
{
	for (auto& sens: sensors)
	{
		if(sens != nullptr) {
		//update des senseur
		sens->update(dt);
		}
	}
}

void NeuronalScorpion::InhibitionSenseursConnectes()
{
	for (auto& sens : sensors) {
		for (size_t j(3); j <=5; ++j)
		{
			size_t i = (sens->getIndex()+j) % 8; 
			(sensors[i])->incrementInhibition((sens->getScore())*(getAppConfig().sensor_inhibition_factor)); 	
		} }
}


Vec2d NeuronalScorpion::getForceAttractionMoving()
{
	Vec2d f;
	double angleRotation = estimationDirection.angle(); 
	if (angleRotation > getAppConfig().scorpion_rotation_angle_precision )
	{
		//faire faire cette rotation et calculer f comme une force de rallentissement
		setRotation(angleRotation);    
		f = getForceAttractionWhenFeeding();  
	} else {
		//faire avancer le scorpion tout droit d'un pas donne p (dans notre cas p = 10)
		//f est donc une force d'attraction vers cible a (p,0) du repere locale 
		Vec2d cible (ConvertToGlobalCoord(Vec2d {10.0, 0.0}));
		setTargetPosition(cible);
		f = getForceAttraction();
	}
	
	return f;
	
}

void NeuronalScorpion::activate() /// ceci est bizarre car quand on appelle cette methode on sait deja que le senseur est activé donc pas besoin de le reverifier lol
{
	scorpionActive = true;
}

///DESSIN DU SCORPION
//methode convertissant en strings les états pour pouvoir les afficher dans le mode debugging
string NeuronalScorpion::fromEnumToString(NeuronalScorpion::Etat etat)
{
    switch (etat)

    {
    case Etat::IDLE :
        return "IDLE";
        break;
    case Etat::WANDERING :
        return "WANDERING" ;
        break;
    case Etat::TARGET_IN_SIGHT :
        return "TARGET_IN_SIGHT";
        break;
    case Etat::MOVING :
        return "MOVING";
        break;
	default :
	cout << " Erreur etat inconnu" << endl;
	exit(1);
    }
}


//methode renvoyant le texte à afficher dans le mode debugging
string NeuronalScorpion::texteAAfficher (NeuronalScorpion::Etat etat, bool sexe, double energyLevel)
{

    string sexe_; //cherche le sexe de l'animal
    if (sexe) {
        sexe_ = "female";
    } else {
        sexe_ = "male" ;
    }

    //concaténation des différents strings pour n'en avoir plus qu'un seul à afficher
    //(on aurait pu faire autrement en appelant trois fois la méthode dans draw et en affichant les trois strings séparémment ce qui aurait permis de centrer le texte)
    string chaine1 (fromEnumToString (etat));
    chaine1 += "\n";
    chaine1 += "\n";
    chaine1 += sexe_;
    chaine1 += "\n";
    chaine1 += "\n";
    chaine1 += to_nice_string (energyLevel);

    return (chaine1);

}


sf::Color NeuronalScorpion::stateColor ()
{
    NeuronalScorpion::Etat state_ (getEtat());
    switch (state_) {
    default :
        return getAppConfig().debug_text_color;
    }
}
void NeuronalScorpion::drawSensors (sf::RenderTarget& targetWindow)
{
	for (auto& sens: sensors)
	{
		//dessin de chaque senseur
		sens->draw(targetWindow);
	}
}

//methode dessinant le neuronal scorpion 
void NeuronalScorpion::draw(sf::RenderTarget& targetWindow) 
{
    //affichage du scorpion 
		if (isDebugOn())
		{
			sf::Texture& texture = getAppTexture (getAppConfig().scorpion_texture);
			auto image_to_draw(buildSprite(getPosition(),(getRadius()*2), texture, getRotation() / DEG_TO_RAD));
			targetWindow.draw(image_to_draw);
			drawVision (targetWindow);
            targetWindow.draw(buildText(texteAAfficher (getEtat(), isFemale(), getEnergyLevel()),
                                        getPosition()+ getDirection().normalised()*getRandomWalkDistance() ,
                                        getAppFont(),
                                        getAppConfig().default_debug_text_size,
                                        stateColor(),
                                        getRotation() / DEG_TO_RAD + 90));
            drawSensors(targetWindow);		
			
		} else {
			Scorpion::draw(targetWindow);
			//si on n'est pas en mode "debugging" alors le scorpion est affiché "normalement" -> appelle a la méthode draw de Scorpion
       }
}

NeuronalScorpion::~NeuronalScorpion()
{
	for (auto& sens : sensors)
	{
		delete sens;
		sens = nullptr;
	}
}

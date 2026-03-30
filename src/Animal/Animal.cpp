#include "Animal/Animal.hpp"
#include <Application.hpp>
#include <Utility/Constants.hpp>
#include <Utility/Utility.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <Random/Uniform.hpp>
#include <chrono>
#include "NeuronalScorpion/WaveGerbil.hpp"
using namespace std;


Animal::Animal (Vec2d position_, double taille, double niveauEnergie, bool sexe_)
    : OrganicEntity(position_, taille, niveauEnergie), speed (0.0),  targetPosition (Vec2d(1.0, 0.0)), 
     sexe(sexe_), pregnant(false), tempsPause (sf::Time::Zero), tempsPauseMating (sf::Time::Zero), tempsDeGestation (sf::Time::Zero)
{}

// manipulateur qui modifie la valeur de la position de la cible, en lui affectant la valeur newPosition
void Animal::setTargetPosition(Vec2d newPosition)
{
    targetPosition = newPosition;
}

// methode calculant le vecteur vitesse de l'animal donnee par le produit de la direction et la norme de la vitesse
Vec2d Animal::getSpeedVector() const
{
    return (direction*speed); // utilisation de la surcharge de l'operateur * du Vec2d
}

    double Animal::getMaxSpeed ()
{

    double speed;

    Etat etat (Etat::FOOD_IN_SIGHT);

    switch (etat) {
    case Etat::FOOD_IN_SIGHT :
        speed = getStandardMaxSpeed() * 2;
        break;
    case Etat::MATE_IN_SIGHT :
        speed = getStandardMaxSpeed() * 3;
        break;
    case Etat::RUNNING_AWAY :
        speed = getStandardMaxSpeed() * 4;
        break;
    case Etat::FEEDING :
        speed = 0.0;
        break;
    default :
        speed = getStandardMaxSpeed();
    }
    // si l'energie de l'animal est en dessous d'un seuil critique, il se deplace plus lentement
    if (getEnergyLevel() <= 45) {
        speed *= 0.5;
    }
    return speed;
}

// methode qui retourne la force d'attraction
Vec2d Animal::getForceAttraction ()
{

    valeurDeceleration deceleration (moyenne);
    Vec2d toTarget (targetPosition - getPosition()); //position de la cible - position de l'animal
    double speed_ ;

    Vec2d nul (0,0);

    if (toTarget == nul) {
        return nul;
    }

    else {

        if ((toTarget.length()/(deceleration/10.0)) < getMaxSpeed())

        {
            speed_ = (toTarget.length()/(deceleration/10.0));
        }

        else

        {
            speed_ = getMaxSpeed();
        }

        Vec2d targetSpeed ((toTarget/toTarget.length())*(speed_)); // vitesse que l'animal souhaite avoir vers la cible
        return targetSpeed - getSpeedVector();
    }
}

//methode qui retourne la force d'attraction lors de l'état de fuite
Vec2d Animal::getForceAttractionFuite()

{
    int delta1 (1000); // coefficient d'amplification de fuite
    double delta2 (1.2); // coefficient >1, tenante en compte l'impact de la distance
    Vec2d dir {(0.0),(0.0)};
    Vec2d force {(0.0),(0.0)};
       
       for (size_t i(0); i < listeDePredateurs.size() ; ++i) 
       {
			dir = ((listeDePredateurs[i]->getPosition()) -(this->getPosition()));
            force +=((-1)*((delta1*dir)/pow((dir.length()), delta2)));
        }
    
    return force;
}

//methode qui analyse l'environnement et mets a jour les attributs cible la plus proche, mate le plus proche et la liste de prédateurs
void Animal::analyzeEnvironment ()
{

    vector <OrganicEntity*> liste (getAppEnv().getEntitiesInSightForAnimal (this)); //liste d'entités organiques visibles par l'animal

    //vide les attributs pour mettre a jour sans qu'il y ait de "restes"
    nourritureProche = nullptr;
    mateProche = nullptr;

    double distanceMin1 (getViewDistance()); //distance maximale à laquelle un animal peut voir une entité organique
    double distanceMin2 (getViewDistance());

    if (!liste.empty()) { //si la liste est vide, alors la méthode ne fait rien et les attributs restent initialisés a nullptr

        for (auto& entity : liste) {

            if (this->eatable(entity) and distanceTo(entity->getPosition()) < distanceMin1) { //trouve la nourriture la plus proche et l'affecte à l'attribut nourritureProche
                distanceMin1 = distanceTo(entity->getPosition()) ;
                nourritureProche = entity ;
            }

            if (this->matable(entity) and distanceTo (entity->getPosition()) < distanceMin2) { //trouve le mate le plus proche et l'affecte à l'attribut mateProche
                distanceMin2 = distanceTo(entity->getPosition());
                mateProche = entity ;
            }

            if (entity->eatable(this)) { //trouve tous les prédateurs en vue et les ajoute dans la liste de prédateurs
                listeDePredateurs.push_back (entity);   
            }
        }
    }
}

void Animal::UpdateState (const sf::Time& dt)
{
	listeDePredateurs.clear();

    analyzeEnvironment ();
    
//l'animal est en mode RUNNING_AWAY tant qu'il y a un predatuer en vue
    if ((listeDePredateurs.size()) > 0)
	{
		setEtat(Etat::RUNNING_AWAY);
    }
	else if ((tempsDeGestation <= sf::Time::Zero) && (pregnant==true)) 

		{
			give_birth (nbEnfants);
			return;
		}


    //update la reproduction à mettre avant la consommation de nourriture car plus important pour l'animal
   else if ((mateProche != nullptr) && (tempsPauseMating <= sf::Time::Zero) && (pregnant == false) 
    && (tempsPauseGivingBirth <= sf::Time::Zero))

    	{
    		if (this->isColliding (*mateProche) and matable(mateProche) and mateProche->matable(this) ) //si lanimal est en collision avec le mate le plus proche -> état mating et reproduction
    		{
    			meet (mateProche);
    			mateProche->meet(this);
    		}
    		else
    		{
    			setEtat(Etat::MATE_IN_SIGHT);
    		}
    	}


    else if (nourritureProche != nullptr)

    {
        if (this-> isColliding (*nourritureProche) ) 	//si l'animal est en collision avec la nourriture la plus proche il passe dans l'état feeding
          { 
			EnergyGain(0.7*(nourritureProche->getEnergyLevel()));//l'animal gagne de l'énergie
            nourritureProche->setEnergyLevel(0.0); //la nourriture perd toute son énergie

            setEtat(Etat::FEEDING);
            tempsPause= fromDouble(getAppConfig().animal_feed_time);
            // si l'animal est en mode feeding, il fait une "pause" avant de passer a l'etat wandering
        } 
        else 
        {
            targetPosition = nourritureProche->getPosition();	 //sinon il passe dans l'état food in sight
            setEtat(Etat::FOOD_IN_SIGHT);
        }
    }


    else { //si aucune de ces conditions ne sont réunies l'animal passe dans l'état wandering / marche aléatoire

        setEtat(Etat::WANDERING);
    }

}

// methode permettant a l'animale de se deplacer et qui calcule la position et la vitesse de l'automate au bout de l'ecoulement du pas d'un intervalle de temps dt
void Animal::update(const sf::Time& dt)
{
       Vec2d force;
       UpdateState (dt);
		
	   tempsDeGestation -= dt;
       tempsPause -= dt;
       tempsPauseMating -= dt;
       tempsPauseGivingBirth -= dt;
       
       
        switch (etat_) {
		  
			
        case Etat::FOOD_IN_SIGHT :
        if (isColliding(*nourritureProche)) {
            force = getForceAttractionWhenFeeding(); 
			if(isEqual(speed, 0.0)) 
			{
				force = {(0.0) , (0.0)};
			}} else {
				force = getForceAttraction();
			}
            break;
        case Etat::WANDERING :
            force = randomWalk() - getPosition();
            break;
		case Etat::RUNNING_AWAY :
            force = getForceAttractionFuite();
            break;
        case Etat::MATE_IN_SIGHT :
			force = getForceAttraction();
			break;
   
        default :
            force = {(0.0) , (0.0)};
        }

        //temps de digestion
        if (tempsPause > (sf::Time::Zero)) {
            force = {(0.0) , (0.0)};
            speed = 0.0;
            setEtat(Etat::FEEDING);
         
        }
        
        if (tempsPauseMating > (sf::Time::Zero)) {
			force = {(0.0), (0.0)};
			speed = 0.0;
			setEtat(Etat::MATING);
		}
		
		if (tempsPauseGivingBirth > (sf::Time::Zero)) {
			force = {(0.0), (0.0)};
			speed = 0.0;
			setEtat(Etat::GIVING_BIRTH);
		}
		
		if (tempsDeGestation <= sf::Time::Zero) {
			tempsPause = sf::Time::Zero;
			}
        updateAttributs (force, dt);

    }
//methode qui mets à jour tous les attributs de direction, energie, vitesse etc. apres un pas de temps dt (est appelée dans la methode update)
void Animal::updateAttributs (Vec2d force, const sf::Time& dt)
{

    Vec2d acceleration (force/ getMass());
    Vec2d newSpeed (getSpeedVector() + acceleration * dt.asSeconds());

    Vec2d newDirection = newSpeed.normalised();
    // plafonner la nouvelle vitesse

    if (newSpeed.length() > getMaxSpeed()) {
        newSpeed = newDirection * getMaxSpeed();
    }

    move(newSpeed * dt.asSeconds());
    
    
	direction = newDirection;
	
    speed = newSpeed.length();
	
	Viellissement(dt); 
	double perte_energie = getAppConfig().animal_base_energy_consumption + (speed*(this->getEnergyLossFactor())*dt.asSeconds());
	EnergyLoss(perte_energie);
}

// accesseur qui retourne l'angle du vecteur direction en coordonnees polaires
double Animal::getRotation() const
{
    return direction.angle();
}

// methode mettant a jour le vecteur direction apres une rotation de angle donne
void Animal::setRotation(double angle)
{
    direction = Vec2d(cos(angle), sin(angle));
}

// methode qui affiche en gris le champs de vision de l'animal
void Animal::drawVision(sf::RenderTarget& targetWindow) const
{
    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent blue
    Arc arc (buildArc( ((-getViewRange()/2)/ DEG_TO_RAD), ((getViewRange()/2) / DEG_TO_RAD),
                       getViewDistance(), getPosition(), color, direction.angle() / DEG_TO_RAD));
    targetWindow.draw(arc);
}

//methode dessinant un animal
void Animal::draw(sf::RenderTarget& targetWindow) 
{
        vector <OrganicEntity*> liste (getAppEnv().getEntitiesInSightForAnimal (this));

        //le champ de vision et la cible virtuelle sont visibles seulement lorsque le mode debugging est activé
        if (isDebugOn())  {
            drawVision (targetWindow);
            targetWindow.draw(buildText(texteAAfficher (getEtat(), sexe, getEnergyLevel()),
                                        getPosition()+direction.normalised()*getRandomWalkDistance() ,
                                        getAppFont(),
                                        getAppConfig().default_debug_text_size,
                                        stateColor(),
                                        getRotation() / DEG_TO_RAD + 90));
            CircularCollider::draw(targetWindow);
              
        if (pregnant) 
    {
		targetWindow.draw((buildAnnulus(getPosition(), getRadius(), sf::Color::Magenta,3)));
	}
	
	if (getEtat() == Etat::GIVING_BIRTH ) {
		targetWindow.draw((buildAnnulus(getPosition(), getRadius(), sf::Color (255,0,0),10)));
	}
        }
        if ((listeDePredateurs.empty()) && (mateProche==nullptr) && (nourritureProche==nullptr)  
        && isDebugOn() && (getEtat() != Etat::MATING) && (getEtat() != Etat::FEEDING) && (getEtat() != Etat::GIVING_BIRTH)) {
            targetWindow.draw((buildAnnulus(getPosition()+direction.normalised()*getRandomWalkDistance() , getRandomWalkRadius(), sf::Color(255, 150, 0), 2)));
            targetWindow.draw(buildCircle (randomWalk(), 5 , sf::Color(0,0,255))); 
        }
    
}


// methode determinant si l'animal voit la cible ou non
bool Animal::isTargetInSight (Vec2d positionCible) const
{
    Vec2d vecteur (positionCible - getPosition());
    double longueurVecteurCarre (vecteur.lengthSquared());
    double EPSILON (cos(((getViewRange())+0.001)/2));
    double dotProduct (direction.dot(vecteur.normalised()));
    return ((longueurVecteurCarre <= pow(getViewDistance(),2)) && ((dotProduct >= EPSILON ) 
    or (isEqual (longueurVecteurCarre, 0))));
}

Vec2d Animal::randomWalk() 
{
    Vec2d random_vec (uniform(-1.0 , 1.0), uniform(-1.0, 1.0)); // appel a la methode uniform
    current_target += random_vec * getRandomWalkJitter();
    current_target = (current_target.normalised())*(getRandomWalkRadius());
    Vec2d moved_current_target = current_target + Vec2d(getRandomWalkDistance(), 0);
    return ConvertToGlobalCoord (moved_current_target);
}


// methode qui convert un vecteur exprime dans le repere local d'un animal en un vecteur dans le repere global
Vec2d Animal::ConvertToGlobalCoord(Vec2d local) const
{
    sf::Transform matTransform; // transformation matrix
    matTransform.translate(getPosition()); //translation a la position local
    matTransform.rotate((getRotation())/DEG_TO_RAD); // rotation de l'angle du vecteur direction de local
    Vec2d global = matTransform.transformPoint(local); // transformation

    return global ;
}


//methode convertissant en strings les états pour pouvoir les afficher dans le mode debugging
string Animal::fromEnumToString(Etat etat) const
{
    switch (etat)

    {
    case Etat::FOOD_IN_SIGHT :
        return "FOOD IN SIGHT";
        break;
    case Etat::FEEDING :
        return "FEEDING";
        break;
    case Etat::RUNNING_AWAY :
        return "RUNNING AWAY";
        break;
    case Etat::MATING :
        return "MATING";
        break;
    case Etat::GIVING_BIRTH:
        return "GIVING BIRTH";
        break;
    case Etat::WANDERING :
        return "WANDERING" ;
        break;
    case Etat::MATE_IN_SIGHT :
        return "MATE IN SIGHT";
        break;
	default :
	cout << " Erreur etat inconnu" << endl;
	exit(1);
    }
}


//methode renvoyant le texte à afficher dans le mode debugging
string Animal::texteAAfficher (Etat etat, bool sexe, double energyLevel) const
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

//methode retournant la couleur a afficher en mode debugging pour le texte (et les circular collider?) mais je sais pas si elle est très utile à voir par la suite
//(car pour l'instant elle ne retourne qu'un état par défaut)
sf::Color Animal::stateColor () const
{
    switch (getEtat()) {
    default :
        return getAppConfig().debug_text_color;
    }
}

Animal::Etat Animal::getEtat() const
{
    return etat_;
}

void Animal::setEtat (Etat etat) 
{
	etat_ = etat;
}

//Perfectionnisme test 18

Vec2d Animal::getForceAttractionWhenFeeding ()
{
	Vec2d negativeTarget {-1.0,0.0}; // cible negative dans le repere locale
	setTargetPosition(negativeTarget);
	Vec2d f (getForceAttraction());
	return f;
}

Vec2d Animal::getDirection () const
{
	return direction;
}

sf::Time Animal::fromDouble (double d) const
{
	return sf::seconds (d);
}

Animal::~Animal()
{}

///SETTERS
void Animal::setPregnant(bool baby)
{
	pregnant = baby;
} 
void Animal::setTimeGivingBirth(sf::Time pause)
{
	tempsPauseGivingBirth = pause;
}
void Animal::setTimeGestation(sf::Time gestation)
{
	tempsDeGestation = gestation;
}
void Animal::setTimeMating(sf::Time mating)
{
	tempsPauseMating = mating;
}
void Animal::setNumberChildren(unsigned int nb)
{
	nbEnfants = nb;
}


///GETTERS
	
bool Animal::isFemale() const
{
	return sexe;
}

bool Animal::isPregnant() const
{
	return pregnant;
}
unsigned int Animal::getNumberChildren() const
{
	return nbEnfants;
}
OrganicEntity* Animal::getNourritureProche() const
{
	return nourritureProche;
}
	



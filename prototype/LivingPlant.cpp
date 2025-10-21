#include "LivingPlant.h"

#include "Herb.h"
#include "Shrub.h"
#include "Succulent.h"
#include "Tree.h"
#include "../composite/PlantComponent.h"
#include "../singleton/Singleton.h"

LivingPlant::LivingPlant(std::string name, double price, int waterAffect, int sunAffect)
    : PlantComponent(price, waterAffect, sunAffect),
      // remember to change to getString() after Wilmar fixes getSeason()
      name(Inventory::getInstance()->getString("")),
      season(Inventory::getInstance()->getString("")),
      age(0),
      health(0),
      waterLevel(0),
      sunExposure(0),
      maturityState(nullptr),
      waterStrategy(nullptr),
      sunStrategy(nullptr) {};

LivingPlant::LivingPlant(const LivingPlant &other)
    : PlantComponent(other),

      name(other.name),
      age(other.age),
      health(other.health),
      waterLevel(other.waterLevel),
      sunExposure(other.sunExposure),
      season(other.season),

      maturityState(other.maturityState),
      waterStrategy(other.waterStrategy),
      sunStrategy(other.sunStrategy) {};

void LivingPlant::setAge(int age)
{
    this->age = age;
};

void LivingPlant::setHealth(int health)
{
    this->health = health;
};

void LivingPlant::setWaterLevel(int waterLevel)
{
    this->waterLevel = waterLevel;
};

void LivingPlant::setSunExposure(int sunExposure)
{
    this->sunExposure = sunExposure;
};

void LivingPlant::setWaterStrategy(int strategy) {
    // waiting on wilmar's final implementation for flyweight
};

void LivingPlant::setSunStrategy(int strategy) {
    // waiting on wilmar's final implementation for flyweight
};

void LivingPlant::setMaturity(int state) {
    // waiting on wilmar's final implementation for flyweight
};

void LivingPlant::setSeason(Flyweight<std::string *> *season)
{
    this->season = season;
}

void LivingPlant::addAttribute(PlantAttributes *attribute) {
    // stub since this is the ConcreteComponent
};

int LivingPlant::getAge()
{
    return this->age;
};

int LivingPlant::getHealth()
{
    return this->health;
};

int LivingPlant::getSunExposure()
{
    return this->sunExposure;
};

std::string LivingPlant::getName()
{
    return *name->getState();
};

int LivingPlant::getAffectSunlight()
{
    return this->affectSunValue;
};

int LivingPlant::getAffectWater()
{
    return this->affectWaterValue;
};

double LivingPlant::getPrice()
{
    return this->price;
};

std::string LivingPlant::getInfo()
{
    std::string plantName = *name->getState();
    std::string baseInfo;

    baseInfo += "Name: " + plantName + "\n";
    baseInfo += "Status: Basic Plant Component\n";
    baseInfo += "--------------------------------------\n";
    baseInfo += "Health: " + std::to_string(health) + "\n";
    baseInfo += "Age: " + std::to_string(age) + " days\n";
    baseInfo += "Water Level: " + std::to_string(waterLevel) + "\n";
    baseInfo += "Sun Exposure: " + std::to_string(sunExposure) + "\n";
    baseInfo += "Base Price: R" + std::to_string(price) + "\n";
    baseInfo += "Water Affection: " + std::to_string(affectWaterValue) + "\n";
    baseInfo += "Sun Affection: " + std::to_string(affectSunValue) + "\n";

    return baseInfo;
};

Flyweight<std::string *> *LivingPlant::getSeason()
{
    return this->season;
}

PlantComponent *LivingPlant::clone()
{
    return new LivingPlant(*this);
};

void LivingPlant::water()
{
    if (this->waterStrategy != nullptr)
    {

        WaterStrategy *strategy = this->waterStrategy->getState();

        int waterApplied = strategy->water(this);

        this->waterLevel += waterApplied;

        // should we add a limit to the amount we can water? And should this be MVP
    }
}

void LivingPlant::setOutside()
{
    if (this->sunStrategy != nullptr)
    {

        SunStrategy *strategy = this->sunStrategy->getState();

        int sunApplied = strategy->addSun(this);

        this->sunExposure += sunApplied;

        // should we add a limit to the amount we can leave plants outside? And should this be MVP
    }
}

int LivingPlant::getWaterLevel()
{
    return this->waterLevel;
};

void LivingPlant::tick()
{
    
}

Herb::Herb()
    : LivingPlant("", 0, 0, 0) {};

Herb::Herb(const Herb &other)
    : LivingPlant(other) {};

PlantComponent *Herb::clone()
{
    return new Herb(*this);
}

Shrub::Shrub()
    : LivingPlant("", 0, 0, 0) {};

Shrub::Shrub(const Shrub &other)
    : LivingPlant(other) {};

PlantComponent *Shrub::clone()
{
    return new Shrub(*this);
}

Succulent::Succulent()
    : LivingPlant("", 0, 0, 0) {};

Succulent::Succulent(const Succulent &other)
    : LivingPlant(other) {};

PlantComponent *Succulent::clone()
{
    return new Succulent(*this);
}

Tree::Tree()
    : LivingPlant("", 0, 0, 0) {};

Tree::Tree(const Tree &other)
    : LivingPlant(other) {};

PlantComponent *Tree::clone()
{
    return new Tree(*this);
}

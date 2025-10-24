#include "LivingPlant.h"

#include "Herb.h"
#include "Shrub.h"
#include "Succulent.h"
#include "Tree.h"
#include "../composite/PlantComponent.h"
#include "../singleton/Singleton.h"

LivingPlant::LivingPlant(std::string name, double price, int waterAffect, int sunAffect)
    : PlantComponent(price, waterAffect, sunAffect), age(0),
      health(0),
      waterLevel(0),
      sunExposure(0),
      maturityState(nullptr),
      waterStrategy(nullptr),
      sunStrategy(nullptr),
      decorator(nullptr)
{
    // remember to change to getString() after Wilmar fixes getSeason()
    this->name = Inventory::getInstance()->getString(name);
    this->season = nullptr;
};

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
      sunStrategy(other.sunStrategy),
      decorator(nullptr) {};

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

void LivingPlant::setWaterStrategy(int strategy)
{
    Inventory *inv = Inventory::getInstance();

    Flyweight<WaterStrategy *> *newStrategy = inv->getWaterFly(strategy);

    this->waterStrategy = newStrategy;
};

void LivingPlant::setSunStrategy(int strategy)
{
    Inventory *inv = Inventory::getInstance();

    Flyweight<SunStrategy *> *newStrategy = inv->getSunFly(strategy);

    this->sunStrategy = newStrategy;
};

void LivingPlant::setMaturity(int state)
{
    Inventory *inv = Inventory::getInstance();

    Flyweight<MaturityState *> *newState = inv->getStates(state);

    this->maturityState = newState;
};

void LivingPlant::setSeason(Flyweight<std::string *> *season)
{
    this->season = season;
}

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

double LivingPlant::getPrice()
{
    return this->price;
};

std::string LivingPlant::getInfo()
{
    std::string plantName = *name->getState();
    std::string baseInfo = "";

    baseInfo += "Name: " + plantName + "\n";
    baseInfo += "Health: " + std::to_string(health) + "\n";
    baseInfo += "Age: " + std::to_string(age) + " days\n";
    baseInfo += "Water Level: " + std::to_string(waterLevel) + "\n";
    baseInfo += "Sun Exposure: " + std::to_string(sunExposure) + "\n";
    baseInfo += "Base Price: R" + std::to_string(price) + "\n";
    baseInfo += "Total Price: R" + std::to_string(decorator->getPrice()) + "\n";
    baseInfo += "Water Affection: " + std::to_string(decorator->affectWater()) + "\n";
    baseInfo += "Sun Affection: " + std::to_string(decorator->affectSunlight()) + "\n";

    return baseInfo;
};

Flyweight<std::string *> *LivingPlant::getSeason()
{
    return this->season;
}

ComponentType LivingPlant::getType() const
{
    return ComponentType::LIVING_PLANT;
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
    }
}

int LivingPlant::affectWater()
{
    return affectWaterValue;
};

int LivingPlant::affectSunlight()
{
    return affectSunValue;
};

void LivingPlant::update()
{
    // added null checks
    if (this->decorator != nullptr)
    {
        this->waterLevel -= this->decorator->affectWater();
        this->sunExposure -= this->decorator->affectSunlight();
    }
    else
    {
        this->waterLevel -= this->affectWater();
        this->sunExposure -= this->affectSunlight();
    }
};

void LivingPlant::setOutside()
{
    if (this->sunStrategy != nullptr)
    {

        SunStrategy *strategy = this->sunStrategy->getState();

        int sunApplied = strategy->addSun(this);
    }
}

int LivingPlant::getWaterLevel()
{
    return this->waterLevel;
}

void LivingPlant::addAttribute(PlantComponent *attribute)
{
    if (this->decorator)
    {
        this->decorator->addAttribute(attribute);
    }
    else
    {
        this->decorator = attribute;
        attribute->addAttribute(this);
    }
}

Herb::Herb()
    : LivingPlant("Herb", 30.00, 3, 3) {};

Herb::Herb(const Herb &other)
    : LivingPlant(other) {};

PlantComponent *Herb::clone()
{
    return new Herb(*this);
}

Shrub::Shrub()
    : LivingPlant("Shrub", 75.00, 4, 4) {};

Shrub::Shrub(const Shrub &other)
    : LivingPlant(other) {};

PlantComponent *Shrub::clone()
{
    return new Shrub(*this);
}

Succulent::Succulent()
    : LivingPlant("Succulent", 45.00, 1, 5) {};

Succulent::Succulent(const Succulent &other)
    : LivingPlant(other) {};

PlantComponent *Succulent::clone()
{
    return new Succulent(*this);
}

Tree::Tree()
    : LivingPlant("Tree", 150.00, 5, 5) {};

Tree::Tree(const Tree &other)
    : LivingPlant(other) {};

PlantComponent *Tree::clone()
{
    return new Tree(*this);
}
PlantComponent *LivingPlant::getDecorator()
{
    return this->decorator;
}
PlantComponent *LivingPlant::correctShape(PlantComponent *mainDecorator)
{
    this->decorator = mainDecorator;
    return this;
}
LivingPlant::~LivingPlant()
{
    if (!deleted)
    {
        deleted = true;
        if (decorator)
        {
            delete decorator;
        }
    }
}
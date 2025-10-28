#include "LivingPlant.h"

#include "Herb.h"
#include "Shrub.h"
#include "Succulent.h"
#include "Tree.h"
#include "../composite/PlantComponent.h"
#include "../singleton/Singleton.h"
#include "../state/MaturityState.h"

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

    Flyweight<WaterStrategy> *newStrategy = inv->getWaterFly(strategy);

    this->waterStrategy = newStrategy;
};

void LivingPlant::setSunStrategy(int strategy)
{
    Inventory *inv = Inventory::getInstance();

    Flyweight<SunStrategy > *newStrategy = inv->getSunFly(strategy);

    this->sunStrategy = newStrategy;
};

void LivingPlant::setMaturity(int state)
{
    Inventory *inv = Inventory::getInstance();

    Flyweight<MaturityState> *newState = inv->getStates(state);

    this->maturityState = newState;
};

void LivingPlant::setSeason(Flyweight<std::string > *season)
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
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2);

    std::string plantName = *name->getState();

    stream << "-------------------------------\n";

    stream << "| " << std::left << std::setw(15) << "Name:" << std::setw(13) << plantName << "|\n";
    stream << "| " << std::left << std::setw(15) << "Health:" << std::setw(13) << health << "|\n";
    stream << "| " << std::left << std::setw(15) << "Age:" << std::setw(13) << (std::to_string(age) + " days") << "|\n";
    stream << "| " << std::left << std::setw(15) << "Water Level:" << std::setw(13) << waterLevel << "|\n";
    stream << "| " << std::left << std::setw(15) << "Sun Exposure:" << std::setw(13) << sunExposure << "|\n";
    stream << "| " << std::left << std::setw(15) << "Base Price:" << "R" << std::setw(12) << price << "|\n";

    stream << "-------------------------------\n";

    if (decorator)
    {
        stream << "\n";
        stream << "Total:\n";
        stream << "-------------------------------\n";
        stream << "| " << std::left << std::setw(20) << "Total Price:" << "R" << std::setw(7) << decorator->getPrice() << "|\n";
        stream << "| " << std::left << std::setw(20) << "Water Affection:" << std::setw(8) << decorator->affectWater() << "|\n";
        stream << "| " << std::left << std::setw(20) << "Sun Affection:" << std::setw(8) << decorator->affectSunlight() << "|\n";
        stream << "-------------------------------\n";
        stream << "Attributes:\n";
    }

    return stream.str();
}

Flyweight<std::string> *LivingPlant::getSeason()
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

Herb::Herb(std::string name)
    : LivingPlant(name, 30.00, 4, 4) {};

Herb::Herb(const Herb &other)
    : LivingPlant(other) {};

PlantComponent *Herb::clone()
{
    return new Herb(*this);
}

Shrub::Shrub()
    : LivingPlant("Shrub", 75.00, 4, 4) {};

Shrub::Shrub(std::string name)
    : LivingPlant(name, 75.00, 4, 4) {};

Shrub::Shrub(const Shrub &other)
    : LivingPlant(other) {};

PlantComponent *Shrub::clone()
{
    return new Shrub(*this);
}

Succulent::Succulent()
    : LivingPlant("Succulent", 45.00, 1, 5) {};

Succulent::Succulent(std::string name)
    : LivingPlant(name, 45.00, 4, 4) {};

Succulent::Succulent(const Succulent &other)
    : LivingPlant(other) {};

PlantComponent *Succulent::clone()
{
    return new Succulent(*this);
}

Tree::Tree()
    : LivingPlant("Tree", 150.00, 5, 5) {};

Tree::Tree(std::string name)
    : LivingPlant(name, 150.00, 4, 4) {};

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
            delete decorator;
    }
}
int LivingPlant::getWaterValue()
{
    return this->waterLevel;
}
int LivingPlant::getSunlightValue()
{
    return this->sunExposure;
}
void LivingPlant::tick()
{
    
    this->maturityState->getState()->grow(this);
}
#include "PlantGroup.h"
#include "../observer/Observer.h"
#include "../prototype/LivingPlant.h"
#include <sstream>

PlantGroup::PlantGroup()
    : PlantComponent(0.0, 0, 0) {};

PlantGroup::~PlantGroup()
{
    std::list<PlantComponent *>::iterator itr = plants.begin();
    while (itr != plants.end())
    {
        if ((*itr)->getDecorator() == nullptr)
            delete (*itr)->getDecorator();
        else
            delete *itr;

        itr++;
        // should work.
    }
}

PlantGroup::PlantGroup(const PlantGroup &other)
    : PlantComponent(other)
{

    for (PlantComponent *component : other.plants)
    {
        PlantComponent *clonedComponent = component->clone();
        this->plants.push_back(clonedComponent);
    }
}

void PlantGroup::setOutside()
{
    if (!plants.empty())
    {
        for (PlantComponent *component : plants)
        {
            component->setOutside();
        }
    }
};

void PlantGroup::water()
{
    if (!plants.empty())
    {
        for (PlantComponent *component : plants)
        {
            component->water();
        }
    }
};

std::string PlantGroup::getInfo()
{
    std::stringstream ss;

    ss << "\n*** Plant Group ***" << std::endl;
    ss << "---------------------------------" << std::endl;
    int counter = 0;
    for (PlantComponent *component : plants)
    {
        counter++;
        ss << component->getDecorator()->getInfo();

        ss << "\n--- End of Component " + std::to_string(counter) + " ---\n";
    }

    ss << "---------------------------------" << std::endl;
    return ss.str();
};

std::list<PlantComponent *> *PlantGroup::getPlants()
{
    return &plants;
}

ComponentType PlantGroup::getType() const
{
    return ComponentType::PLANT_GROUP;
}
PlantComponent *PlantGroup::clone()
{
    return new PlantGroup(*this);
};

void PlantGroup::update()
{
    for (PlantComponent *component : plants)
    {
        component->update();
    }
};

int PlantGroup::affectWater()
{
    int totalAffected = 0;

    for (PlantComponent *component : plants)
    {
        totalAffected += component->affectWater();
    }

    return totalAffected;
};

int PlantGroup::affectSunlight()
{
    int totalAffected = 0;

    for (PlantComponent *component : plants)
    {
        totalAffected += component->affectSunlight();
    }

    return totalAffected;
};

double PlantGroup::getPrice()
{
    double totalPrice = this->price;
    for (PlantComponent *component : plants)
    {
        totalPrice += component->getPrice();
    }
    return totalPrice;
};

void PlantGroup::addAttribute(PlantComponent *attribute)
{
    for (PlantComponent *component : plants)
    {
        PlantComponent *clonedAttribute = attribute->clone();
        component->addAttribute(clonedAttribute);
    }
};

void PlantGroup::addComponent(PlantComponent *component)
{
    plants.push_back(component);
}

std::string PlantGroup::getName()
{
    std::stringstream ss;
    ss << "Plant Group: ";

    int count = 0;
    for (PlantComponent *component : plants)
    {
        if (count < 3)
        {
            ss << component->getName() << ", ";
        }
        count++;
    }

    std::string name = ss.str();
    if (name.length() > 2)
    {
        name.pop_back();
        name.pop_back();
    }
    return name;
};
PlantComponent *PlantGroup::correctShape(PlantComponent *component)
{
    throw "This should never be run";
    delete component;
    return nullptr;
}

// observer stuff

void PlantGroup::attach(Observer *careTaker)
{
    if (!careTaker)
        return;
    bool exists = false;
    for (std::list<Observer *>::iterator it = observers.begin(); it != observers.end(); ++it)
    {
        if (*it == careTaker)
        {
            exists = true;
            break;
        }
    }
    if (!exists)
    {
        observers.push_back(careTaker);
    }
}

void PlantGroup::detach(Observer *careTaker)
{
    if (!careTaker)
        return;
    observers.remove(careTaker);
}

/**
 * @brief Notifies observers that all plants need water.
 */
void PlantGroup::waterNeeded()
{
    for (Observer *obs : observers)
    {
        for (PlantComponent *plant : plants)
        {
            plant->water();
            LivingPlant *lp = dynamic_cast<LivingPlant *>(plant);
            if (lp)
            {
                obs->getWaterUpdate(lp);
            }
        }
    }
}

/**
 * @brief Notifies observers that all plants need sunlight.
 */
void PlantGroup::sunlightNeeded()
{
    for (Observer *obs : observers)
    {
        for (PlantComponent *plant : plants)
        {
            plant->setOutside();
            LivingPlant *lp = dynamic_cast<LivingPlant *>(plant);
            if (lp)
            {
                obs->getSunUpdate(lp);
            }
        }
    }
}

/**
 * @brief Notifies observers that all plants have updated states.
 */
void PlantGroup::stateUpdated()
{
    for (Observer *obs : observers)
    {
        for (PlantComponent *plant : plants)
        {
            plant->update();
            LivingPlant *lp = dynamic_cast<LivingPlant *>(plant);
            if (lp)
            {
                obs->getStateUpdate(lp);
            }
        }
    }
}

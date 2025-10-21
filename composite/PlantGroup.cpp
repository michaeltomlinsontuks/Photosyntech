#include "PlantGroup.h"
#include <sstream>

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
        ss << component->getInfo();

        ss << "\n--- End of Component" + std::to_string(counter) + " ---\n";
    }

    ss << "---------------------------------" << std::endl;
    return ss.str();
};

void PlantGroup::tick()
{
    auto itr = this->plants.begin();
    while (itr != plants.end())
    {
        if (*itr)
            (*itr)->tick();
    }
}
// please use testing like this.

#include "singleton/Singleton.h"
#include "prototype/Tree.h"
#include "state/Seed.h"
#include "decorator/plantDecorator/Autumn.h"
#include "flyweight/Flyweight.h"
#include "flyweight/FlyweightFactory.h"
#include "prototype/LivingPlant.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "prototype/Succulent.h"
#include "strategy/LowWater.h"
#include "strategy/MidWater.h"
#include "strategy/AlternatingWater.h"
#include "strategy/HighWater.h"
#include "strategy/AlternatingWater.h"
#include "strategy/LowSun.h"
#include "strategy/MidSun.h"
#include "strategy/HighSun.h"
#include "strategy/AlternatingSun.h"
#include "singleton/Singleton.h"
#include "state/Seed.h"
#include "state/Vegetative.h"
#include "state/Mature.h"
#include "state/Dead.h"
#include "builder/Director.h"
#include "builder/RoseBuilder.h"
#include "builder/CactusBuilder.h"
#include "mediator/Customer.h"
#include "mediator/Staff.h"
#include "mediator/SalesFloor.h"
#include "mediator/SuggestionFloor.h"
#include "mediator/Mediator.h"
#include "mediator/User.h"
#include "observer/Observer.h"
#include "observer/Subject.h"
#include "composite/PlantGroup.h"
#include "iterator/AggPlant.h"
#include <type_traits>

void howToUseBuilder();
void iteratorUsage();
int main()
{
    Inventory::getInstance();
    // creates the singleton needed;

    howToUseBuilder();
    iteratorUsage();
    delete Inventory::getInstance();
    // delete the instance
    return 0;
}

void howToUseBuilder()
{
    RoseBuilder *roseBuilder = new RoseBuilder();
    Director *roseDirector = new Director(roseBuilder);
    roseDirector->construct();
    Builder *cactusBuilder = new CactusBuilder();
    Director *cactusDirector = new Director(cactusBuilder);
    cactusDirector->construct();
    // Initiate rose delivery
    PlantGroup *roseDelivery = new PlantGroup();
    for (int i = 0; i < 3; i++)
    {
        roseDelivery->addComponent(roseBuilder->getResult());
    }
    // there are now 100 roses in the plantGroup.
    PlantGroup *cactusDelivery = new PlantGroup();
    for (int i = 0; i < 3; i++)
    {
        cactusDelivery->addComponent(cactusBuilder->getResult());
    }
    Inventory::getInstance()->getInventory()->addComponent(roseDelivery);
    Inventory::getInstance()->getInventory()->addComponent(cactusDelivery);
    cout << Inventory::getInstance()->getInventory()->getInfo() << endl;

    delete cactusBuilder;
    delete cactusDirector;
    delete roseBuilder;
    delete roseDirector;
}
void iteratorUsage()
{
    Aggregate *factory = new AggPlant(Inventory::getInstance()->getInventory()->getPlants());

    Iterator *itr = factory->createIterator();

    while (!itr->isDone())
    {

        cout << itr->currentItem()->getDecorator()->getInfo() << endl;
        cout<< "press enter to continue" << endl;
        cin.get();
        itr->next();
    }
    delete itr;
    delete factory;
}
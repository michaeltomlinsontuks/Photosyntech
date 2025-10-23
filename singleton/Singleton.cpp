#include "Singleton.h"
#include "../state/Dead.h"
#include "../state/Mature.h"
#include "../state/Vegetative.h"
#include "../state/Seed.h"
#include "../composite/PlantGroup.h"

Inventory *Inventory::instance = nullptr;

Inventory::Inventory()
{

    inventory = new PlantGroup();

    stringFactory = new FlyweightFactory<string, string *>();
    waterStrategies = new FlyweightFactory<int, WaterStrategy *>();
    sunStrategies = new FlyweightFactory<int, SunStrategy *>();
    states = new FlyweightFactory<int, MaturityState *>();
    staffList = new vector<Staff *>();
    customerList = new vector<Customer *>();

    // Adding the water strategies
    waterStrategies->getFlyweight(LowWater::getID(), new LowWater());
    waterStrategies->getFlyweight(MidWater::getID(), new MidWater());
    waterStrategies->getFlyweight(HighWater::getID(), new HighWater());
    waterStrategies->getFlyweight(AlternatingWater::getID(), new AlternatingWater());

    // adding the Sun strategies
    sunStrategies->getFlyweight(LowSun::getID(), new LowSun());
    sunStrategies->getFlyweight(MidSun::getID(), new MidSun());
    sunStrategies->getFlyweight(HighSun::getID(), new HighSun());
    sunStrategies->getFlyweight(AlternatingSun::getID(), new AlternatingSun());

    states->getFlyweight(Seed::getID(), new Seed());
    states->getFlyweight(Vegetative::getID(), new Vegetative());
    states->getFlyweight(Mature::getID(), new Mature());
    states->getFlyweight(Dead::getID(), new Dead());
}
#include <chrono>
#include <iostream>

Inventory::~Inventory()
{
    using namespace std::chrono;

    auto start_total = high_resolution_clock::now();

    auto start_inventory = high_resolution_clock::now();
    if (inventory)
        delete inventory;
    auto end_inventory = high_resolution_clock::now();
    std::cout << "Deleted inventory in " << duration<double>(end_inventory - start_inventory).count() << "s\n";

    auto start_strategies = high_resolution_clock::now();
    delete stringFactory;
    delete waterStrategies;
    delete sunStrategies;
    delete states;
    auto end_strategies = high_resolution_clock::now();
    std::cout << "Deleted strategies in " << duration<double>(end_strategies - start_strategies).count() << "s\n";

    auto start_staff = high_resolution_clock::now();
    for (auto itr = staffList->begin(); itr != staffList->end(); ++itr)
    {
        if (*itr != nullptr)
            delete *itr;
    }
    delete staffList;
    auto end_staff = high_resolution_clock::now();
    std::cout << "Deleted staff in " << duration<double>(end_staff - start_staff).count() << "s\n";

    auto start_customers = high_resolution_clock::now();
    for (auto itrCustomer = customerList->begin(); itrCustomer != customerList->end(); ++itrCustomer)
    {
        if (*itrCustomer != nullptr)
            delete *itrCustomer;
    }
    delete customerList;
    auto end_customers = high_resolution_clock::now();
    std::cout << "Deleted customers in " << duration<double>(end_customers - start_customers).count() << "s\n";

    instance = NULL;

    auto end_total = high_resolution_clock::now();
    std::cout << "Total Inventory destruction time: " << duration<double>(end_total - start_total).count() << "s\n";
}

Inventory *Inventory::getInstance()
{
    if (!instance)
    {
        instance = new Inventory();
    }

    return instance;
}

Flyweight<std::string *> *Inventory::getString(std::string str)
{
    string *flyweightData = new string(str);
    Flyweight<std::string *> *fly = stringFactory->getFlyweight(*flyweightData, flyweightData);
    if (fly->getState() != flyweightData)
    {
        delete flyweightData;
    }
    return fly;
}
Flyweight<WaterStrategy *> *Inventory::getWaterFly(int id)
{

    try
    {
        return waterStrategies->getFlyweight(id);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
        return waterStrategies->getFlyweight(LowWater::getID());
    }
}
Flyweight<MaturityState *> *Inventory::getStates(int id)
{
    try
    {
        return states->getFlyweight(id);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
        return states->getFlyweight(Seed::getID());
    }
}

Flyweight<SunStrategy *> *Inventory::getSunFly(int id)
{
    try
    {
        return sunStrategies->getFlyweight(id);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
        return sunStrategies->getFlyweight(LowSun::getID());
    }
}

PlantGroup *Inventory::getInventory()
{
    return inventory;
}

vector<Customer *> *Inventory::getCustomers()
{
    return customerList;
}
vector<Staff *> *Inventory::getStaff()
{
    return staffList;
}

void Inventory::addStaff(Staff *staff)
{
    staffList->push_back(staff);
}
void Inventory::addCustomer(Customer *customer)
{
    customerList->push_back(customer);
}
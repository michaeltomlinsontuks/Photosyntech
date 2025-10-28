#include "Singleton.h"
#include "../state/Dead.h"
#include "../state/Mature.h"
#include "../state/Vegetative.h"
#include "../state/Seed.h"
#include "../composite/PlantGroup.h"

Inventory *Inventory::instance = nullptr;
thread *Inventory::TickerThread = nullptr;
std::atomic<bool> Inventory::on(false);

Inventory::Inventory()
{
    on.store(false);
    inventory = new PlantGroup();

    stringFactory = new FlyweightFactory<string, string >();
    waterStrategies = new FlyweightFactory<int, WaterStrategy >();
    sunStrategies = new FlyweightFactory<int, SunStrategy >();
    states = new FlyweightFactory<int, MaturityState>();
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
Inventory::~Inventory()
{

    stopTicker();

    if (inventory)
        delete inventory;

    delete stringFactory;
    delete waterStrategies;
    delete sunStrategies;
    delete states;

    std::vector<Staff *>::iterator itr = staffList->begin();
    while (!(itr == staffList->end()))
    {
        if (*itr != nullptr)
        {
            delete *itr;
        }
        itr++;
    }

    std::vector<Customer *>::iterator itrCustomer = customerList->begin();
    while (!(itrCustomer == customerList->end()))
    {
        if (*itrCustomer != nullptr)
        {
            delete *itrCustomer;
        }
        itrCustomer++;
    }
    delete staffList;
    delete customerList;
    instance = NULL;
}
Inventory *Inventory::getInstance()
{
    if (!instance)
    {
        instance = new Inventory();
    }

    return instance;
}

Flyweight<std::string > *Inventory::getString(std::string str)
{
    string *flyweightData = new string(str);
    Flyweight<std::string > *fly = stringFactory->getFlyweight(*flyweightData, flyweightData);
    if (fly->getState() != flyweightData)
    {
        delete flyweightData;
    }
    return fly;
}
Flyweight<WaterStrategy> *Inventory::getWaterFly(int id)
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
Flyweight<MaturityState> *Inventory::getStates(int id)
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

Flyweight<SunStrategy > *Inventory::getSunFly(int id)
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
bool Inventory::startTicker()
{
    Inventory *inv = getInstance();

    if (!on.load())
    {
        on.store(true);
        if (!TickerThread)
            TickerThread = new thread(&Inventory::TickInventory, inv);

        return true;
    }
    else
        return false;
}
bool Inventory::stopTicker()
{

    if (on.load())
    {
        on.store(false);
        
        if (TickerThread && TickerThread->joinable())
        {
            TickerThread->join();
            delete TickerThread;
            TickerThread = nullptr;
        }
        else if (TickerThread)
            delete TickerThread;

        return true;
    }
    else
        return false;
}

void Inventory::TickInventory()
{
    while (on.load())
    {
        cout << "A tick occured" << endl;
        this->inventory->tick();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
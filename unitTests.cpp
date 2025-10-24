// please use testing like this.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "singleton/Singleton.h"
#include "prototype/Tree.h"
#include "state/Seed.h"
#include "decorator/plantDecorator/Autumn.h"
#include <doctest.h>

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
TEST_CASE("Overall Testing of flyweight strings + error handling")
{
    FlyweightFactory<int, string *> *fac = new FlyweightFactory<int, string *>();

    SUBCASE("factory is created")
    {
        CHECK(fac != nullptr);
    }

    SUBCASE("Correct String is inserted and accessable")
    {
        fac->getFlyweight(0, new string("Insert1"));
        CHECK(*fac->getFlyweight(0)->getState() == "Insert1");
    }

    SUBCASE("Correct String is inserted and when multiple strings exist")
    {
        fac->getFlyweight(0, new string("Insert1"));
        fac->getFlyweight(1, new string("Insert2"));
        CHECK(*fac->getFlyweight(1)->getState() == "Insert2");
        CHECK(*fac->getFlyweight(0)->getState() == "Insert1");
    }
    try
    {
        fac->getFlyweight(5);
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }

    delete fac;
}
TEST_CASE("Overall Testing of flyweight water strategies")
{
    FlyweightFactory<int, WaterStrategy *> *fac = new FlyweightFactory<int, WaterStrategy *>();
    LivingPlant *plant = new Tree();
    fac->getFlyweight(LowWater::getID(), new LowWater());

    CHECK(fac->getFlyweight(LowWater::getID())->getState()->water(plant) == 10);

    fac->getFlyweight(MidWater::getID(), new MidWater());

    CHECK(fac->getFlyweight(MidWater::getID())->getState()->water(plant) == 20);
    delete fac;
    delete plant;
}
TEST_CASE("Singleton basics with water strategy testing and with state testing")
{

    LivingPlant *plant = new Tree();

    Inventory *inv = Inventory::getInstance();
    CHECK(inv == Inventory::getInstance());
    CHECK(inv->getWaterFly(LowWater::getID())->getState()->water(plant) == 10);
    CHECK(Inventory::getInstance()->getWaterFly(MidWater::getID())->getState()->water(plant) == 20);

    for (int i = 0; i < 7; i++)
    {
        Inventory::getInstance()->getStates(Seed::getID())->getState()->grow(plant);
    };
    CHECK(plant->getAge() == 7);

    SUBCASE("Correct exception handling")
    {
        CHECK(Inventory::getInstance()->getWaterFly(5000)->getState()->water(plant) == 10);

        CHECK(*Inventory::getInstance()->getString("Insert1")->getState() == "Insert1");
    }

    delete plant;

    delete inv;
}

TEST_CASE("Testing decorator")
{
    LivingPlant *plant = new Tree();
    plant->addAttribute(new Autumn());
    delete Inventory::getInstance();
    delete plant->getDecorator();

    delete Inventory::getInstance();
}

TEST_CASE("Testing WaterStrategy implementations")
{
    LivingPlant *plant = new Tree();

    SUBCASE("LowWater strategy")
    {
        WaterStrategy *lowWater = new LowWater();
        CHECK(lowWater->water(plant) == 10);
        delete lowWater;
    }

    SUBCASE("MidWater strategy")
    {
        WaterStrategy *midWater = new MidWater();
        CHECK(midWater->water(plant) == 20);
        delete midWater;
    }

    SUBCASE("HighWater strategy")
    {
        WaterStrategy *highWater = new HighWater();
        CHECK(highWater->water(plant) == 30);
        delete highWater;
    }

    SUBCASE("AlternatingWater strategy")
    {
        WaterStrategy *altWater = new AlternatingWater();
        int first = altWater->water(plant);
        int second = altWater->water(plant);
        CHECK(first != second);
        CHECK((first >= 2 && first <= 5));
        CHECK((second >= 2 && second <= 5));
        delete altWater;
    }

    delete plant;
}

TEST_CASE("Testing SunStrategy implementations")
{
    LivingPlant *plant = new Tree();

    SUBCASE("LowSun strategy")
    {
        SunStrategy *lowSun = new LowSun();
        CHECK(lowSun->addSun(plant) == 6);
        delete lowSun;
    }

    SUBCASE("MidSun strategy")
    {
        SunStrategy *midSun = new MidSun();
        CHECK(midSun->addSun(plant) == 25);
        delete midSun;
    }

    SUBCASE("HighSun strategy")
    {
        SunStrategy *highSun = new HighSun();
        CHECK(highSun->addSun(plant) == 72);
        delete highSun;
    }

    SUBCASE("AlternatingSun strategy")
    {
        SunStrategy *altSun = new AlternatingSun();
        int first = altSun->addSun(plant);
        int second = altSun->addSun(plant);
        CHECK(first != second);
        CHECK((first == 16 || first == 36));
        CHECK((second == 16 || second == 36));
        delete altSun;
    }

    delete plant;
}

TEST_CASE("Testing strategy switching in LivingPlant")
{
    LivingPlant *plant = new LivingPlant("Test Plant", 25.0, 5, 5);

    SUBCASE("Water strategy switching")
    {
        plant->setWaterLevel(0);
        plant->setWaterStrategy(1);
        plant->water();

        CHECK(plant->getWaterLevel() == 10);

        plant->setWaterLevel(0);
        plant->setWaterStrategy(2);
        plant->water();
        CHECK(plant->getWaterLevel() == 20);

        plant->setWaterLevel(0);
        plant->setWaterStrategy(3);
        plant->water();
        CHECK(plant->getWaterLevel() == 30);
    }

    SUBCASE("Sun strategy switching")
    {
        plant->setSunExposure(0);
        plant->setSunStrategy(1);
        plant->setOutside();
        CHECK(plant->getSunExposure() == 6);

        plant->setSunExposure(0);
        plant->setSunStrategy(2);
        plant->setOutside();
        CHECK(plant->getSunExposure() == 25);

        plant->setSunExposure(0);
        plant->setSunStrategy(3);
        plant->setOutside();
        CHECK(plant->getSunExposure() == 72);
    }

    delete plant;
}

TEST_CASE("Testing MaturityState transitions and behavior")
{
    Inventory *inv = Inventory::getInstance();
    LivingPlant *plant = new Tree();

    SUBCASE("Seed -> Vegetative transition")
    {
        plant->setAge(6);
        plant->setHealth(50);

        plant->setWaterLevel(56);
        plant->setSunExposure(30);
        plant->setMaturity(Seed::getID());

        inv->getStates(Seed::getID())->getState()->grow(plant);

        CHECK(plant->getWaterLevel() == 25);
        CHECK(plant->getSunExposure() == 50);
        CHECK(plant->getHealth() >= 50);
    }

    SUBCASE("Vegetative -> Mature transition")
    {
        plant->setAge(29);
        plant->setHealth(60);
        plant->setWaterLevel(50);
        plant->setSunExposure(50);
        plant->setMaturity(Vegetative::getID());

        inv->getStates(Vegetative::getID())->getState()->grow(plant);

        CHECK(plant->getWaterLevel() == 40);
        CHECK(plant->getSunExposure() == 60);
        CHECK(plant->getHealth() >= 60);
    }

    SUBCASE("Mature -> Dead transition by age")
    {
        plant->setAge(119);
        plant->setHealth(10);
        plant->setWaterLevel(40);
        plant->setSunExposure(40);
        plant->setMaturity(Mature::getID());

        inv->getStates(Mature::getID())->getState()->grow(plant);

        CHECK(plant->getWaterLevel() == 0);
        CHECK(plant->getSunExposure() == 0);
        CHECK(plant->getHealth() == 0);
    }

    SUBCASE("Dead state grow increments age only and keeps zeros")
    {
        plant->setAge(120);
        plant->setHealth(0);
        plant->setWaterLevel(0);
        plant->setSunExposure(0);
        plant->setMaturity(Dead::getID());

        inv->getStates(Dead::getID())->getState()->grow(plant);

        CHECK(plant->getAge() == 121);
        CHECK(plant->getWaterLevel() == 0);
        CHECK(plant->getHealth() == 0);
    }

    delete plant;
}

// ============================================================================
// ITERATOR PATTERN COMPREHENSIVE TEST SUITE
// ============================================================================
// These tests ensure stable iterator functionality with Flyweight integration.
// Tests cover: PlantIterator, SeasonIterator (with Flyweight pointer comparison),
//              nested hierarchies, edge cases, constructor overloads, and memory efficiency
// ============================================================================
// KEY IMPLEMENTATION DETAILS:
// - SeasonIterator uses Flyweight<std::string*>* for season comparison
// - Direct pointer comparison (O(1)) instead of string comparison (O(n))
// - AggSeason supports both string and Flyweight pointer constructors
// - Flyweight pattern ensures same season strings share same pointer
// ============================================================================

#include "iterator/Iterator.h"
#include "iterator/PlantIterator.h"
#include "iterator/SeasonIterator.h"
#include "iterator/AggPlant.h"
#include "iterator/AggSeason.h"
#include "composite/PlantGroup.h"
#include "prototype/Succulent.h"
#include "prototype/Tree.h"
#include "prototype/Shrub.h"
#include "prototype/Herb.h"
#include <vector>

// ============================================================================
// TEST HELPER FUNCTIONS
// ============================================================================

/**
 * @brief Counts the total number of plants returned by an iterator
 * @param iter Iterator to count (will be reset with first())
 * @return Number of plants iterated
 */
int countIteratorResults(Iterator *iter)
{
    int count = 0;
    iter->first();
    while (!iter->isDone())
    {
        count++;
        iter->next();
    }
    return count;
}

/**
 * @brief Collects all plants from an iterator into a vector
 * @param iter Iterator to collect from (will be reset with first())
 * @return Vector of pointers to LivingPlants
 */
std::vector<LivingPlant *> collectPlants(Iterator *iter)
{
    std::vector<LivingPlant *> plants;
    iter->first();
    while (!iter->isDone())
    {
        plants.push_back(iter->currentItem());
        iter->next();
    }
    return plants;
}

/**
 * @brief Creates a test plant with specified season
 * @param season Season name string
 * @return Pointer to created LivingPlant (Succulent)
 *
 * Note: Uses Flyweight pattern via inv->getString(season) to ensure
 * all plants with the same season share the same Flyweight pointer.
 */
LivingPlant *createPlantWithSeason(const std::string &season)
{
    Inventory *inv = Inventory::getInstance();
    LivingPlant *plant = new Succulent();
    plant->setSeason(inv->getString(season));
    return plant;
}

// ============================================================================
// PLANTITERATOR BASIC TESTS
// ============================================================================

TEST_CASE("PlantIterator - Empty collection")
{
    std::list<PlantComponent *> emptyList;
    AggPlant *agg = new AggPlant(&emptyList);
    Iterator *iter = agg->createIterator();

    SUBCASE("isDone() returns true immediately for empty collection")
    {
        CHECK(iter->isDone() == true);
    }

    SUBCASE("currentItem() returns nullptr for empty collection")
    {
        CHECK(iter->currentItem() == nullptr);
    }

    SUBCASE("Calling next() on empty collection has no effect")
    {
        iter->next();
        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);
    }

    delete iter;
    delete agg;
}

TEST_CASE("PlantIterator - Single plant")
{
    Inventory *inv = Inventory::getInstance();
    LivingPlant *plant = new Succulent();
    plant->setSeason(inv->getString("Spring"));

    std::list<PlantComponent *> plantList;
    plantList.push_back(plant);

    AggPlant *agg = new AggPlant(&plantList);
    Iterator *iter = agg->createIterator();

    SUBCASE("first() positions at the plant")
    {
        iter->first();
        CHECK(iter->isDone() == false);
        CHECK(iter->currentItem() == plant);
    }

    SUBCASE("next() after single plant makes isDone() true")
    {
        iter->first();
        iter->next();
        CHECK(iter->isDone() == true);
        CHECK(iter->currentItem() == nullptr);
    }

    SUBCASE("Iteration sequence is correct")
    {
        iter->first();
        CHECK(iter->currentItem() == plant);
        iter->next();
        CHECK(iter->isDone() == true);
    }

    delete iter;
    delete agg;
    delete plant;
}

TEST_CASE("PlantIterator - Multiple plants in flat list")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant1 = new Succulent();
    plant1->setSeason(inv->getString("Spring"));
    LivingPlant *plant2 = new Tree();
    plant2->setSeason(inv->getString("Summer"));
    LivingPlant *plant3 = new Shrub();
    plant3->setSeason(inv->getString("Autumn"));

    std::list<PlantComponent *> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);
    plantList.push_back(plant3);

    AggPlant *agg = new AggPlant(&plantList);
    Iterator *iter = agg->createIterator();

    SUBCASE("Count returns correct number")
    {
        CHECK(countIteratorResults(iter) == 3);
    }

    SUBCASE("Iteration returns all plants in order")
    {
        std::vector<LivingPlant *> collected = collectPlants(iter);
        CHECK(collected.size() == 3);
        CHECK(collected[0] == plant1);
        CHECK(collected[1] == plant2);
        CHECK(collected[2] == plant3);
    }

    SUBCASE("Manual iteration works correctly")
    {
        iter->first();
        CHECK(iter->currentItem() == plant1);
        iter->next();
        CHECK(iter->currentItem() == plant2);
        iter->next();
        CHECK(iter->currentItem() == plant3);
        iter->next();
        CHECK(iter->isDone() == true);
    }

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
    delete plant3;
}

TEST_CASE("PlantIterator - Mixed plant types")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *succulent = new Succulent();
    succulent->setSeason(inv->getString("Spring"));
    LivingPlant *tree = new Tree();
    tree->setSeason(inv->getString("Summer"));
    LivingPlant *shrub = new Shrub();
    shrub->setSeason(inv->getString("Autumn"));
    LivingPlant *herb = new Herb();
    herb->setSeason(inv->getString("Winter"));

    std::list<PlantComponent *> plantList;
    plantList.push_back(succulent);
    plantList.push_back(tree);
    plantList.push_back(shrub);
    plantList.push_back(herb);

    AggPlant *agg = new AggPlant(&plantList);
    Iterator *iter = agg->createIterator();

    CHECK(countIteratorResults(iter) == 4);

    std::vector<LivingPlant *> collected = collectPlants(iter);
    CHECK(collected.size() == 4);
    CHECK(collected[0] == succulent);
    CHECK(collected[1] == tree);
    CHECK(collected[2] == shrub);
    CHECK(collected[3] == herb);

    delete iter;
    delete agg;
    delete succulent;
    delete tree;
    delete shrub;
    delete herb;
}

// ============================================================================
// SEASONITERATOR BASIC TESTS
// ============================================================================
// These tests verify SeasonIterator's Flyweight-based season filtering.
// Uses direct Flyweight pointer comparison for O(1) season matching.
// ============================================================================

TEST_CASE("SeasonIterator - Empty collection with season filter")
{
    Inventory *inv = Inventory::getInstance();
    std::list<PlantComponent *> emptyList;

    // Using Flyweight pointer constructor
    AggSeason *agg = new AggSeason(&emptyList, inv->getString("Spring"));
    Iterator *iter = agg->createIterator();

    CHECK(iter->isDone() == true);
    CHECK(iter->currentItem() == nullptr);

    delete iter;
    delete agg;
}

TEST_CASE("SeasonIterator - Single matching plant")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant = createPlantWithSeason("Spring");
    std::list<PlantComponent *> plantList;
    plantList.push_back(plant);

    AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
    Iterator *iter = agg->createIterator();

    SUBCASE("Returns the matching plant")
    {
        iter->first();
        CHECK(iter->isDone() == false);
        CHECK(iter->currentItem() == plant);
    }

    SUBCASE("Becomes done after the single match")
    {
        iter->first();
        iter->next();
        CHECK(iter->isDone() == true);
    }

    delete iter;
    delete agg;
    delete plant;
}

TEST_CASE("SeasonIterator - Single non-matching plant")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant = createPlantWithSeason("Summer");
    std::list<PlantComponent *> plantList;
    plantList.push_back(plant);

    AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
    Iterator *iter = agg->createIterator();

    CHECK(iter->isDone() == true);
    CHECK(iter->currentItem() == nullptr);

    delete iter;
    delete agg;
    delete plant;
}

TEST_CASE("SeasonIterator - Multiple matching plants")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant1 = createPlantWithSeason("Spring");
    LivingPlant *plant2 = createPlantWithSeason("Spring");
    LivingPlant *plant3 = createPlantWithSeason("Spring");

    std::list<PlantComponent *> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);
    plantList.push_back(plant3);

    AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
    Iterator *iter = agg->createIterator();

    CHECK(countIteratorResults(iter) == 3);

    std::vector<LivingPlant *> collected = collectPlants(iter);
    CHECK(collected.size() == 3);
    CHECK(collected[0] == plant1);
    CHECK(collected[1] == plant2);
    CHECK(collected[2] == plant3);

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
    delete plant3;
}

TEST_CASE("SeasonIterator - Mixed seasons with filtering")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *spring1 = createPlantWithSeason("Spring");
    LivingPlant *summer1 = createPlantWithSeason("Summer");
    LivingPlant *spring2 = createPlantWithSeason("Spring");
    LivingPlant *autumn1 = createPlantWithSeason("Autumn");

    std::list<PlantComponent *> plantList;
    plantList.push_back(spring1);
    plantList.push_back(summer1);
    plantList.push_back(spring2);
    plantList.push_back(autumn1);

    // Note: All "Spring" plants share the same Flyweight pointer, enabling O(1) comparison
    SUBCASE("Filter for Spring returns only Spring plants")
    {
        AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();

        std::vector<LivingPlant *> collected = collectPlants(iter);
        CHECK(collected.size() == 2);
        CHECK(collected[0] == spring1);
        CHECK(collected[1] == spring2);

        delete iter;
        delete agg;
    }

    SUBCASE("Filter for Summer returns only Summer plants")
    {
        AggSeason *agg = new AggSeason(&plantList, inv->getString("Summer"));
        Iterator *iter = agg->createIterator();

        std::vector<LivingPlant *> collected = collectPlants(iter);
        CHECK(collected.size() == 1);
        CHECK(collected[0] == summer1);

        delete iter;
        delete agg;
    }

    SUBCASE("Filter for Autumn returns only Autumn plants")
    {
        AggSeason *agg = new AggSeason(&plantList, inv->getString("Autumn"));
        Iterator *iter = agg->createIterator();

        std::vector<LivingPlant *> collected = collectPlants(iter);
        CHECK(collected.size() == 1);
        CHECK(collected[0] == autumn1);

        delete iter;
        delete agg;
    }

    delete spring1;
    delete summer1;
    delete spring2;
    delete autumn1;
}

TEST_CASE("SeasonIterator - No matching plants")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *summer1 = createPlantWithSeason("Summer");
    LivingPlant *summer2 = createPlantWithSeason("Summer");
    LivingPlant *summer3 = createPlantWithSeason("Summer");

    std::list<PlantComponent *> plantList;
    plantList.push_back(summer1);
    plantList.push_back(summer2);
    plantList.push_back(summer3);

    AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
    Iterator *iter = agg->createIterator();

    CHECK(iter->isDone() == true);
    CHECK(iter->currentItem() == nullptr);
    CHECK(countIteratorResults(iter) == 0);

    delete iter;
    delete agg;
    delete summer1;
    delete summer2;
    delete summer3;
}

TEST_CASE("SeasonIterator - All four seasons")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *spring = createPlantWithSeason("Spring");
    LivingPlant *summer = createPlantWithSeason("Summer");
    LivingPlant *autumn = createPlantWithSeason("Autumn");
    LivingPlant *winter = createPlantWithSeason("Winter");

    std::list<PlantComponent *> plantList;
    plantList.push_back(spring);
    plantList.push_back(summer);
    plantList.push_back(autumn);
    plantList.push_back(winter);

    SUBCASE("Filter Spring")
    {
        AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 1);
        CHECK(collectPlants(iter)[0] == spring);
        delete iter;
        delete agg;
    }

    SUBCASE("Filter Summer")
    {
        AggSeason *agg = new AggSeason(&plantList, inv->getString("Summer"));
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 1);
        CHECK(collectPlants(iter)[0] == summer);
        delete iter;
        delete agg;
    }

    SUBCASE("Filter Autumn")
    {
        AggSeason *agg = new AggSeason(&plantList, inv->getString("Autumn"));
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 1);
        CHECK(collectPlants(iter)[0] == autumn);
        delete iter;
        delete agg;
    }

    SUBCASE("Filter Winter")
    {
        AggSeason *agg = new AggSeason(&plantList, inv->getString("Winter"));
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 1);
        CHECK(collectPlants(iter)[0] == winter);
        delete iter;
        delete agg;
    }

    delete spring;
    delete summer;
    delete autumn;
    delete winter;
}

// ============================================================================
// SEASONITERATOR FLYWEIGHT IMPLEMENTATION TESTS
// ============================================================================

TEST_CASE("SeasonIterator - String constructor overload")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *spring1 = createPlantWithSeason("Spring");
    LivingPlant *summer1 = createPlantWithSeason("Summer");
    LivingPlant *spring2 = createPlantWithSeason("Spring");

    std::list<PlantComponent *> plantList;
    plantList.push_back(spring1);
    plantList.push_back(summer1);
    plantList.push_back(spring2);

    SUBCASE("String constructor filters correctly")
    {
        // Using string constructor (internally converts to Flyweight)
        AggSeason *agg = new AggSeason(&plantList, "Spring");
        Iterator *iter = agg->createIterator();

        std::vector<LivingPlant *> collected = collectPlants(iter);
        CHECK(collected.size() == 2);
        CHECK(collected[0] == spring1);
        CHECK(collected[1] == spring2);

        delete iter;
        delete agg;
    }

    SUBCASE("Flyweight constructor filters correctly")
    {
        // Using Flyweight constructor
        AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();

        std::vector<LivingPlant *> collected = collectPlants(iter);
        CHECK(collected.size() == 2);
        CHECK(collected[0] == spring1);
        CHECK(collected[1] == spring2);

        delete iter;
        delete agg;
    }

    SUBCASE("Both constructors produce identical results")
    {
        // String constructor
        AggSeason *aggString = new AggSeason(&plantList, "Spring");
        Iterator *iterString = aggString->createIterator();
        int countString = countIteratorResults(iterString);

        // Flyweight constructor
        AggSeason *aggFly = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iterFly = aggFly->createIterator();
        int countFly = countIteratorResults(iterFly);

        CHECK(countString == countFly);
        CHECK(countString == 2);

        delete iterString;
        delete aggString;
        delete iterFly;
        delete aggFly;
    }

    delete spring1;
    delete summer1;
    delete spring2;
}

TEST_CASE("SeasonIterator - Flyweight pointer comparison")
{
    Inventory *inv = Inventory::getInstance();

    SUBCASE("Same season string yields same Flyweight pointer")
    {
        Flyweight<std::string *> *season1 = inv->getString("Spring");
        Flyweight<std::string *> *season2 = inv->getString("Spring");

        // Flyweight pattern ensures same pointer for same value
        CHECK(season1 == season2);
    }

    SUBCASE("Different season strings yield different Flyweight pointers")
    {
        Flyweight<std::string *> *spring = inv->getString("Spring");
        Flyweight<std::string *> *summer = inv->getString("Summer");

        CHECK(spring != summer);
    }

    SUBCASE("Flyweight pointer comparison enables O(1) filtering")
    {
        LivingPlant *plant1 = createPlantWithSeason("Spring");
        LivingPlant *plant2 = createPlantWithSeason("Spring");

        // Both plants should have same Flyweight pointer for "Spring"
        CHECK(plant1->getSeason() == plant2->getSeason());

        // And it should match the singleton's "Spring" Flyweight
        CHECK(plant1->getSeason() == inv->getString("Spring"));
        CHECK(plant2->getSeason() == inv->getString("Spring"));

        delete plant1;
        delete plant2;
    }

    SUBCASE("Iterator uses direct pointer comparison")
    {
        LivingPlant *spring1 = createPlantWithSeason("Spring");
        LivingPlant *spring2 = createPlantWithSeason("Spring");
        LivingPlant *summer1 = createPlantWithSeason("Summer");

        std::list<PlantComponent *> plantList;
        plantList.push_back(spring1);
        plantList.push_back(summer1);
        plantList.push_back(spring2);

        // Create iterator with Flyweight pointer
        Flyweight<std::string *> *springFly = inv->getString("Spring");
        AggSeason *agg = new AggSeason(&plantList, springFly);
        Iterator *iter = agg->createIterator();

        // Should find both spring plants via pointer comparison
        std::vector<LivingPlant *> collected = collectPlants(iter);
        CHECK(collected.size() == 2);
        CHECK(collected[0] == spring1);
        CHECK(collected[1] == spring2);

        delete iter;
        delete agg;
        delete spring1;
        delete spring2;
        delete summer1;
    }
}

TEST_CASE("SeasonIterator - Flyweight memory efficiency")
{
    Inventory *inv = Inventory::getInstance();

    SUBCASE("Multiple plants share season Flyweight")
    {
        // Create many plants with same season
        std::vector<LivingPlant *> plants;
        for (int i = 0; i < 10; i++)
        {
            plants.push_back(createPlantWithSeason("Spring"));
        }

        // All should point to same Flyweight
        Flyweight<std::string *> *firstSeason = plants[0]->getSeason();
        for (int i = 1; i < 10; i++)
        {
            CHECK(plants[i]->getSeason() == firstSeason);
        }

        // Cleanup
        for (LivingPlant *plant : plants)
        {
            delete plant;
        }
    }

    SUBCASE("Iterator aggregate shares Flyweight with plants")
    {
        LivingPlant *plant1 = createPlantWithSeason("Summer");
        LivingPlant *plant2 = createPlantWithSeason("Summer");

        std::list<PlantComponent *> plantList;
        plantList.push_back(plant1);
        plantList.push_back(plant2);

        // Create aggregate with same season Flyweight
        AggSeason *agg = new AggSeason(&plantList, "Summer");

        // The aggregate's internal targetSeason should match plants' seasons
        // (can't directly test private member, but iterator should find them)
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 2);

        delete iter;
        delete agg;
        delete plant1;
        delete plant2;
    }
}

// ============================================================================
// ITERATOR BEHAVIOR CONTRACT TESTS
// ============================================================================

TEST_CASE("Iterator behavior - first() resets iterator")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant1 = createPlantWithSeason("Spring");
    LivingPlant *plant2 = createPlantWithSeason("Spring");
    LivingPlant *plant3 = createPlantWithSeason("Spring");

    std::list<PlantComponent *> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);
    plantList.push_back(plant3);

    AggPlant *agg = new AggPlant(&plantList);
    Iterator *iter = agg->createIterator();

    SUBCASE("first() called twice positions at beginning both times")
    {
        iter->first();
        CHECK(iter->currentItem() == plant1);
        iter->first();
        CHECK(iter->currentItem() == plant1);
    }

    SUBCASE("first() after next() resets to beginning")
    {
        iter->first();
        iter->next();
        CHECK(iter->currentItem() == plant2);
        iter->first();
        CHECK(iter->currentItem() == plant1);
    }

    SUBCASE("first() after complete iteration allows re-iteration")
    {
        // First iteration
        int count1 = countIteratorResults(iter);
        CHECK(count1 == 3);
        CHECK(iter->isDone() == true);

        // Reset and iterate again
        iter->first();
        CHECK(iter->isDone() == false);
        int count2 = countIteratorResults(iter);
        CHECK(count2 == 3);
    }

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
    delete plant3;
}

TEST_CASE("Iterator behavior - next() at end stays at end")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant = createPlantWithSeason("Spring");
    std::list<PlantComponent *> plantList;
    plantList.push_back(plant);

    AggPlant *agg = new AggPlant(&plantList);
    Iterator *iter = agg->createIterator();

    iter->first();
    iter->next();
    CHECK(iter->isDone() == true);

    // Call next() multiple times at end
    iter->next();
    CHECK(iter->isDone() == true);
    CHECK(iter->currentItem() == nullptr);

    iter->next();
    CHECK(iter->isDone() == true);
    CHECK(iter->currentItem() == nullptr);

    delete iter;
    delete agg;
    delete plant;
}

TEST_CASE("Iterator behavior - currentItem() doesn't advance iterator")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant1 = createPlantWithSeason("Spring");
    LivingPlant *plant2 = createPlantWithSeason("Spring");

    std::list<PlantComponent *> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);

    AggPlant *agg = new AggPlant(&plantList);
    Iterator *iter = agg->createIterator();

    iter->first();
    LivingPlant *item1 = iter->currentItem();
    LivingPlant *item2 = iter->currentItem();
    LivingPlant *item3 = iter->currentItem();

    CHECK(item1 == plant1);
    CHECK(item2 == plant1);
    CHECK(item3 == plant1);
    CHECK(iter->isDone() == false);

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
}

TEST_CASE("Iterator behavior - isDone() accurately reflects state")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant1 = createPlantWithSeason("Spring");
    LivingPlant *plant2 = createPlantWithSeason("Spring");

    std::list<PlantComponent *> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);

    AggPlant *agg = new AggPlant(&plantList);
    Iterator *iter = agg->createIterator();

    SUBCASE("isDone() false when elements remain")
    {
        iter->first();
        CHECK(iter->isDone() == false);
        iter->next();
        CHECK(iter->isDone() == false);
    }

    SUBCASE("isDone() true after all elements exhausted")
    {
        iter->first();
        iter->next();
        iter->next();
        CHECK(iter->isDone() == true);
    }

    SUBCASE("isDone() false after first() resets")
    {
        iter->first();
        iter->next();
        iter->next();
        CHECK(iter->isDone() == true);
        iter->first();
        CHECK(iter->isDone() == false);
    }

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
}

// ============================================================================
// COMPARISON TESTS: PlantIterator vs SeasonIterator
// ============================================================================

TEST_CASE("PlantIterator vs SeasonIterator comparison")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *spring1 = createPlantWithSeason("Spring");
    LivingPlant *spring2 = createPlantWithSeason("Spring");
    LivingPlant *summer1 = createPlantWithSeason("Summer");
    LivingPlant *summer2 = createPlantWithSeason("Summer");
    LivingPlant *autumn1 = createPlantWithSeason("Autumn");

    std::list<PlantComponent *> plantList;
    plantList.push_back(spring1);
    plantList.push_back(summer1);
    plantList.push_back(spring2);
    plantList.push_back(summer2);
    plantList.push_back(autumn1);

    SUBCASE("PlantIterator returns all plants")
    {
        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 5);
        delete iter;
        delete agg;
    }

    SUBCASE("SeasonIterator count <= PlantIterator count")
    {
        AggPlant *aggAll = new AggPlant(&plantList);
        Iterator *iterAll = aggAll->createIterator();
        int allCount = countIteratorResults(iterAll);

        AggSeason *aggSpring = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iterSpring = aggSpring->createIterator();
        int springCount = countIteratorResults(iterSpring);

        CHECK(springCount <= allCount);
        CHECK(springCount == 2);
        CHECK(allCount == 5);

        delete iterAll;
        delete aggAll;
        delete iterSpring;
        delete aggSpring;
    }

    SUBCASE("SeasonIterator is subset of PlantIterator")
    {
        AggSeason *aggSpring = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iterSpring = aggSpring->createIterator();
        std::vector<LivingPlant *> springPlants = collectPlants(iterSpring);

        AggPlant *aggAll = new AggPlant(&plantList);
        Iterator *iterAll = aggAll->createIterator();
        std::vector<LivingPlant *> allPlants = collectPlants(iterAll);

        // Every spring plant should be in all plants
        for (LivingPlant *springPlant : springPlants)
        {
            bool found = false;
            for (LivingPlant *plant : allPlants)
            {
                if (plant == springPlant)
                {
                    found = true;
                    break;
                }
            }
            CHECK(found == true);
        }

        delete iterSpring;
        delete aggSpring;
        delete iterAll;
        delete aggAll;
    }

    delete spring1;
    delete spring2;
    delete summer1;
    delete summer2;
    delete autumn1;
}

// ============================================================================
// EDGE CASE TESTS
// ============================================================================

TEST_CASE("Edge case - Multiple iterators on same collection are independent")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant1 = createPlantWithSeason("Spring");
    LivingPlant *plant2 = createPlantWithSeason("Spring");
    LivingPlant *plant3 = createPlantWithSeason("Spring");

    std::list<PlantComponent *> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);
    plantList.push_back(plant3);

    AggPlant *agg = new AggPlant(&plantList);
    Iterator *iter1 = agg->createIterator();
    Iterator *iter2 = agg->createIterator();

    // Advance iter1
    iter1->first();
    iter1->next();
    CHECK(iter1->currentItem() == plant2);

    // iter2 should be independent
    iter2->first();
    CHECK(iter2->currentItem() == plant1);

    // Advance iter2
    iter2->next();
    iter2->next();
    CHECK(iter2->currentItem() == plant3);

    // iter1 should still be at plant2
    CHECK(iter1->currentItem() == plant2);

    delete iter1;
    delete iter2;
    delete agg;
    delete plant1;
    delete plant2;
    delete plant3;
}

TEST_CASE("Edge case - Iterator doesn't modify collection")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant1 = createPlantWithSeason("Spring");
    LivingPlant *plant2 = createPlantWithSeason("Spring");

    std::list<PlantComponent *> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);

    size_t originalSize = plantList.size();

    AggPlant *agg = new AggPlant(&plantList);
    Iterator *iter = agg->createIterator();

    // Iterate through collection
    countIteratorResults(iter);

    // Collection should be unchanged
    CHECK(plantList.size() == originalSize);
    CHECK(plantList.front() == plant1);
    CHECK(plantList.back() == plant2);

    delete iter;
    delete agg;
    delete plant1;
    delete plant2;
}

TEST_CASE("Edge case - All plants same season")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *plant1 = createPlantWithSeason("Spring");
    LivingPlant *plant2 = createPlantWithSeason("Spring");
    LivingPlant *plant3 = createPlantWithSeason("Spring");

    std::list<PlantComponent *> plantList;
    plantList.push_back(plant1);
    plantList.push_back(plant2);
    plantList.push_back(plant3);

    SUBCASE("Filtering for that season returns all")
    {
        AggSeason *agg = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 3);
        delete iter;
        delete agg;
    }

    SUBCASE("Filtering for different season returns none")
    {
        AggSeason *agg = new AggSeason(&plantList, inv->getString("Summer"));
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 0);
        delete iter;
        delete agg;
    }

    delete plant1;
    delete plant2;
    delete plant3;
}

TEST_CASE("Edge case - Each plant different season")
{
    Inventory *inv = Inventory::getInstance();

    LivingPlant *spring = createPlantWithSeason("Spring");
    LivingPlant *summer = createPlantWithSeason("Summer");
    LivingPlant *autumn = createPlantWithSeason("Autumn");
    LivingPlant *winter = createPlantWithSeason("Winter");

    std::list<PlantComponent *> plantList;
    plantList.push_back(spring);
    plantList.push_back(summer);
    plantList.push_back(autumn);
    plantList.push_back(winter);

    SUBCASE("PlantIterator returns all 4")
    {
        AggPlant *agg = new AggPlant(&plantList);
        Iterator *iter = agg->createIterator();
        CHECK(countIteratorResults(iter) == 4);
        delete iter;
        delete agg;
    }

    SUBCASE("Each season filter returns exactly 1")
    {
        AggSeason *aggSpring = new AggSeason(&plantList, inv->getString("Spring"));
        Iterator *iterSpring = aggSpring->createIterator();
        CHECK(countIteratorResults(iterSpring) == 1);
        delete iterSpring;
        delete aggSpring;

        AggSeason *aggSummer = new AggSeason(&plantList, inv->getString("Summer"));
        Iterator *iterSummer = aggSummer->createIterator();
        CHECK(countIteratorResults(iterSummer) == 1);
        delete iterSummer;
        delete aggSummer;

        AggSeason *aggAutumn = new AggSeason(&plantList, inv->getString("Autumn"));
        Iterator *iterAutumn = aggAutumn->createIterator();
        CHECK(countIteratorResults(iterAutumn) == 1);
        delete iterAutumn;
        delete aggAutumn;

        AggSeason *aggWinter = new AggSeason(&plantList, inv->getString("Winter"));
        Iterator *iterWinter = aggWinter->createIterator();
        CHECK(countIteratorResults(iterWinter) == 1);
        delete iterWinter;
        delete aggWinter;
    }

    delete spring;
    delete summer;
    delete autumn;
    delete winter;
}

// ============================================================================
// END OF ITERATOR TEST SUITE
// ============================================================================
// Note: Nested hierarchy tests are commented out pending PlantGroup::getPlants()
// implementation. These tests assume the refactor changes will be completed.
// Uncomment when PlantGroup::getPlants() is available.
// ============================================================================

/*
// ============================================================================
// NESTED HIERARCHY TESTS (Requires PlantGroup::getPlants())
// ============================================================================

TEST_CASE("Nested hierarchy - PlantGroup with plants") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Spring");
    LivingPlant* plant3 = createPlantWithSeason("Spring");

    PlantGroup* group = new PlantGroup();
    // Assuming PlantGroup has add() or similar method
    group->add(plant1);
    group->add(plant2);
    group->add(plant3);

    std::list<PlantComponent*> components;
    components.push_back(group);

    AggPlant* agg = new AggPlant(&components);
    Iterator* iter = agg->createIterator();

    CHECK(countIteratorResults(iter) == 3);

    delete iter;
    delete agg;
    delete group;
}

TEST_CASE("Nested hierarchy - 2 levels deep") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Summer");

    PlantGroup* innerGroup = new PlantGroup();
    innerGroup->add(plant1);
    innerGroup->add(plant2);

    LivingPlant* plant3 = createPlantWithSeason("Autumn");

    PlantGroup* outerGroup = new PlantGroup();
    outerGroup->add(innerGroup);
    outerGroup->add(plant3);

    std::list<PlantComponent*> components;
    components.push_back(outerGroup);

    AggPlant* aggAll = new AggPlant(&components);
    Iterator* iterAll = aggAll->createIterator();
    CHECK(countIteratorResults(iterAll) == 3);
    delete iterAll;
    delete aggAll;

    AggSeason* aggSpring = new AggSeason(&components, inv->getString("Spring"));
    Iterator* iterSpring = aggSpring->createIterator();
    CHECK(countIteratorResults(iterSpring) == 1);
    delete iterSpring;
    delete aggSpring;

    delete outerGroup;
}

TEST_CASE("Nested hierarchy - 3+ levels deep") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    PlantGroup* level3 = new PlantGroup();
    level3->add(plant1);

    LivingPlant* plant2 = createPlantWithSeason("Summer");
    PlantGroup* level2 = new PlantGroup();
    level2->add(level3);
    level2->add(plant2);

    LivingPlant* plant3 = createPlantWithSeason("Autumn");
    PlantGroup* level1 = new PlantGroup();
    level1->add(level2);
    level1->add(plant3);

    std::list<PlantComponent*> components;
    components.push_back(level1);

    AggPlant* agg = new AggPlant(&components);
    Iterator* iter = agg->createIterator();
    CHECK(countIteratorResults(iter) == 3);
    delete iter;
    delete agg;

    delete level1;
}

TEST_CASE("Nested hierarchy - Mixed plants and groups") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* plant1 = createPlantWithSeason("Spring");
    LivingPlant* plant2 = createPlantWithSeason("Summer");

    PlantGroup* group1 = new PlantGroup();
    group1->add(plant2);

    LivingPlant* plant3 = createPlantWithSeason("Autumn");

    std::list<PlantComponent*> components;
    components.push_back(plant1);
    components.push_back(group1);
    components.push_back(plant3);

    AggPlant* agg = new AggPlant(&components);
    Iterator* iter = agg->createIterator();

    std::vector<LivingPlant*> collected = collectPlants(iter);
    CHECK(collected.size() == 3);
    CHECK(collected[0] == plant1);
    CHECK(collected[1] == plant2);
    CHECK(collected[2] == plant3);

    delete iter;
    delete agg;
    delete group1;
}

TEST_CASE("Nested hierarchy - Empty nested groups") {
    PlantGroup* emptyInner = new PlantGroup();
    PlantGroup* outerGroup = new PlantGroup();
    outerGroup->add(emptyInner);

    std::list<PlantComponent*> components;
    components.push_back(outerGroup);

    AggPlant* agg = new AggPlant(&components);
    Iterator* iter = agg->createIterator();

    CHECK(iter->isDone() == true);
    CHECK(countIteratorResults(iter) == 0);

    delete iter;
    delete agg;
    delete outerGroup;
}

TEST_CASE("Nested hierarchy - Seasonal filtering with nesting") {
    Inventory* inv = Inventory::getInstance();

    LivingPlant* spring1 = createPlantWithSeason("Spring");
    LivingPlant* summer1 = createPlantWithSeason("Summer");

    PlantGroup* innerGroup = new PlantGroup();
    innerGroup->add(spring1);
    innerGroup->add(summer1);

    LivingPlant* spring2 = createPlantWithSeason("Spring");
    LivingPlant* summer2 = createPlantWithSeason("Summer");

    PlantGroup* outerGroup = new PlantGroup();
    outerGroup->add(innerGroup);
    outerGroup->add(spring2);
    outerGroup->add(summer2);

    std::list<PlantComponent*> components;
    components.push_back(outerGroup);

    AggSeason* aggSpring = new AggSeason(&components, inv->getString("Spring"));
    Iterator* iterSpring = aggSpring->createIterator();
    CHECK(countIteratorResults(iterSpring) == 2);
    delete iterSpring;
    delete aggSpring;

    AggSeason* aggSummer = new AggSeason(&components, inv->getString("Summer"));
    Iterator* iterSummer = aggSummer->createIterator();
    CHECK(countIteratorResults(iterSummer) == 2);
    delete iterSummer;
    delete aggSummer;

    delete outerGroup;
}
*/

TEST_CASE("Testing Builder Pattern Implementation")
{
    SUBCASE("Testing Director-Builder Interaction")
    {
        Builder *roseBuilder = new RoseBuilder();
        Director director(roseBuilder);
        director.construct();
        PlantComponent *rosePlant = director.getPlant();

        CHECK(rosePlant != nullptr);

        delete rosePlant->getDecorator();
        delete roseBuilder;
    }

    SUBCASE("Testing Rose Plant Properties")
    {
        Builder *roseBuilder = new RoseBuilder();
        Director director(roseBuilder);
        director.construct();
        PlantComponent *rosePlant = director.getPlant();
        std::string info = rosePlant->getInfo();
        CHECK(!info.empty());
        CHECK(info.find("Base Price") != std::string::npos);

        rosePlant->water();
        delete rosePlant->getDecorator();

        delete roseBuilder;
        delete Inventory::getInstance();
    }

    SUBCASE("Testing Cactus Builder")
    {
        Builder *cactusBuilder = new CactusBuilder();
        Director director(cactusBuilder);
        director.construct();
        PlantComponent *cactusPlant = director.getPlant();
        std::string info = cactusPlant->getInfo();
        CHECK(!info.empty());
        CHECK(info.find("Water Level") != std::string::npos);
        CHECK(info.find("Sun Exposure") != std::string::npos);

        cactusPlant->setOutside();

        delete cactusPlant->getDecorator();
        delete cactusBuilder;
    }

    SUBCASE("Testing Builder Pattern with Multiple Plants")
    {
        Builder *roseBuilder = new RoseBuilder();
        Builder *cactusBuilder = new CactusBuilder();
        Director director(roseBuilder);
        director.construct();
        PlantComponent *rosePlant = director.getPlant();
        Director director2(cactusBuilder);
        director2.construct();
        PlantComponent *cactusPlant = director2.getPlant();
        CHECK(rosePlant != nullptr);
        CHECK(cactusPlant != nullptr);
        CHECK(rosePlant->getInfo() != cactusPlant->getInfo());
        LivingPlant *roseLivingPlant = dynamic_cast<LivingPlant *>(rosePlant);
        LivingPlant *cactusLivingPlant = dynamic_cast<LivingPlant *>(cactusPlant);
        if (roseLivingPlant && cactusLivingPlant)
        {
            roseLivingPlant->setSunExposure(0);
            cactusLivingPlant->setSunExposure(0);
            rosePlant->setOutside();
            cactusPlant->setOutside();
            CHECK(cactusLivingPlant->getSunExposure() > roseLivingPlant->getSunExposure());
        }

        delete rosePlant->getDecorator();
        delete cactusPlant->getDecorator();

        delete roseBuilder;
        delete cactusBuilder;
        delete Inventory::getInstance();
    }

    SUBCASE("Testing Complete Builder Process")
    {
        Builder *roseBuilder = new RoseBuilder();
        Director director(roseBuilder);
        director.construct();
        PlantComponent *rosePlant = director.getPlant();
        LivingPlant *roseLivingPlant = dynamic_cast<LivingPlant *>(rosePlant);
        CHECK(roseLivingPlant != nullptr);
        if (roseLivingPlant)
        {
            int initialWater = roseLivingPlant->getWaterLevel();
            rosePlant->water();
            CHECK(roseLivingPlant->getWaterLevel() > initialWater);
            roseLivingPlant->setWaterLevel(0);
            rosePlant->water();
            CHECK(roseLivingPlant->getWaterLevel() >= 20);
        }

        delete rosePlant->getDecorator();
        delete roseBuilder;

        delete Inventory::getInstance();
    }
}

TEST_CASE("Testing load on system with many rose objects")
{

    SUBCASE("Testing load of 1_000")
    {
        cout << endl;

        Builder *builder = new RoseBuilder();
        Director *dir = new Director(builder);

        dir->construct();
        PlantGroup *mainInventory = Inventory::getInstance()->getInventory();

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000; i++)
        {
            mainInventory->addComponent(dir->getPlant());
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time to add 1000 plants: " << duration.count() << " seconds" << std::endl;

        delete builder;
        delete dir;
        delete Inventory::getInstance();
        cout << "All 1000 plants de-allocated" << endl;
    }
    SUBCASE("Testing load of 1_000_000")
    {
        cout << endl;

        Builder *builder = new RoseBuilder();
        Director *dir = new Director(builder);

        dir->construct();
        PlantGroup *mainInventory = Inventory::getInstance()->getInventory();

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000000; i++)
        {
            mainInventory->addComponent(dir->getPlant());
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time to add 1_000_000 plants: " << duration.count() << " seconds" << std::endl;

        delete builder;
        delete dir;
        delete Inventory::getInstance();
        cout << "All 1_000_000 plants de-allocated" << endl;
    }
    SUBCASE("Testing load of 10_000_000")
    {
        cout << endl;

        Builder *builder = new RoseBuilder();
        Director *dir = new Director(builder);

        dir->construct();
        PlantGroup *mainInventory = Inventory::getInstance()->getInventory();

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000000; i++)
        {
            mainInventory->addComponent(dir->getPlant());
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time to add 10_000_000 plants: " << duration.count() << " seconds" << std::endl;

        delete builder;
        delete dir;
        delete Inventory::getInstance();
        cout << "All 10_000_000 plants de-allocated" << endl;
    }
}
#include "AggSeason.h"
#include "../singleton/Singleton.h"

AggSeason::AggSeason(std::list<PlantComponent*>* plants, const std::string& season) : Aggregate(plants)
{
	// Convert string to Flyweight pointer via Singleton
	targetSeason = Inventory::getInstance()->getString(season);
}

AggSeason::AggSeason(std::list<PlantComponent*>* plants, Flyweight<std::string>* season) : Aggregate(plants)
{
	// Directly assign the Flyweight pointer
	targetSeason = season;
}

Iterator* AggSeason::createIterator()
{
	return new SeasonIterator(this);
}

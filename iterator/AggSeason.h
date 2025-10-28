#ifndef PHOTOSYNTECH_AGGSEASON_H
#define PHOTOSYNTECH_AGGSEASON_H

#include "Aggregate.h"
#include "SeasonIterator.h"
#include <list>
#include <string>
#include "../composite/PlantComponent.h"
#include "../flyweight/Flyweight.h"

/**
 * @brief Generic concrete aggregate for creating season-filtered plant iterators.
 *
 * Creates SeasonIterator instances that filter and return only plants matching
 * the specified target season. Stores the plant collection and provides access
 * to SeasonIterator through friend relationship.
 *
 * **System Role:**
 * Factory for season-specific inventory iteration. Produces SeasonIterator for browsing
 * plants suitable for any season (Spring, Summer, Autumn, Winter). Enables seasonal
 * browsing and category-specific customer shopping experiences.
 *
 * **Pattern Role:** Concrete Aggregate (seasonal iterator factory)
 *
 * **Related Patterns:**
 * - Aggregate: Implements iterator factory interface
 * - Iterator: Creates SeasonIterator instances (declared as friend)
 * - Decorator: Works with seasonal decorators for filtering
 * - Facade: Enables seasonal browsing through system
 *
 * **System Interactions:**
 * - Constructor stores reference to plant collection and target season
 * - createIterator() creates SeasonIterator
 * - Returns iterator pre-configured for seasonal filtering
 * - Used by seasonal browsing commands
 * - Replaces season-specific aggregate classes (AggSpring, AggSummer, etc.)
 *
 * @see Aggregate (abstract factory)
 * @see SeasonIterator (concrete iterator created, has friend access)
 */
class AggSeason : public Aggregate
{
	friend class SeasonIterator;

	private:
		/**
		 * @brief The target season for filtering as a Flyweight pointer.
		 * Shared across all instances filtering the same season for memory efficiency.
		 */
		Flyweight<std::string>* targetSeason;

	public:
		/**
		 * @brief Constructor that initializes the aggregate with a plant collection and target season string.
		 * Converts the season string to a Flyweight internally.
		 * @param plants Pointer to the list of PlantComponents to manage.
		 * @param season The target season string for filtering (e.g., "Spring", "Summer", "Autumn", "Winter").
		 */
		AggSeason(std::list<PlantComponent*>* plants, const std::string& season);

		/**
		 * @brief Constructor that initializes the aggregate with a plant collection and Flyweight season.
		 * @param plants Pointer to the list of PlantComponents to manage.
		 * @param season Flyweight pointer to the target season for filtering.
		 */
		AggSeason(std::list<PlantComponent*>* plants, Flyweight<std::string>* season);

		/**
		 * @brief Creates a season-filtered iterator for this aggregate's plant collection.
		 * @return Pointer to a SeasonIterator for season-filtered traversal.
		 */
		Iterator* createIterator();

		/**
		 * @brief Virtual destructor for proper cleanup.
		 */
		virtual ~AggSeason() {}
};

#endif //PHOTOSYNTECH_AGGSEASON_H

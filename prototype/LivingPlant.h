#ifndef LivingPlant_h
#define LivingPlant_h

#include <string>
#include "../composite/PlantComponent.h"
#include "../flyweight/Flyweight.h"

#include <sstream>
#include <iomanip>
#include "../strategy/WaterStrategy.h"
#include "../strategy/SunStrategy.h"
#include "../decorator/PlantAttributes.h"

/**
 * @brief Base class for all living plant objects in the Prototype pattern.
 *
 * Represents an individual plant (leaf node in the Composite pattern) with specific
 * characteristics like age, health, water level, and sun exposure. Manages strategies
 * for watering and sunlight, as well as maturity state. Serves as the Context for
 * State and Strategy patterns. Uses Flyweight pattern for shared immutable data.
 *
 * **System Role:**
 * This abstract base class is the context and storage for all plant lifecycle data.
 * It implements PlantComponent (Composite leaf) and enables deep cloning via the
 * clone() method for Prototype pattern. Holds references to Strategy (water/sun)
 * and State (maturity) flyweights for behavior delegation. Core entity in system.
 *
 * **Pattern Role:** Abstract Prototype (defines cloning interface)
 *
 * **Related Patterns:**
 * - PlantComponent: Leaf implementation of composite interface
 * - State Pattern: Delegates to MaturityState flyweights
 * - Strategy Pattern: Delegates to WaterStrategy and SunStrategy flyweights
 * - Flyweight Pattern: References to shared strategy and state objects
 * - Builder Pattern: Created by concrete builders during plant construction
 * - Decorator Pattern: Can be wrapped with PlantAttributes decorators
 * - Composite Pattern: Leaf node in plant hierarchy
 * - Observer Pattern: Subject notifications trigger on state changes
 *
 * **System Interactions:**
 * - Builder creates LivingPlant subclass instances
 * - Assigns water/sun strategies via setWaterStrategy(), setSunStrategy()
 * - Assigns maturity state via setMaturity()
 * - clone() creates deep copies for inventory mass production
 * - Decorators wrap instances without changing interface
 * - Strategies executed on water(), state processed by affectWater/Sunlight
 *
 * @see PlantComponent (Composite leaf interface)
 * @see State pattern (MaturityState context)
 * @see Strategy pattern (WaterStrategy, SunStrategy context)
 * @see Flyweight pattern (shared strategy/state references)
 * @see Decorator pattern (attributes wrap LivingPlant)
 */


class LivingPlant : public PlantComponent
{
protected:
	/**
	 * Name of the plant.
	 */
	Flyweight<std::string > *name;

	PlantComponent *decorator;
	int age;
	int health;
	int waterLevel;
	int sunExposure;

	/**
	 * Growing season for the plant.
	 */
	Flyweight<std::string > *season;

	Flyweight<MaturityState > *maturityState;
	Flyweight<WaterStrategy > *waterStrategy;
	Flyweight<SunStrategy > *sunStrategy;

public:
	/**
	 * @brief Constructs a living plant with basic attributes.
	 * @param name Name of the plant.
	 * @param price Base price of the plant.
	 * @param waterAffect Water affection value.
	 * @param sunAffect Sun affection value.
	 */
	LivingPlant(std::string name, double price, int waterAffect, int sunAffect);

	/**
	 * @brief Constructs a copy of an existing living plant.
	 *
	 * Performs a member-wise shallow copy for flyweights.
	 * and a deep copy for the decorator chain.
	 *
	 * @param other The living plant object to copy.
	 */
	LivingPlant(const LivingPlant &other);

	/**
	 * @brief Sets the age for this plant.
	 * @param age Integer age for the new age of the plant.
	 */
	void setAge(int age);

	/**
	 * @brief Sets the health for this plant.
	 * @param health Integer health for the new health of the plant.
	 */
	void setHealth(int health);

	/**
	 * @brief Sets the waterLevel for this plant.
	 * @param waterLevel Integer waterLevel for the new waterLevel of the plant.
	 */
	void setSeason(Flyweight<std::string> *season);

	/**
	 * @brief Sets the season for this plant.
	 * @param waterLevel Integer waterLevel for the new waterLevel of the plant.
	 */
	void setWaterLevel(int waterLevel);

	/**
	 * @brief Sets the sunExposure for this plant.
	 * @param sunExposure Integer sunExposure for the new sunExposure of the plant.
	 */
	void setSunExposure(int sunExposure);

	/**

	 * @brief Sets the water strategy for this plant.
	 * @param strategy Integer ID of the water strategy to use.
	 */
	void setWaterStrategy(int strategy);

	/**
	 * @brief Sets the sun strategy for this plant.
	 * @param strategy Integer ID of the sun strategy to use.
	 */
	void setSunStrategy(int strategy);

	/**
	 * @brief Sets the maturity state for this plant.
	 * @param state Integer ID of the maturity state.
	 */
	void setMaturity(int state);

	/**
	 * @brief Adds a decorator attribute to this plant.
	 * @param attribute Pointer to the PlantAttributes decorator to add.
	 */
	void addAttribute(PlantComponent *attribute) ;

	/**
	 * @brief Gets the season of the plant.
	 * @return Season of the plant.
	 */
	Flyweight<std::string > *getSeason();

	/**
	 * @brief Gets the component type (LIVING_PLANT).
	 *
	 * Enables efficient type identification without dynamic_cast.
	 *
	 * @return ComponentType::LIVING_PLANT
	 */
	ComponentType getType() const ;

	/**
	 * @brief Gets the age of the plant in months.
	 * @return Age in months.
	 */
	int getAge();

	/**
	 * @brief Gets plant name as a formatted string.
	 * @return String containing plant name.
	 */
	std::string getName() ;

	/**
	 * @brief Gets plant health as an Integer.
	 * @return Integer containing plant health.
	 */
	int getHealth();

	/**
	 * @brief Gets plant sunExposure as an Integer.
	 * @return Integer containing plant sunExposure.
	 */
	int getSunExposure();

	/**
	 * @brief Gets plant waterLevel as an Integer.
	 * @return Integer containing plant waterLevel.
	 */
	int getWaterLevel();

	/**
	 * @brief Gets the sunlight affection value.
	 * @return Integer representing sunlight impact.
	 */

	/**
	 * @brief Gets the water affection value.
	 * @return Integer representing water impact.
	 */

	/**
	 * @brief Subtracts waterAffect and sunAffect from waterLevel and sunExposure.
	 */
	void update() ;

	/**
	 * @brief Gets the sunlight affection value including decorator modifications.
	 * @return Integer representing total sunlight impact.
	 */
	int affectSunlight() ;

	/**
	 * @brief Gets the water affection value including decorator modifications.
	 * @return Integer representing total water impact.
	 */
	int affectWater() ;

	/**
	 * @brief Gets the price of this plant.
	 * @return Price in currency units.
	 */
	double getPrice() ;

	/**
	 * @brief Gets plant information as a string.
	 * @return String containing plant details.
	 */
	std::string getInfo() ;

	/**
	 * @brief Clones the plant creating a deep copy (Prototype pattern).
	 * @return Pointer to a new plant object that is a copy of this one.
	 */
	virtual PlantComponent *clone() ;

	/**
	 * @brief Waters the plant component.
	 */
	void water() ;

	/**
	 * @brief Sets the plant component to be outside. (Calls Sun Strategy)
	 */
	void setOutside() ;

	/**
	 * @brief Virtual destructor for proper cleanup of derived classes.
	 */
	virtual PlantComponent *getDecorator() ;

/**
 * @brief Virtual destructor for LivingPlant.
 *
 * Ensures proper cleanup of derived plant components and decorators.
 * Enables polymorphic deletion when using base class pointers.
 */
virtual ~LivingPlant();

/**
 * @brief Validates or adjusts the decorator chain for a plant component.
 *
 * Stub of the decorator, brought to the head of the clone
 *
 * @param mainDecorator Expected to be a season attribute 
 * @return Pointer to the corrected or validated PlantComponent.
 */
PlantComponent *correctShape(PlantComponent *mainDecorator);

/**
 * @brief Retrieves the water requirement value of the plant.
 *
 * Returns the hydration level needed by this plant component, which may be
 * influenced by strategy, maturity, or decoration layers.
 *
 * @return Integer representing water value.
 */
virtual int getWaterValue();

/**
 * @brief Retrieves the sunlight requirement value of the plant.
 *
 * Returns the sunlight exposure level required by this plant component,
 * potentially influenced by strategy, maturity, or decoration layers.
 *
 * @return Integer representing sunlight value.
 */
virtual int getSunlightValue();

/**
 * @brief Advances the internal state of the plant component by one tick.
 *
 * This method simulates time progression, allowing the plant to update
 * its maturity
 * 
 */
virtual void tick();

};

#endif

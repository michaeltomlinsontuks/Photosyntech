#ifndef Singleton_h
#define Singleton_h

using namespace std;
#include <string>
#include <vector>

#include "../flyweight/FlyweightFactory.h"

#include "../strategy/LowSun.h"
#include "../strategy/MidSun.h"
#include "../strategy/HighSun.h"
#include "../strategy/AlternatingSun.h"
#include "../strategy/LowWater.h"
#include "../strategy/MidWater.h"
#include "../strategy/HighWater.h"
#include "../strategy/AlternatingWater.h"

/**
 * @brief Singleton class managing global inventory and flyweight factories.
 *
 * Ensures only one instance exists and provides global access point through
 * getInstance(). Manages the shared inventory and flyweight factories for
 * efficient memory usage of shared immutable data (seasons, strategies).
 *
 * **System Role:**
 * This class serves as the central resource hub for the entire Photosyntech system.
 * It is responsible for:
 * - Maintaining the single global plant inventory (PlantGroup)
 * - Managing three flyweight factories for memory optimization
 * - Providing consistent access to shared resources throughout the application
 *
 * **Pattern Role:** Singleton (ensures single instance, provides global access point)
 *
 * **Related Patterns:**
 * - Flyweight: Manages three flyweight factories (strategy and season caches)
 * - Composite: Owns the root PlantGroup representing the inventory
 * - Builder: Director obtains strategy instances from singleton
 * - Facade: Accesses inventory and resources through singleton instance
 * - Command: Commands modify inventory state via singleton reference
 * - Observer: Plant group (managed by singleton) broadcasts notifications
 * - Iterator: Iterator factories obtain inventory collection from singleton
 *
 * **System Interactions:**
 * - All subsystems access singleton via getInstance() for shared resources
 * - Flyweight factories accessed for strategy and season object pooling
 * - Inventory (root PlantGroup) serves as hierarchical plant collection
 * - Resource lifetime managed by singleton until application termination
 *
 * @see PlantGroup (managed inventory root)
 * @see FlyweightFactory (template used for resource caching)
 * @see Builder (obtains strategies from singleton)
 * @see Facade (primary access point for singleton)
 */

class Customer;
class WaterStrategy;
class SunStrategy;
class MaturityState;
class PlantGroup;
class Staff;
class Customer;
class Inventory

{
private:
	static Inventory *instance;
	PlantGroup *inventory;
	FlyweightFactory<std::string, string *> *stringFactory;
	FlyweightFactory<int, WaterStrategy *> *waterStrategies;
	FlyweightFactory<int, SunStrategy *> *sunStrategies;
	FlyweightFactory<int, MaturityState *> *states;
	vector<Staff *> *staffList;
	vector<Customer *> *customerList;
	/**
	 * @brief Private constructor to prevent direct instantiation.
	 */
	Inventory();

public:
	/**
	 * @brief Gets the singleton instance.
	 * @return Pointer to the single Singleton instance.
	 */
	static Inventory *getInstance();

	/**
	 * @brief Gets a flyweight for a season name.
	 * @param season Season name string.
	 * @return Const pointer to the Flyweight wrapping the season string.
	 */
	Flyweight<std::string *> *getString(std::string season);

	/**
	 * @brief Gets a flyweight for a water strategy.
	 * @param level Integer identifier Class2for the water strategy level.
	 * @return Const pointer to the Flyweight wrapping the WaterStrategy.
	 */
	Flyweight<WaterStrategy *> *getWaterFly(int level);

	/**
	 * @brief Gets a flyweight for a sun strategy.
	 * @param level Integer identifier for the sun strategy level.
	 * @return Const pointer to the Flyweight wrapping the SunStrategy.
	 */
	Flyweight<SunStrategy *> *getSunFly(int level);

	/**
	 * @brief Gets the global plant inventory.
	 * @return Const pointer to the PlantGroup representing the inventory.
	 */
	PlantGroup *getInventory();

	/**
	 * @brief Deleted copy constructor to prevent copying.
	 */
	Inventory(const Inventory &) = delete;

	/**
	 * @brief Deleted assignment operator to prevent assignment.
	 */
	Inventory &operator=(const Inventory &) = delete;

	/**
	 * @brief to get a flyweight based on a specific id.
	 * @throws exception if there is an id given but no data aswell as no item in the factory to give.
	 */
	Flyweight<MaturityState *> *getStates(int id);

	/**
	 * @brief a getter for the customer list used in the system
	 */
	vector<Customer *> *getCustomers();
	/**
	 * @brief a getter for the Staff list used in the system
	 */
	vector<Staff *> *getStaff();


	/**
	 * @brief adds a staff member to the system
	 */
	void addStaff(Staff *staff);

	/**
	 * @brief adds a customer to the system
	 */
	void addCustomer(Customer *Customer);

	/**
	 * @brief the destructor for the inventory Last thing to be deleted in the main system.
	 */
	~Inventory();
};

#endif

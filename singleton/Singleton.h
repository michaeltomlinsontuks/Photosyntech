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
#include <thread>
#include <atomic>

/**
 * @class Inventory
 * @brief Singleton class managing global plant inventory and flyweight factories.
 *
 * The Inventory class serves as the centralized resource manager for the Photosyntech system.
 * It ensures a single instance exists and provides global access to shared resources such as
 * strategy flyweights, season strings, maturity states, and hierarchical plant inventory.
 *
 * ### Responsibilities:
 * - Maintain the global plant inventory (root PlantGroup)
 * - Manage flyweight factories for memory-efficient reuse of:
 *   - Season strings
 *   - Water strategies
 *   - Sun strategies
 *   - Maturity states
 * - Track system-wide staff and customer lists
 * - Provide thread-safe ticking mechanism for inventory updates
 *
 * ### Design Patterns:
 * - **Singleton**: Guarantees a single instance via `getInstance()`
 * - **Flyweight**: Caches reusable strategy/state objects
 * - **Composite**: Inventory is a tree of PlantGroup nodes
 * - **Builder**: Strategy instances retrieved from flyweight factories
 * - **Facade**: Centralized access to system resources
 * - **Command**: Inventory-modifying commands use singleton reference
 * - **Observer**: Inventory broadcasts updates to observers
 * - **Iterator**: Inventory provides iterable plant collections
 *
 * ### Multithreading:
 * - Background thread (`TickerThread`) periodically invokes `TickInventory()`
 * - Controlled via `startTicker()` and `stopTicker()` methods
 * - Thread-safe flag `on` governs lifecycle
 *
 * ### Related Components:
 * @see PlantGroup
 * @see FlyweightFactory
 * @see WaterStrategy, SunStrategy, MaturityState
 * @see Staff, Customer
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
	FlyweightFactory<std::string, string > *stringFactory;
	FlyweightFactory<int, WaterStrategy > *waterStrategies;
	FlyweightFactory<int, SunStrategy > *sunStrategies;
	FlyweightFactory<int, MaturityState > *states;
	vector<Staff *> *staffList;
	vector<Customer *> *customerList;
	/**
	 * @brief Private constructor to prevent direct instantiation.
	 */
	Inventory();
	// Multithreading components
	void TickInventory();
	static thread *TickerThread;
	static atomic<bool> on;
	// Multithreading components

public:
	/**
	 * @brief Retrieves the singleton instance of Inventory.
	 * @return Pointer to the single Inventory instance.
	 */
	static Inventory *getInstance();

	/**
	 * @brief Retrieves a flyweight for a season name.
	 * @param season Season name string.
	 * @return Flyweight wrapping the season string.
	 */
	Flyweight<std::string > *getString(std::string season);

	/**
	 * @brief Retrieves a flyweight for a water strategy level.
	 * @param level Integer identifier for water strategy.
	 * @return Flyweight wrapping the WaterStrategy instance.
	 */
	Flyweight<WaterStrategy > *getWaterFly(int level);

	/**
	 * @brief Retrieves a flyweight for a sun strategy level.
	 * @param level Integer identifier for sun strategy.
	 * @return Flyweight wrapping the SunStrategy instance.
	 */
	Flyweight<SunStrategy > *getSunFly(int level);

	/**
	 * @brief Retrieves a flyweight for a maturity state.
	 * @param id Integer identifier for maturity state.
	 * @return Flyweight wrapping the MaturityState instance.
	 * @throws std::runtime_error if id is invalid or not cached.
	 */
	Flyweight<MaturityState > *getStates(int id);

	/**
	 * @brief Gets the root plant inventory group.
	 * @return Pointer to the root PlantGroup.
	 */
	PlantGroup *getInventory();

	/**
	 * @brief Retrieves the list of registered customers.
	 * @return Pointer to vector of Customer pointers.
	 */
	vector<Customer *> *getCustomers();

	/**
	 * @brief Retrieves the list of registered staff members.
	 * @return Pointer to vector of Staff pointers.
	 */
	vector<Staff *> *getStaff();

	/**
	 * @brief Adds a staff member to the system.
	 * @param staff Pointer to Staff instance.
	 */
	void addStaff(Staff *staff);

	/**
	 * @brief Adds a customer to the system.
	 * @param Customer Pointer to Customer instance.
	 */
	void addCustomer(Customer *Customer);

	/**
	 * @brief Starts the background ticker thread.
	 * @return True if on was false false if otherwise
	 * @note Creates the thread if it does not yet exist
	 */
	static bool startTicker();

	/**
	 * @brief Stops the background ticker thread.
	 * @return True if it on was true, false if otherwise
	 * @note deletes the thread pointer
	 */
	static bool stopTicker();

	/**
	 * @brief Destructor. Cleans up all managed resources.
	 */
	~Inventory();
};
#endif
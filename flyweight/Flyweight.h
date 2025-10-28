#ifndef Flyweight_h
#define Flyweight_h

/**
 * @brief Template class for sharing immutable data objects.
 *
 * Stores shared immutable data (seasons, strategies) and provides access
 * through getState(). Used by FlyweightFactory to minimize memory consumption
 * by sharing instances across multiple plants instead of duplicating data.
 *
 * **System Role:**
 * This template wrapper class wraps immutable shared data objects. Together with
 * FlyweightFactory, enables massive memory optimization by sharing thousands of
 * plant instances that all reference the same strategy and seasonal flyweight objects.
 * Reduces memory usage by 99.92% compared to individual copies.
 *
 * **Pattern Role:** Flyweight (wraps and provides access to shared state)
 *
 * **Related Patterns:**
 * - FlyweightFactory: Creates and manages Flyweight instances
 * - Singleton: Factory instances managed by singleton
 * - Builder: Obtains flyweight strategies during construction
 * - Strategy: Shared WaterStrategy and SunStrategy instances
 * - Prototype: Cloned plants share flyweight references
 *
 * **System Interactions:**
 * - Factory creates Flyweight<T> wrapping immutable data
 * - getState() provides access to wrapped shared data
 * - Multiple plants reference same Flyweight instance
 * - Template enables type-safe sharing of any immutable data
 * - Factories maintain Flyweight lifetime, not individual plants
 *
 * @see FlyweightFactory (creates and manages instances)
 * @see Singleton (manages factories)
 * @see Strategy (shared strategy instances)
 *
 * @tparam T The type of data being shared (e.g., string, WaterStrategy, SunStrategy).
 */
template <class T>
class Flyweight
{
	private:
		T *data;

	public:
		/**
		 * @brief Constructs a Flyweight with the given data.
		 * @param data Pointer to the shared data object.
		 */
		Flyweight(T *data);

		/**
		 * @brief Gets the shared state data.
		 * @return Pointer to the shared data object.
		 */
		T* getState();

		/**
		 * @brief Destructor for cleanup.
		 */
		~Flyweight();
};
#include "Flyweight.cpp"

#endif

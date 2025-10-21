#ifndef PlantGroup_h
#define PlantGroup_h

#include <string>
#include <list>
#include "PlantComponent.h"
#include "../observer/Subject.h"
#include "../decorator/PlantAttributes.h"

/**
 * @brief Represents a group of plants in the Composite pattern.
 *
 * Acts as the Composite role, managing a collection of PlantComponent objects
 * (both individual plants and other groups). Implements operations to traverse
 * and manipulate entire plant collections uniformly. Also acts as a Subject
 * in the Observer pattern, notifying staff of plant care needs.
 */
class PlantGroup : public PlantComponent, public Subject
{
private:
	std::list<PlantComponent *> plants;

public:
	/**
	 * @brief Sets all plants in this group to be outside.
	 */
	void setOutside();

	/**
	 * @brief Waters all plants in this group.
	 */
	void water();

	/**
	 * @brief Gets information about all plants in this group.
	 * @return String containing details of all plants in the group.
	 */
	std::string getInfo();

	/**
	 * @brief Clones the plant group and all its contained plants.
	 * @return Pointer to a new PlantGroup that is a copy of this one.
	 */
	PlantComponent *clone();

	/**
	 * @brief Attaches an observer to receive notifications from this group.
	 * @param watcher Pointer to the Observer to attach.
	 */
	void attach(Observer *watcher);

	/**
	 * @brief Detaches an observer from this group.
	 * @param watcher Pointer to the Observer to detach.
	 */
	void detach(Observer *watcher);

	/**
	 * @brief Updates the state of this plant group.
	 */
	void update();

	/**
	 * @brief Gets the total water affection value for all plants in the group.
	 * @return Integer representing cumulative water impact.
	 */
	int affectWater();

	/**
	 * @brief Gets the total sunlight affection value for all plants in the group.
	 * @return Integer representing cumulative sunlight impact.
	 */
	int affectSunlight();

	/**
	 * @brief Notifies observers that plants in this group need water.
	 */
	void waterNeeded();

	/**
	 * @brief Notifies observers that plants in this group need sunlight.
	 */
	void sunlightNeeded();

	/**
	 * @brief Notifies observers that a plant's state has been updated.
	 */
	void stateUpdated();

	/**
	 * @brief Gets the total price of all plants in this group.
	 * @return Total price in currency units.
	 */
	double getPrice();

	/**
	 * @brief Adds an attribute decorator to all plants in this group.
	 * @param attribute Pointer to the PlantAttributes decorator to add.
	 */
	void addAttribute(PlantAttributes *attribute);

	virtual void tick();
};

#endif

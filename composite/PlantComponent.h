#ifndef PlantComponent_h
#define PlantComponent_h

#include <string>
class PlantAttributes;

/**
 * @brief Abstract base class representing a plant component in the Composite pattern.
 *
 * Declares the common interface for both individual plants and plant groups.
 * This is the Component role in the Composite pattern, enabling uniform treatment
 * of individual objects and compositions. All concrete plant types inherit from this class.
 *
 * **System Role:**
 * This abstract class defines the unified interface that all plant entities (individual
 * plants and plant groups) must implement. It enables clients to work with individual
 * plants and hierarchies of plant groups transparently through the same interface.
 * Core to hierarchical inventory organization.
 *
 * **Pattern Role:** Abstract Component (defines interface for leaves and composites)
 *
 * **Related Patterns:**
 * - LivingPlant: Leaf implementation of this interface
 * - PlantGroup: Composite implementation of this interface
 * - Decorator: PlantAttributes decorates PlantComponent
 * - Prototype: clone() enables copying plant hierarchies
 * - Composite Pattern: Enables tree traversal and operations
 * - Iterator: Iterators traverse components via this interface
 * - Observer: Subject implemented by PlantGroup (composite nodes)
 *
 * **System Interactions:**
 * - All plants and groups accessed through PlantComponent interface
 * - Operations (water, getInfo, getPrice) work uniformly on leaves and composites
 * - Decorators wrap components, preserving interface
 * - Iterators traverse hierarchies using this interface
 * - Singleton inventory root is PlantGroup (PlantComponent)
 *
 * @see LivingPlant (leaf implementation)
 * @see PlantGroup (composite implementation)
 * @see PlantAttributes (decorator for components)
 */
class PlantComponent
{
protected:
	double price;
	int affectWaterValue;
	int affectSunValue;

public:
	/**
	 * @brief Constructs a PlantComponent with basic attributes.
	 * @param name Name of the plant.
	 * @param price Base price of the plant.
	 * @param waterAffect Water affection value.
	 * @param sunAffect Sun affection value.
	 */
	PlantComponent(double price, int waterAffect, int sunAffect);
	/**
	 * @brief Clones the plant component (Prototype pattern).
	 * @return Pointer to a new plant object that is a copy of this one.
	 */
	virtual PlantComponent *clone() = 0;

	/**
	 * @brief Virtual destructor for proper cleanup of derived classes.
	 */
	virtual ~PlantComponent() {}

	/**
	 * @brief Waters the plant component.
	 */
	virtual void water() = 0;

	/**
	 * @brief Sets the plant component to be outside.(Calls Sun Strategy)
	 */
	virtual void setOutside() = 0;

	/**
	 * @brief Gets plant information as a string.
	 * @return String containing plant details.
	 */
	virtual std::string getInfo() = 0;

	/**
	 * @brief Gets plant name as a formatted string.
	 * @return String containing plant name.
	 */
	virtual std::string getName() = 0;

	/**
	 * @brief Gets the sunlight affection value for this component.
	 * @return Integer representing sunlight impact.
	 */
	virtual int getAffectSunlight() = 0;

	/**
	 * @brief Gets the water affection value for this component.
	 * @return Integer representing water impact.
	 */
	virtual int getAffectWater() = 0;

	/**
	 * @brief Gets the price of this plant component.
	 * @return Price in currency units.
	 */
	virtual double getPrice() = 0;

	/**
	 * @brief Adds an attribute decorator to this plant component.
	 * @param attribute Pointer to the PlantAttributes decorator to add.
	 */
	virtual void addAttribute(PlantAttributes *attribute) = 0;

	virtual void tick() = 0;
};

#endif
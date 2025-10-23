#include "customerDecorator/LargePot.h"
#include "customerDecorator/PlantCharm.h"
#include "customerDecorator/RedPot.h"
#include "customerDecorator/ShopThemedCharm.h"

#include "plantDecorator/Autumn.h"
#include "plantDecorator/LargeFlowers.h"
#include "plantDecorator/LargeLeaf.h"
#include "plantDecorator/LargeStem.h"
#include "plantDecorator/SmallFlowers.h"
#include "plantDecorator/SmallLeaf.h"
#include "plantDecorator/SmallStem.h"
#include "plantDecorator/Spring.h"
#include "plantDecorator/Summer.h"
#include "plantDecorator/Thorns.h"
#include "plantDecorator/Winter.h"

LargePot::LargePot()
    : PlantAttributes("Large Pot", 25.00, 0, 0)
{
}

LargePot::LargePot(const LargePot &other)
    : PlantAttributes(other)
{
}

PlantComponent *LargePot::clone()
{
    PlantComponent *clone = new LargePot();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}
PlantCharm::PlantCharm()
    : PlantAttributes("Standard Plant Charm", 10.00, 0, 0)
{
}

PlantCharm::PlantCharm(const PlantCharm &other)
    : PlantAttributes(other)
{
}

PlantComponent *PlantCharm::clone()
{
    PlantComponent *clone = new PlantCharm();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}

RedPot::RedPot()
    : PlantAttributes("Red Clay Pot", 15.00, 0, 0)
{
}

RedPot::RedPot(const RedPot &other)
    : PlantAttributes(other)
{
}

PlantComponent *RedPot::clone()
{
    PlantComponent *clone = new RedPot();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}

ShopThemedCharm::ShopThemedCharm()
    : PlantAttributes("Cute Charm", 20.00, 0, 0)
{
}

ShopThemedCharm::ShopThemedCharm(const ShopThemedCharm &other)
    : PlantAttributes(other)
{
}

PlantComponent *ShopThemedCharm::clone()
{
    PlantComponent *clone = new ShopThemedCharm();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}

Autumn::Autumn()
    : PlantAttributes("Autumn Season", 0.00, 0, 0)
{
}

Autumn::Autumn(const Autumn &other)
    : PlantAttributes(other)
{
}

PlantComponent *Autumn::clone()
{
    PlantComponent *clone = new Autumn();
    clone->addAttribute(this->nextComponent->clone());
    return clone->correctShape(clone);
}

LargeFlowers::LargeFlowers()
    : PlantAttributes("Large Flowers", 5.00, 1, 1)
{
}

LargeFlowers::LargeFlowers(const LargeFlowers &other)
    : PlantAttributes(other)
{
}

PlantComponent *LargeFlowers::clone()
{
    PlantComponent *clone = new LargeFlowers();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}

LargeLeaf::LargeLeaf()
    : PlantAttributes("Large Leaves", 3.00, 1, 0)
{
}

LargeLeaf::LargeLeaf(const LargeLeaf &other)
    : PlantAttributes(other)
{
}

PlantComponent *LargeLeaf::clone()
{
    PlantComponent *clone = new LargeLeaf();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}

LargeStem::LargeStem()
    : PlantAttributes("Large Stem", 2.00, 0, 0)
{
}

LargeStem::LargeStem(const LargeStem &other)
    : PlantAttributes(other)
{
}

PlantComponent *LargeStem::clone()
{
    PlantComponent *clone = new LargeStem();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}

SmallFlowers::SmallFlowers()

    : PlantAttributes("Small Flowers", 1.00, 0, 0)
{
}

SmallFlowers::SmallFlowers(const SmallFlowers &other)
    : PlantAttributes(other)
{
}

PlantComponent *SmallFlowers::clone()
{
    PlantComponent *clone = new SmallFlowers();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}

SmallLeaf::SmallLeaf()
    : PlantAttributes("Small Leaves", 1.00, -1, 0)
{
}

SmallLeaf::SmallLeaf(const SmallLeaf &other)
    : PlantAttributes(other)
{
}

PlantComponent *SmallLeaf::clone()
{
    PlantComponent *clone = new SmallLeaf();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}

SmallStem::SmallStem()
    : PlantAttributes("Small Stem", 0.00, 0, 0)
{
}

SmallStem::SmallStem(const SmallStem &other)
    : PlantAttributes(other)
{
}

PlantComponent *SmallStem::clone()
{
    PlantComponent *clone = new SmallStem();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}

Spring::Spring()
    : PlantAttributes("Spring Season", 0.00, 0, 0)
{
}

Spring::Spring(const Spring &other)
    : PlantAttributes(other)
{
}

PlantComponent *Spring::clone()
{
    PlantComponent *clone = new Spring();
    clone->addAttribute(this->nextComponent->clone());
    return clone->correctShape(clone);
}

Summer::Summer()
    : PlantAttributes("Summer Season", 0.00, 0, 0)
{
}

Summer::Summer(const Summer &other)
    : PlantAttributes(other)
{
}

PlantComponent *Summer::clone()
{
    PlantComponent *clone = new Summer();
    clone->addAttribute(this->nextComponent->clone());
    return clone->correctShape(clone);
}

Thorns::Thorns()
    : PlantAttributes("Thorns/Spikes", 5.00, 0, -1)
{
}

Thorns::Thorns(const Thorns &other)
    : PlantAttributes(other)
{
}

PlantComponent *Thorns::clone()
{
    PlantComponent *clone = new Thorns();
    clone->addAttribute(this->nextComponent->clone());
    return clone;
}

Winter::Winter()
    : PlantAttributes("Winter Season", 0.00, 0, 0)
{
}

Winter::Winter(const Winter &other)
    : PlantAttributes(other)
{
}

PlantComponent *Winter::clone()
{
    PlantComponent *clone = new Winter();
    clone->addAttribute(this->nextComponent->clone());
    return clone->correctShape(clone);
}
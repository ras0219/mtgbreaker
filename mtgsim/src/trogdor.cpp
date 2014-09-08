#include "trogdor.hpp"
#include "playerlogic.hpp"
#include "pl_utilities.hpp"
#include "core_card_set.hpp"

struct TrogdorLogic : PlayerLogicMixin<TrogdorLogic> {

};

const Deck trogdor_deck =
{
    {
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &Mountain::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data,
        &LightningBolt::cardclass_data
    }
};

PlayerLogic* make_trogdor_ai() { return new TrogdorLogic(); }
const Deck& make_trogdor_deck() {
    return trogdor_deck;
}
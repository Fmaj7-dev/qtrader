#include "simulation/simulation.h"

using namespace core;
using namespace core::simulation;

Simulation::Simulation( const Criteria& criteria, 
                        float capital,
                        float asset,
                        float buyAmnt,
                        float sellAmnt )
    :criteria_( criteria ),
    capital_( capital ),
    buyAmount_ ( buyAmnt ),
    sellAmount_( sellAmnt ),
    assetAmount_( asset )
{

}

/* void Simulation::setCriteria( const Criteria& criteria )
{
    criteria_ = criteria;
} */

void Simulation::setCapital( float capital )
{
    capital_ = capital;
}
void Simulation::setAsset( float asset )
{
    assetAmount_ = asset;
}

void Simulation::setBuyAmount( float buy )
{
    buyAmount_ = buy;
}

void Simulation::setSellAmount( float sell )
{
    sellAmount_ = sell;
}

float Simulation::getCapital() const
{
    return capital_;
}

float Simulation::getAsset() const
{
    return assetAmount_;
}

float Simulation::getBuyAmount() const
{
    return buyAmount_;
}

float Simulation::getSellAmount() const
{
    return sellAmount_;
}

const Criteria& Simulation::getCriteria() const
{
    return criteria_;
}

void Simulation::increaseCapital( float amount )
{
    capital_ += amount;
}
void Simulation::decreaseCapital( float amount )
{
    capital_ -= amount;
}
void Simulation::increaseAsset( float amount )
{
    assetAmount_ += amount;
}

void Simulation::decreaseAsset( float amount )
{
    assetAmount_ -= amount;
}


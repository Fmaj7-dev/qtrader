#ifndef SIMULATION_H
#define SIMULATION_H

#include "criteria.h"

namespace core
{
namespace simulation
{

class Simulation
{
public:
    Simulation( const Criteria& criteria, 
                float capital,
                float asset = 0,
                float buyAmnt = 100,
                float sellAmnt = 100 );

    //void setCriteria( const Criteria& criteria );
    void setCapital( float capital );
    void setAsset( float asset );
    void setBuyAmount( float buy );
    void setSellAmount( float sell );

    float getCapital() const;
    float getAsset() const;
    float getBuyAmount() const;
    float getSellAmount() const;
    const Criteria& getCriteria() const;

    void increaseCapital( float amount );
    void decreaseCapital( float amount );
    void increaseAsset( float amount );
    void decreaseAsset( float amount );

private:
    Criteria criteria_;

    // amount of capital
    float capital_;

    // buy amount of capital
    float buyAmount_;

    // sell amount ofa capital
    float sellAmount_;

    // amount of [BTC, gold, etc]
    float assetAmount_;
};

}
}
#endif
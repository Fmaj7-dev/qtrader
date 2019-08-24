#include "simulation/simulator.h"

using namespace core;
using namespace core::simulation;

Simulator::Simulator()
{
    
}

void Simulator::runSimulation( Simulation& simulation )
{
    const Criteria& criteria = simulation.getCriteria();

    Criteria::Condition buyCondition = criteria.buyConditions[0];
    Criteria::Condition sellCondition = criteria.sellConditions[0];

}
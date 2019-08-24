#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "simulation.h"

namespace core
{
namespace simulation
{

class Simulator 
{
public:
    Simulator();
    void runSimulation( Simulation& simulation );
};

}
}
#endif
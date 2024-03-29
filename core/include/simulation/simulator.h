#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "seriesrepository.h"
#include "simulation.h"

namespace core
{
namespace simulation
{

class Simulator 
{
public:
    Simulator( SeriesRepository& repository );
    void runSimulation( Simulation& simulation, int begin = 0, int end = 0 );
    void sellStock( Simulation& simulation );

private:
    SeriesRepository& repo_;
};

}
}
#endif
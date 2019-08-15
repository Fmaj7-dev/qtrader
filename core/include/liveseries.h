#ifndef LIVESERIES_H
#define LIVESERIES_H

#include <string>
#include <vector>
#include <ctime>

class LiveTerm
{
public:
    unsigned int id;
    std::time_t time;
    std::string hTime;
    float value;
};

class LiveSeries
{
public:
    LiveSeries( std::string name );

    std::vector< LiveTerm > values;
    
private:
    std::string name_;
};

#endif
#ifndef SIMPLEMOVINGAVERAGE_H
#define SIMPLEMOVINGAVERAGE_H

#include <vector>

namespace core
{
namespace analysis
{

class SimpleMovingAverageTerm
{
public:
    std::time_t time;
    float value;
};

using SMAValues = std::vector< SimpleMovingAverageTerm >;

class SimpleMovingAverage
{
public:
    SimpleMovingAverage();
    void calculate( const LiveSeries& liveSeries, int n );

    const SMAValues& getValues() const;

private:
    SMAValues values_;
};
}
}

#endif
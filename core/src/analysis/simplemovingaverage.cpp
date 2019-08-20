#include "liveseries.h"
#include "simplemovingaverage.h"
#include "utils/logger.h"

SimpleMovingAverage::SimpleMovingAverage()
{

}

void SimpleMovingAverage::calculate( const LiveSeries& liveSeries, int n )
{
    auto inputLength = liveSeries.values.size();
    values_.resize( inputLength );

    // circular buffer filled with zeros
    std::vector< float > tempBuffer(n, 0);
    // pointer to oldest element
    int oldest = 0;
    // current sum of elements in buffer
    float currentSum = 0;
    bool filled = false;

    for (auto i = 0; i < inputLength; ++i)
    {
        // remove old element from sum
        currentSum -= tempBuffer[oldest];

        // push new value in buffer
        auto newValue = liveSeries.values[i].value;
        auto newTime = liveSeries.values[i].time;
        tempBuffer[oldest] = newValue;

        // increment pointer
        oldest = ++oldest%n;

        // add new element to sum
        currentSum += newValue;

        // filled will be false during the initial fill, after that always true
        if ( oldest == 0 )
            filled = true;

        // calculate average (first n times will be different)
        float smaValue;
        if( filled )
             smaValue = currentSum/n;
        else
            smaValue = currentSum/oldest;
        
        // insert average in output vector
        values_[i].value = smaValue;
        values_[i].time = newTime;
    }
}

const SMAValues& SimpleMovingAverage::getValues() const
{
    return values_;
}
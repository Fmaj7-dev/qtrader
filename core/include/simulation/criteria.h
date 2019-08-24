#ifndef CRITERIA_H
#define CRITERIA_H

#include <string>
#include <vector>

namespace core
{
namespace simulation
{

// FIXME: currently only one condition supported
class Criteria
{
public:
    // Subject: represents the subject and the object of the action
    class Subject
    {
    public:
        enum class Type
        {
            SMA,
            EMA,
        };

        enum class Series
        {
            BTC,
            BCH,
            ETH
        };

        Subject(){}
        Subject( Type typeInput, Series seriesInput, int valueInput )
            :type(typeInput),
            series(seriesInput),
            value(valueInput)
        {}

        Series series;
        int value;
        Type type;
    };

    // Verb: represents the event that happened
    enum class Verb
    {
        FALL_BEHIND,
        GET_AHEAD,
        IS_HIGHER,
        IS_LOWER
    };

    // Condition: example SMA50 FALL_BEHIND SMA100
    class Condition
    {
    public:
        Condition(Subject subA, 
                  Subject subB,
                  Verb v)
        : a( subA ),
          b( subB ),
          verb( v )
        {}

        Subject a;
        Subject b;
        Verb verb;
    };

    // Criteria: currently only one condition is supported:
    // example: when BTC_SMA50 GET_AHEAD BTC_SMA100 -> BUY
    //
    // it should not be limited, example:
    // when BTC_SMA50 IS_LOWER BTC_SMA100 *AND* BTC_BOLLINGER IS_LOWER 0.1 -> SELL
    Criteria( )
    {
    }

    void addBuyCondition(Condition& condition)
    {
        buyConditions.push_back( condition );
    }

    void addSellCondition(Condition& condition)
    {
        sellConditions.push_back( condition );
    }

    std::vector<Condition> buyConditions;
    std::vector<Condition> sellConditions;
};

}
}
#endif
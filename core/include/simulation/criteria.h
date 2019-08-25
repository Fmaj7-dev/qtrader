#ifndef CRITERIA_H
#define CRITERIA_H

#include "repositorydefinitions.h"

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
        enum class Indicator
        {
            SMA,
            EMA,
        };
        Subject(){}
        Subject( Indicator typeInput, 
                 RepositoryDefinitions::Stock s, 
                 int param )

            :stock( s ),
            indicatorParam( param ),
            indicator( typeInput )
        {}

        RepositoryDefinitions::Stock stock;
        int indicatorParam;
        Indicator indicator;
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
        : subjectA( subA ),
          subjectB( subB ),
          verb( v )
        {}

        Subject subjectA;
        Subject subjectB;
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

    void addBuyCondition(  Condition& condition)
    {
        buyConditions.push_back( condition );
    }

    void addSellCondition( Condition& condition )
    {
        sellConditions.push_back( condition );
    }

    std::vector<Condition> buyConditions;
    std::vector<Condition> sellConditions;
};

}
}
#endif
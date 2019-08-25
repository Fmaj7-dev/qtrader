#include "simulation/simulator.h"
#include "repositorydefinitions.h"
#include "utils/logger.h"

using namespace core;
using namespace core::simulation;

Simulator::Simulator( SeriesRepository& repository )
:repo_( repository )
{
    
}

void Simulator::runSimulation( Simulation& simulation )
{
    const Criteria& criteria = simulation.getCriteria();

    // buy variables
    const Criteria::Condition& buyCondition = criteria.buyConditions[0];
    const Criteria::Subject& buySubjectA = buyCondition.subjectA;
    const Criteria::Subject& buySubjectB = buyCondition.subjectB;
    const std::string& buySeriesNameA = RepositoryDefinitions::toString( buySubjectA.stock );
    const std::string& buySeriesNameB = RepositoryDefinitions::toString( buySubjectB.stock );
    const Criteria::Verb& buyVerb = buyCondition.verb;

    const auto buySeriesA = repo_.getSeries( buySeriesNameA );
    const auto buySeriesB = repo_.getSeries( buySeriesNameB );
    const auto buySMAA = repo_.getSMA( buySeriesNameA, buySubjectA.indicatorParam );
    const auto buySMAB = repo_.getSMA( buySeriesNameB, buySubjectB.indicatorParam );

    // sell variables
    const Criteria::Condition& sellCondition = criteria.sellConditions[0];
    const Criteria::Subject& sellSubjectA = sellCondition.subjectA;
    const Criteria::Subject& sellSubjectB = sellCondition.subjectB;
    const std::string& sellSeriesNameA = RepositoryDefinitions::toString( sellSubjectA.stock );
    const std::string& sellSeriesNameB = RepositoryDefinitions::toString( sellSubjectB.stock );
    const Criteria::Verb& sellVerb = sellCondition.verb;

    const auto sellSeriesA = repo_.getSeries( sellSeriesNameA );
    const auto sellSeriesB = repo_.getSeries( sellSeriesNameB );
    const auto sellSMAA = repo_.getSMA( sellSeriesNameA, sellSubjectA.indicatorParam );
    const auto sellSMAB = repo_.getSMA( sellSeriesNameB, sellSubjectB.indicatorParam );
    

    // FIXME: I'am assuming both series and SMA's have the same size/origin

    int startPoint = std::max(buySubjectA.indicatorParam, buySubjectB.indicatorParam );

    bool buy_aOverB = false;
    bool sell_aOverB = false;

    for( int i = startPoint; i < buySeriesA.values.size(); ++i )
    {
        float valueA = buySMAA.getValues()[i].value;
        float valueB = buySMAB.getValues()[i].value;
        /* if(valueA > valueB) std::cout<<">";
        else std::cout<<"<"; */

        float sellValueA = sellSMAA.getValues()[i].value;
        float sellValueB = sellSMAB.getValues()[i].value;

        // detect change in tendency from a>b to a<b
        if( buy_aOverB && valueB > valueA )
        {
            //log("change");
            if( buyVerb == Criteria::Verb::FALL_BEHIND )
            {
                float amountToSpend = std::min( simulation.getBuyAmount(), simulation.getCapital() );
                float price = buySeriesA.values[i].value;
                //log("buying ", amountToSpend, " at ",  price);
                if( amountToSpend < 1.0 ) continue;
                float assetBought = amountToSpend / price;
                simulation.decreaseCapital( amountToSpend );
                simulation.increaseAsset( assetBought );
            }
        }
        // detect change in tendency from a<b to a>b
        else if ( !buy_aOverB && valueA > valueB )
        {
            //log("change...");
            if( buyVerb == Criteria::Verb::GET_AHEAD )
            {
                float amountToSpend = std::min( simulation.getBuyAmount(), simulation.getCapital() );
                float price = buySeriesA.values[i].value;
                //log("buying ", amountToSpend, " at ",  price);
                if( amountToSpend < 1.0 ) continue;
                float assetBought = amountToSpend / price;
                simulation.decreaseCapital( amountToSpend );
                simulation.increaseAsset( assetBought );
            }
        }
        else
        {
            //log("not buying anything");
        }

        //sell detection
        if( sell_aOverB && sellValueB > sellValueA )
        {
            //log("sell change");
            if( sellVerb == Criteria::Verb::FALL_BEHIND )
            {
                float assetAmount = simulation.getAsset();
                float price = sellSeriesA.values[i].value;
                //log( "selling at ", price );
                simulation.increaseCapital( price * assetAmount );
                simulation.setAsset( 0 );
            }
        }
        // detect change in tendency from a<b to a>b
        else if ( !sell_aOverB && sellValueA > sellValueB )
        {
            //log("sell change...");
            if( sellVerb == Criteria::Verb::GET_AHEAD )
            {
                float assetAmount = simulation.getAsset();
                float price = sellSeriesA.values[i].value;
                //log( "selling at ", price );
                simulation.increaseCapital( price * assetAmount );
                simulation.setAsset( 0 );
            }
        }
        else
        {
            //log("not selling anything");
        }

        buy_aOverB = valueA > valueB;
        sell_aOverB = sellValueA > sellValueB;
    }
}

void Simulator::sellStock( Simulation& simulation )
{
    const Criteria& criteria = simulation.getCriteria();

    Criteria::Condition buyCondition = criteria.buyConditions[0];
    Criteria::Subject buySubjectA = buyCondition.subjectA;
    std::string buySeriesNameA = RepositoryDefinitions::toString( buySubjectA.stock );
    auto buySeriesA = repo_.getSeries( buySeriesNameA );
    float price = buySeriesA.values[ buySeriesA.values.size()-1 ].value;
    //log("selling ALL ", simulation.getAsset(), " at ", price );

    simulation.increaseCapital( simulation.getAsset() * price );
    simulation.setAsset( 0 );
}
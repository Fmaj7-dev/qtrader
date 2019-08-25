//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "utils/logger.h"
#include "seriesrepository.h"
#include "simulation/criteria.h"

//auto repo = std::make_shared<SeriesRepository>();

TEST_CASE("Criteria Construction")
{
  using namespace core;
  using namespace core::simulation;

  Criteria::Subject btcSMA20( Criteria::Subject::Indicator::SMA,
                              RepositoryDefinitions::Stock::LIVE_BTC,
                              20 );

  Criteria::Subject btcSMA100( Criteria::Subject::Indicator::SMA,
                              RepositoryDefinitions::Stock::LIVE_BTC,
                              100 );
                            

  Criteria::Condition buyCondition( btcSMA20, btcSMA100, Criteria::Verb::GET_AHEAD );
  Criteria::Condition sellCondition( btcSMA20, btcSMA100, Criteria::Verb::FALL_BEHIND );

  Criteria criteria;
  criteria.addBuyCondition( buyCondition );
  criteria.addSellCondition( sellCondition );

  REQUIRE( criteria.buyConditions.size() == 1 );
  REQUIRE( criteria.sellConditions.size() == 1 );

  REQUIRE( criteria.buyConditions[0].verb == Criteria::Verb::GET_AHEAD );
  REQUIRE( criteria.sellConditions[0].verb == Criteria::Verb::FALL_BEHIND );
}


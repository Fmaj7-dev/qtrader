#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "seriesrepository.h"

#include <memory>


std::shared_ptr<SeriesRepository> repo;

TEST_CASE("database access test")
{
  int crashed = 0;
  try{
    repo = std::make_shared<SeriesRepository>();
  }
  catch(...)
  {
    ++crashed;
  }

  REQUIRE(crashed == 0);

  try{
    repo.reset();
  }
  catch(...)
  {
    ++crashed;
  }

  REQUIRE(crashed == 0);
}

TEST_CASE("tables reading test")
{

} 

TEST_CASE("series reading test")
{
  SeriesRepository repo;
  auto availableSeries = repo.getAvailableSeries();

  for (auto& i: availableSeries)
  {
      auto series = repo.getSeries(i);
      size_t size = series.values.size();
      std::cout<<i<<" "<<size<<" elements"<<std::endl;
      REQUIRE( size != 0 );
  }

  REQUIRE( 1 == 1);
}

#include "seriesrepository.h"
#include <iostream>

SeriesRepository::SeriesRepository()
{
    
}

void SeriesRepository::fillAllSeries()
{
    auto tables= sqlProvider_.getAvailableTables();
    for( auto& tableName : tables)
    {
        // insert series if not exist
        if ( tableName.compare(0, 5, "live_") != 0 )
        {
            LiveSeries newSeries( tableName );
            sqlProvider_.fillLiveSeries( newSeries, tableName );
            liveSeriesMap_.emplace( tableName, newSeries );
        }
    }
}

SeriesList SeriesRepository::getAvailableSeries()
{
    return sqlProvider_.getAvailableTables();
}

// name must exist
const LiveSeries& SeriesRepository::getSeries( std::string name )
{
    auto search = liveSeriesMap_.find( name );

    // if not exist
    if ( search == liveSeriesMap_.end() )
    {
        // FIXME: make sure we are not copying it 
        LiveSeries newSeries( name );
        sqlProvider_.fillLiveSeries( newSeries, name );
        liveSeriesMap_.emplace( name, newSeries );
    }

    search = liveSeriesMap_.find( name );
    return search->second;
}

const SimpleMovingAverage& SeriesRepository::getSMA( std::string seriesName, int n )
{
    // get series SMA is based on
    const LiveSeries& series = getSeries( seriesName );

    // sma must be unique based on name and main parameter
    std::string smaName = seriesName + std::to_string(n);

    auto search = SMAMap_.find( smaName );

    // if not exist
    if ( search == SMAMap_.end() )
    {
        SimpleMovingAverage sma;
        sma.calculate( series, n );
        SMAMap_.emplace( smaName, sma );
    }

    search = SMAMap_.find( smaName );
    return search->second;
}
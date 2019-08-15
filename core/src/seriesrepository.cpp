#include "seriesrepository.h"

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

const LiveSeries& SeriesRepository::getSeries( std::string name )
{
    auto search = liveSeriesMap_.find( name );

    // if not exist
    if ( search == liveSeriesMap_.end() )
    {
        LiveSeries newSeries( name );
        sqlProvider_.fillLiveSeries( newSeries, name );
        liveSeriesMap_.emplace( name, newSeries );
    }

    search = liveSeriesMap_.find( name );
    return search->second;
}